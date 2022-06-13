//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_CUBICSPLINE_H
#define SFMATH_CUBICSPLINE_H


class CubicSpline {
public:
    CubicSpline(float *xdat, float *ydat, unsigned int N); //construct
    float Interpolate(float x); //Get spline value at point
    int datN;
    float *xData;
    float *yData;
    float *dX;
    float **coeffs;
};


#endif //SFMATH_CUBICSPLINE_H
