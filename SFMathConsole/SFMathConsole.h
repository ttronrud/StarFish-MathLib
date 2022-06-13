//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCONSOLE_H
#define SFMATH_SFMATHCONSOLE_H

//Functions imported from DLL
extern "C"
{
    //DLL Import of FFT_PSD from DLL
    __declspec(dllimport) void __stdcall FFT_PSD(float *data, unsigned int data_len, bool use_hanning, float *out_data, int*out_data_len);
    __declspec(dllimport) void __stdcall SFMath_Hello();
    __declspec(dllimport) void __stdcall CSpline_Interp(float *X, float*Y, unsigned int N, float *intXs, float *predYs, unsigned int NPreds);
};

//Test functions
void TestFFT();
void TestCSpline();
#endif //SFMATH_SFMATHCONSOLE_H
