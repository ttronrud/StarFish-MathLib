//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_FFT_CAPI_H
#define SFMATH_FFT_CAPI_H


extern "C" {
//~~~~~FFT Methods~~~~~//
__declspec(dllexport) void __stdcall FFT_PredictN(unsigned int data_len, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_PSD(float *data, unsigned int data_len, bool use_hanning, float *out_data, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_PSD_windows(float *data, unsigned int data_len, unsigned int window_size, bool use_hanning, float *out_data, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_Spectrum(float *data_re, float *data_im, unsigned int data_len, bool use_hanning, float *out_data_re, float *out_data_im, int *out_len);
};


#endif //SFMATH_FFT_CAPI_H
