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
};

//Test functions
void TestFFT();
#endif //SFMATH_SFMATHCONSOLE_H
