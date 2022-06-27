//
// Created by ttronrud on 2022-06-24.
//

#include "cppFFT.h"
#include <cstring>

cppFFT::cppFFT(SFComplex *indat, int N, fft_dir dir)
{
    auto n = (unsigned)N;
    log2_N = log2_u(n);
    data = (SFComplex *) malloc(n*sizeof(SFComplex)); //store original data
    res = (SFComplex *) malloc(n*sizeof(SFComplex)); //where the result will live
    memcpy(data, indat, n*sizeof(SFComplex));
    memcpy(res, indat, n*sizeof(SFComplex));
    direction = dir;
}

unsigned int cppFFT::log2_u(unsigned int v)
{
    int r;      // result goes here

    static const int _multiplyDeBruijnBitPosition[32] =
            {
                    0, 9, 1, 10, 13, 21, 2, 29, 11, 14, 16, 18, 22, 25, 3, 30,
                    8, 12, 20, 28, 15, 17, 24, 7, 19, 27, 23, 6, 26, 5, 4, 31
            };

    v |= v >> 1; // first round down to one less than a power of 2
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;

    r = _multiplyDeBruijnBitPosition[(unsigned)(v * 0x07C4ACDDU) >> 27];

    return r;
}

void cppFFT::ffti_f()
{

    //Now only "res" will be modified
    //and the original data is preserved
    ffti_shuffle_f();
    ffti_evaluate_f();
}

void cppFFT::ffti_shuffle_f()
{
    /*
     * Basic Bit-Reversal Scheme:
     *
     * The incrementing pattern operations used here correspond
     * to the logic operations of a synchronous counter.
     *
     * Incrementing a binary number simply flips a sequence of
     * least-significant bits, for example from 0111 to 1000.
     * So in order to compute the next bit-reversed index, we
     * have to flip a sequence of most-significant bits.
     */

    //Test with new complex class

    unsigned N = 1 << log2_N;   /* N */
    unsigned Nd2 = N >> 1;      /* N/2 = number range midpoint */
    unsigned Nm1 = N - 1;       /* N-1 = digit mask */
    unsigned i;                 /* index for array elements */
    unsigned j;                 /* index for next element swap location */

    for (i = 0, j = 0; i < N; i++) {
        if (j > i) {
            SFComplex tmp = res[i];
            res[i] = res[j];
            res[j] = tmp;
        }

        /*
         * Find least significant zero bit
         */

        unsigned lszb = ~i & (i + 1);

        /*
         * Use division to bit-reverse the single bit so that we now have
         * the most significant zero bit
         *
         * N = 2^r = 2^(m+1)
         * Nd2 = N/2 = 2^m
         * if lszb = 2^k, where k is within the range of 0...m, then
         *     mszb = Nd2 / lszb
         *          = 2^m / 2^k
         *          = 2^(m-k)
         *          = bit-reversed value of lszb
         */

        unsigned mszb = Nd2 / lszb;

        /*
         * Toggle bits with bit-reverse mask
         */

        unsigned bits = Nm1 & ~(mszb - 1);
        j ^= bits;
    }
}



void cppFFT::ffti_evaluate_f()
{
    /*
     * In-place FFT butterfly algorithm
     *
     * input:
     *     A[] = array of N shuffled complex values where N is a power of 2
     * output:
     *     A[] = the DFT of input A[]
     *
     * for r = 1 to log2(N)
     *     m = 2^r
     *     Wm = exp(−j2π/m)
     *     for n = 0 to N-1 by m
     *         Wmk = 1
     *         for k = 0 to m/2 - 1
     *             u = A[n + k]
     *             t = Wmk * A[n + k + m/2]
     *             A[n + k]       = u + t
     *             A[n + k + m/2] = u - t
     *             Wmk = Wmk * Wm
     *
     * For inverse FFT, use Wm = exp(+j2π/m)
     */

    unsigned N;
    unsigned r;
    unsigned m, md2;
    unsigned n, k;
    unsigned i_e, i_o;
    double theta_2pi;
    double theta;       /* Use double for precision */
    SFComplex Wm, Wmk;  /* Use double for precision */
    SFComplex u, t;     /* Use double for precision */

    N = 1 << log2_N;
    theta_2pi = (direction == FFT_FORWARD) ? -M_PI : M_PI;
    theta_2pi *= 2;

    for (r = 1; r <= log2_N; r++)
    {
        m = 1 << r;
        md2 = m >> 1;
        theta = theta_2pi / m;
        Wm = SFComplex(cos(theta), sin(theta));
        //Wm.real = cos(theta);
        //Wm.imag = sin(theta);
        for (n = 0; n < N; n += m)
        {
            Wmk = SFComplex(1.0,0.0);
            //Wmk.re = 1.f;
            //Wmk.im = 0.f;
            for (k = 0; k < md2; k++)
            {
                i_e = n + k;
                i_o = i_e + md2;
                u = SFComplex(res[i_e]);
                //u.re = res[i_e].re;
                //u.im = res[i_e].im;
                t = Wmk*res[i_o];
                //t.re = complex_mul_re(Wmk.re, Wmk.im, res[i_o].re, res[i_o].im);
                //t.im = complex_mul_im(Wmk.re, Wmk.im, res[i_o].re, res[i_o].im);
                res[i_e] = u + t;
                //res[i_e].re = u.re + t.re;
                //res[i_e].im = u.im + t.im;
                res[i_o] = u-t;
                //res[i_o].re = u.re - t.re;
                //res[i_o].im = u.im - t.im;
                t = Wmk * Wm;
                //t.re = complex_mul_re(Wmk.re, Wmk.im, Wm.re, Wm.im);
                //t.im = complex_mul_im(Wmk.re, Wmk.im, Wm.re, Wm.im);
                Wmk = t;
            }
        }
    }
}