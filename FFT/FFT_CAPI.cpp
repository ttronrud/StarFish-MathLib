//
// Created by ttronrud on 2022-06-10.
//

#include "FFT_CAPI.h"
#include "FFT.h"
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
 * FFT ~ take arrays of real and imaginary components, perform an FFT, and write the real and imaginary spectral
 *       components to pre-allocated arrays
 *
 * Notes:
 * The returned spectra will have an index->frequency mapping based on the output length, L. The mapping is:
 * (index/L) Hz.
 */

extern "C" __declspec(dllexport) void __stdcall FFT_PredictN(unsigned int data_len, int *out_data_len)
{
    if (out_data_len == NULL)
        return;
    unsigned r = log2_u(data_len);
    unsigned N = 1 << r;
    *out_data_len = N;
}

extern "C" __declspec(dllexport) void __stdcall FFT_PSD(float *data, unsigned int data_len, bool use_hanning, float *out_data, int*out_data_len)
{
    if(out_data == NULL)
        return;
    //Create our complex data representation
    complex_f *cdata;
    cdata = (complex_f*)malloc(data_len*sizeof(complex_f));

    //first, we need to turn the real data into complex data
    for(int i = 0; i < data_len; i++)
    {
        cdata[i].re = data[i];
        cdata[i].im = 0.0f;
        if(use_hanning)
            cdata[i].re *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
    }
    unsigned r = log2_u(data_len);
    unsigned N = 1 << r; //how many indices will be returned?
    ffti_f(cdata, r ,FFT_FORWARD);

    for(int i = 0; i < N; i++)
    {
        out_data[i] = sqrt(cdata[i].re*cdata[i].re + cdata[i].im*cdata[i].im)/N; //get magnitude for spectrum
        //std::cout << out_data[i] << std::endl;
    }
    *out_data_len = N; //write N to the out-data's length

    free(cdata); //free our complex data, now that we're done with it
}

extern "C" __declspec(dllexport) void __stdcall FFT_Spectrum(float *data_re, float *data_im, unsigned int data_len, bool use_hanning, float *out_data_re, float *out_data_im, int *out_len)
{
    if(out_data_im == NULL || out_data_re == NULL)
        return; //can't add to null pointers
    unsigned r = log2_u(data_len);
    unsigned N = 1 << r; //how many indices will be returned?
    //Create our complex data representation
    complex_f *cdata;
    cdata = (complex_f*)malloc(data_len*sizeof(complex_f));

    //if the imaginary component isn't defined, just keep it zero-d
    if(data_im == NULL)
    {
        //first, we need to turn the components into complex data
        for(int i = 0; i < data_len; i++)
        {
            cdata[i].re = data_re[i];
            cdata[i].im = 0.0f;

            if(use_hanning)
                cdata[i].re *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
        }
    }
    else //If there's an imaginary input component
    {
        //first, we need to turn the components into complex data
        for(int i = 0; i < data_len; i++)
        {
            cdata[i].re = data_re[i];
            cdata[i].im = data_im[i];

            if(use_hanning)
            {
                cdata[i].re *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
                cdata[i].im *= (0.5 - 0.5*cos(2*3.14159 * (i+1)/(data_len + 1)));
            }
        }
    }
    ffti_f(cdata, r ,FFT_FORWARD);

    for(int i = 0; i < N; i++)
    {
        out_data_re[i] = cdata[i].re/N;
        out_data_im[i] = cdata[i].im/N;
    }
    if(out_len == NULL)
    {
        out_len = (int*)malloc(sizeof(int));
    }
    *out_len = N;

    free(cdata);
}