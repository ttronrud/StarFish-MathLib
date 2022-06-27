//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCONSOLE_H
#define SFMATH_SFMATHCONSOLE_H

//Functions imported from DLL
extern "C"
{
    //DLL Import of FFT_PSD from DLL
    __declspec(dllimport) void __stdcall FFT_PSD(double *data, unsigned int data_len, bool use_hanning, double *out_data, int*out_data_len);
    __declspec(dllimport) void __stdcall FFT_PSD_windows(double *data, unsigned int data_len, unsigned int window_size, bool use_hanning, double *out_data, int*out_data_len);
    __declspec(dllimport) void __stdcall SFMath_Hello();
    __declspec(dllimport) void __stdcall CSpline_Interp(double *X, double*Y, unsigned int N, double *intXs, double *predYs, unsigned int NPreds);
};

//Test functions
void TestFFT();
void TestCSpline();
void ComboCSplineFFTTest();
void RRPracticeTest();
#endif //SFMATH_SFMATHCONSOLE_H
