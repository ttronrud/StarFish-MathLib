//
// Created by ttronrud on 2022-06-10.
//
#include "../SFMathCAPI.h"
#include "FFT_CAPI.h"
//#include "FFT.h"
#include "cppFFT.h"
#include <iostream>

//~~~~~~~~~~FFT Methods~~~~~~~~~~//
/* Files: FFT.cpp/h, complex.cpp/h
 * Contributors: Russell Haley (SFM), rshuston (GH), Thor Tronrud (SFM)
 * Initial Source: https://github.com/russellhaley/FFT-C/
 * Description:
 * An implementation of a fast fourier transform method, and helper functions to facilitate
 * the use of native C/CPP types in caller methods, instead of requiring complex math libraries
 *
 * The exposed methods are:
 * PredictN ~ Predict the number of output spectral bins with the same math used to calculate the value in
 *            the heavy-lifting methods. *This might be useful for pre-allocation in the caller libraries!*
 * FFTSpectrum ~ take real floating-point data as input, perform an FFT, and calculate the spectral power array
 *               to return by reference, through pre-assigned arrays.
 *               The returned spectrum has frequency values for each bin defined by the sampling rate of the input
 *               data -- e.g. total time of 256s, with 512 samples, gives a freq of 2 Hz to out_len.
 *               This means the bin->freq mapping for bin i, calculated on data with # samples N over time T is:
 *                          freq(i) = N/T * i/out_len (Hz)
 * FFT_PSD ~ take an array of data, compute the FFT spectrum, and calculate the power with the magnitude of
 *           the real+imaginary vectors.
 * FFT_PSD_windows ~ compute the average FFT PSD on windows across the entire data.
 *
 * Notes:
 * The returned spectra will have an index->frequency mapping based on the output length, L. The mapping is:
 * (index/L) Hz.
 */
extern "C" {
//Finds the nearest power-of-two for output spectrum length
SFMATH_EXPORT void __stdcall FFT_PredictN(unsigned int data_len, int *out_data_len)
{
    if (out_data_len == nullptr)
        return;
    unsigned r = cppFFT::log2_u(data_len);
    unsigned N = 1 << r;
    *out_data_len = N;
}

/*
 * FFT_PSD_windows
 * An intermediary function to take in a long array of data,
 * split into windows of a specific size (preferably power of 2!),
 * and return the averaged PSD across all windows over the data
 * by reference!
 */
SFMATH_EXPORT void __stdcall FFT_PSD_windows(double *data, unsigned int data_len, unsigned int window_size, bool use_hanning, double *out_data, int*out_data_len)
{

    if(out_data == nullptr || out_data_len == nullptr)
        return;
    //how many windows?
    unsigned n_wind = data_len/window_size;
    double *tmp_psd = (double *)malloc(window_size*sizeof(double));
    double *tmp_dat = (double *)malloc(window_size*sizeof(double));
    memset(out_data,0,window_size*sizeof(double));

    for(int i = 0; i < n_wind; i++)
    {
        //construct window of data
        for(int j = 0; j < window_size; j++)
        {
            tmp_dat[j] = data[i*window_size + j]; //get offset data
        }
        FFT_PSD(tmp_dat, window_size, use_hanning, tmp_psd, out_data_len);
        //now add to total PSD, which is our output-by-reference
        for(int j = 0; j < window_size; j++)
        {
            out_data[j] += tmp_psd[j]/(1.0*n_wind);
        }
    }
    free(tmp_psd);
    free(tmp_dat);

}

SFMATH_EXPORT void __stdcall FFT_PSD(double *data, unsigned int data_len, bool use_hanning, double *out_data, int*out_data_len)
{
    if(out_data == nullptr)
        return;
    //Create our complex data representation
    SFComplex *cdata;
    cdata = (SFComplex *)malloc(data_len*sizeof(SFComplex));

    //first, we need to turn the real data into complex data
    for(int i = 0; i < data_len; i++)
    {
        cdata[i] = SFComplex(data[i],0.0);
        //cdata[i].re = data[i];
        //cdata[i].im = 0.0f;
        if(use_hanning)
        {
            cdata[i] = cdata[i]*(0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
        }
    }
    unsigned r = cppFFT::log2_u(data_len);
    unsigned N = 1 << r; //how many indices will be returned?
    std::unique_ptr<cppFFT> fft(new cppFFT(cdata, N, FFT_FORWARD));
    fft->ffti_f();
    //ffti_f(cdata, r ,FFT_FORWARD);

    for(int i = 0; i < N; i++)
    {
        out_data[i] = fft->res[i].mag();
                //sqrt(fft->res[i].re*fft->res[i].re + fft->res[i].im*fft->res[i].im);
        //out_data[i] = sqrt(cdata[i].re*cdata[i].re + cdata[i].im*cdata[i].im); //get magnitude for spectrum
        //std::cout << out_data[i] << std::endl;
    }
    *out_data_len = N; //write N to the out-data's length

    free(cdata); //free our complex data, now that we're done with it
}

SFMATH_EXPORT void __stdcall FFT_Spectrum(double *data_re, double *data_im, unsigned int data_len, bool use_hanning, double *out_data_re, double *out_data_im, int *out_len)
{
    if(out_data_im == nullptr || out_data_re == nullptr)
        return; //can't add to null pointers
    unsigned r = cppFFT::log2_u(data_len);
    unsigned N = 1 << r; //how many indices will be returned?
    //Create our complex data representation
    SFComplex *cdata;
    cdata = (SFComplex*)malloc(data_len*sizeof(SFComplex));

    //if the imaginary component isn't defined, just keep it zero-d
    if(data_im == nullptr)
    {
        //first, we need to turn the components into complex data
        for(int i = 0; i < data_len; i++)
        {
            cdata[i] = SFComplex(data_re[i],0.0);
            //cdata[i].re = data_re[i];
            //cdata[i].im = 0.0f;

            if(use_hanning)
                cdata[i] = cdata[i]*(0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
            //cdata[i].re *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
        }
    }
    else //If there's an imaginary input component
    {
        //first, we need to turn the components into complex data
        for(int i = 0; i < data_len; i++)
        {
            cdata[i] = SFComplex(data_re[i], data_im[i]);
            //cdata[i].re = data_re[i];
            //cdata[i].im = data_im[i];

            if(use_hanning)
            {
                cdata[i] = cdata[i]*(0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
                //cdata[i].re *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
                //cdata[i].im *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
            }
        }
    }

    std::unique_ptr<cppFFT> fft(new cppFFT(cdata, N, FFT_FORWARD));
    fft->ffti_f();
    //ffti_f(cdata, r ,FFT_FORWARD);

    for(int i = 0; i < N; i++)
    {
        out_data_re[i] = fft->res[i].mag()/N;
        //out_data_im[i] = fft->res[i].im/N;
        //out_data_re[i] = cdata[i].re/N;
        //out_data_im[i] = cdata[i].im/N;
    }
    if(out_len == nullptr)
    {
        out_len = (int*)malloc(sizeof(int));
    }
    *out_len = N;

    free(cdata);
}
}