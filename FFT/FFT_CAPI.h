//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_FFT_CAPI_H
#define SFMATH_FFT_CAPI_H


extern "C" {
//~~~~~FFT Methods~~~~~//
__declspec(dllexport) void __stdcall FFT_PredictN(unsigned int data_len, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_PSD(double *data, unsigned int data_len, bool use_hanning, double *out_data, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_PSD_windows(double *data, unsigned int data_len, unsigned int window_size, bool use_hanning, double *out_data, int*out_data_len);
__declspec(dllexport) void __stdcall FFT_Spectrum(double *data_re, double *data_im, unsigned int data_len, bool use_hanning, double *out_data_re, double *out_data_im, int *out_len);
};


#endif //SFMATH_FFT_CAPI_H
