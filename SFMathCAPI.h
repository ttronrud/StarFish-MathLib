//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCAPI_H
#define SFMATH_SFMATHCAPI_H

extern "C" {
    __declspec(dllexport) void __stdcall Hello();
    //~~~~~FFT Methods~~~~~//
    __declspec(dllexport) void __stdcall FFTSpectrum(float *data, unsigned int data_len, bool use_hanning, float *out_data, int*out_data_len);
    __declspec(dllexport) void __stdcall FFT(float *data_re, float *data_im, unsigned int data_len, bool use_hanning, float *out_data_re, float *out_data_im, int *out_len);
};


#endif //SFMATH_SFMATHCAPI_H
