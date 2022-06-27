//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_CUBICSPLINE_CAPI_H
#define SFMATH_CUBICSPLINE_CAPI_H


extern "C"
{
__declspec(dllexport) void __stdcall CSpline_Interp(double *X, double*Y, unsigned int N, double *intXs, double *predYs, unsigned int NPreds);
__declspec(dllexport) void __stdcall CSpline_Coeffs(double *X, double*Y, unsigned int N, double **coeffs);
};


#endif //SFMATH_CUBICSPLINE_CAPI_H
