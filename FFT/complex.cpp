//
// Created by ttronrud on 2022-06-10.
// A complex number class with overloaded operators
//

#include "complex.h"

SFComplex::SFComplex(double re, double im)
{
    real = re;
    imag = im;
}
//copy constructor
SFComplex::SFComplex(SFComplex *c)
{
    real = c->real;
    imag = c->imag;
}
//overload complex operators
SFComplex SFComplex::operator + (SFComplex const &obj)
{
    SFComplex res;
    res.real = real + obj.real;
    res.imag = imag + obj.imag;
    return res;
}
SFComplex SFComplex::operator - (SFComplex const &obj)
{
    SFComplex res;
    res.real = real - obj.real;
    res.imag = imag - obj.imag;
    return res;
}
SFComplex SFComplex::operator * (SFComplex const &obj)
{
    SFComplex res;
    res.real = real*obj.real - imag*obj.imag;
    res.imag = real*obj.imag + imag*obj.real;
    return res;
}
SFComplex SFComplex::operator * (double mul)
{
    SFComplex res;
    res.real = real*mul;
    res.imag = imag*mul;
    return res;
}
SFComplex SFComplex::operator / (double mul)
{
    SFComplex res;
    res.real = real/mul;
    res.imag = imag/mul;
    return res;
}
double SFComplex::mag()
{
    return (double)sqrt(real*real + imag*imag); //magnitude is sqrt(zz*)
}
//////////////////