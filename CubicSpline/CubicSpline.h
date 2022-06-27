//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_CUBICSPLINE_H
#define SFMATH_CUBICSPLINE_H


class CubicSpline {
public:
    CubicSpline(double *xdat, double *ydat, unsigned int N); //construct
    float Interpolate(double x); //Get spline value at point
    int datN;
    double *xData;
    double *yData;
    double *dX;
    double **coeffs;
};


#endif //SFMATH_CUBICSPLINE_H
