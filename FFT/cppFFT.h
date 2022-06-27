//
// Created by ttronrud on 2022-06-24.
//

#ifndef SFMATH_CPPFFT_H
#define SFMATH_CPPFFT_H

#include "complex.h"
#include <cstdlib>

typedef enum fft_dir {
    FFT_FORWARD,    /* kernel uses "-1" sign */
    FFT_INVERSE     /* kernel uses "+1" sign */
} fft_dir;

class cppFFT {
public:
    //vars
    SFComplex *data;
    unsigned log2_N;
    fft_dir direction;
    SFComplex *res;
    //TO DO: Replace with Complex class
    cppFFT(SFComplex *indat, int N, fft_dir dir);
    //cppFFT(Complex<double> *indat, int N, fft_dir dir);
    static unsigned log2_u(unsigned v);
/* In-place FFT */
    void ffti_f();

private:
    void ffti_shuffle_f();
    void ffti_evaluate_f();
};


#endif //SFMATH_CPPFFT_H
