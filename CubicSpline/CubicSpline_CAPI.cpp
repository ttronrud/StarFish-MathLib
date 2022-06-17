//~~~~~~~~~~CSpline Methods~~~~~~~~~~//
/* Files: CubicSpline.cpp/h
 * Contributors: Thor Tronrud (SFM), Tomer953 (GH)
 * Initial Source: https://github.com/tomer953/cubic-spline
 *                 Based on https://www.math.ntnu.no/emner/TMA4215/2008h/cubicsplines.pdf
 * Description:
 * Generates piecewise cubic function to approximate input data, and interpolate any x value within the initial
 * range by finding the corresponding cubic spline S_i and calculating the approximation based on difference
 * from the spline-chunk's origin
 *
 * The exposed methods are:
 * CSpline_Interp ~ Take input X and Y arrays of length N, as well as interpolation Xs, and an allocated array for
 *                  predicted Y values, both of length NPreds
 * CSpline_Coeffs ~ Populate an input reference array of shape (N,4) with the calculated cubic coefficients for the
 *                  input X,Y data.
 *                  To calculate the spline interpolation at x manually for an index i, use:
 *                  A = coeff[i][0]
 *                  B = coeff[i][1]
 *                  C = coeff[i][2]
 *                  D = coeff[i][3]
 *                  h = x - X[i] //Offset from spline root
 *                  S_i(x) = A*h^3 + B*h^2 + C*h + D
 *
 * Notes:
 *  Really doesn't do well past the initial input values (as expected of cubic splines). Try really hard to keep
 *  evaluation values within the input range
 */

#include "CubicSpline_CAPI.h"
#include "CubicSpline.h"
#include "../SFMathCAPI.h"
#include <iostream>
extern "C"{

SFMATH_EXPORT void __stdcall CSpline_Interp(float *X, float*Y, unsigned int N, float *intXs, float *predYs, unsigned int NPreds)
{
    CubicSpline *cspline = new CubicSpline(X,Y,N);
    for(int i = 0; i < NPreds; i++)
    {
        predYs[i] = cspline->Interpolate(intXs[i]);
    }
}
SFMATH_EXPORT void __stdcall CSpline_Coeffs(float *X, float*Y, unsigned int N, float **coeffs)
{
    CubicSpline *cspline = new CubicSpline(X,Y,N);
    for(int i = 0; i < N; i++)
    {
        coeffs[i][0] = cspline->coeffs[i][0];
        coeffs[i][1] = cspline->coeffs[i][1];
        coeffs[i][2] = cspline->coeffs[i][2];
        coeffs[i][3] = cspline->coeffs[i][3];
    }
}

};
