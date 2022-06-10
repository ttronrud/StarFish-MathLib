//
// Created by ttronrud on 2022-06-10.
//

#include "SFMathCAPI.h"
#include <stdio.h>
#include <iostream>
#include "FFT.h"

//Basic exposed method to make sure DLL is imported
//correctly
extern "C" __declspec(dllexport) void __stdcall Hello()
{
    std::cout << "Hello!" << std::endl;
}

//~~~~~~~~~~FFT Methods~~~~~~~~~~//
//Feed in real data, the length, and pointers to the output data and output data length
//Return the spectral magnitude (sqrt of squared sum of real and imaginary components)
//Without modifying input data
//and ouput by ref instead of return vals
//if you can estimate the length of the output data, you can static-allocate them and just use out_data_len
//to limit access
//Hanning window reduces noise outside of the main peak
extern "C" __declspec(dllexport) void __stdcall FFTSpectrum(float *data, unsigned int data_len, bool use_hanning, float *out_data, int*out_data_len)
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
        out_data[i] = sqrt(cdata[i].re*cdata[i].re + cdata[i].im*cdata[i].im); //get magnitude for spectrum
        //std::cout << out_data[i] << std::endl;
    }
    *out_data_len = N; //write N to the out-data's length

    free(cdata); //free our complex data, now that we're done with it
}

//Basic FFT function exposed more directly
//Take real and imaginary components, return the real and imaginary components
extern "C" __declspec(dllexport) void __stdcall FFT(float *data_re, float *data_im, unsigned int data_len, bool use_hanning, float *out_data_re, float *out_data_im, int *out_len)
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
        out_data_re[i] = cdata[i].re;
        out_data_im[i] = cdata[i].im;
    }
    if(out_len == NULL)
    {
        out_len = (int*)malloc(sizeof(int));
    }
    *out_len = N;

    free(cdata);
}