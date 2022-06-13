//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_CUBICSPLINE_CAPI_H
#define SFMATH_CUBICSPLINE_CAPI_H


extern "C"
{
__declspec(dllexport) void __stdcall CSpline_Interp(float *X, float*Y, unsigned int N, float *intXs, float *predYs, unsigned int NPreds);
__declspec(dllexport) void __stdcall CSpline_Coeffs(float *X, float*Y, unsigned int N, float **coeffs);
};


#endif //SFMATH_CUBICSPLINE_CAPI_H
