//
// Created by ttronrud on 2022-06-10.
//

#include "complex.h"

Complex::Complex(float re, float im)
{
    real = re;
    imag = im;
}
//overload complex operators
Complex Complex::operator + (Complex const &obj)
{
    Complex res;
    res.real = real + obj.real;
    res.imag = imag + obj.imag;
    return res;
}
Complex Complex::operator * (Complex const &obj)
{
    Complex res;
    res.real = real*obj.real - imag*obj.imag;
    res.imag = real*obj.imag + imag*obj.real;
    return res;
}
float Complex::mag()
{
    return sqrt(real*real + imag*imag); //magnitude is sqrt(zz*)
}