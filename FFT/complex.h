//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_COMPLEX_H
#define SFMATH_COMPLEX_H

#include <cmath>

//try a more complete complex class
class Complex {
private:
    float real;
    float imag;
public:
    Complex(float re=0, float im=0);

    Complex operator + (Complex const &obj);
    Complex operator * (Complex const &obj);
    float mag();
};

typedef struct complex_f {
    float re;
    float im;
} complex_f;

typedef struct complex_d {
    double re;
    double im;
} complex_d;


#define complex_mul_re(a_re, a_im, b_re, b_im)  (a_re * b_re - a_im * b_im)
#define complex_mul_im(a_re, a_im, b_re, b_im)  (a_re * b_im + a_im * b_re)
#define M_PI 3.1415926


#endif

