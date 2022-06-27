//
// Created by ttronrud on 2022-06-24.
//
/*
MIT License

Copyright (c) 2018 Robert S. Huston, Pinpoint Dynamics, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
        of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
        copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
        copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//Based on https://github.com/RussellHaley/FFT-C by Russell Haley and rshuston
//Converted to C++ class by ttronrud

#ifndef SFMATH_CPPFFT_H
#define SFMATH_CPPFFT_H

#include "complex.h"
#include <cstdlib>

typedef enum fft_dir {
    FFT_FORWARD,    /* kernel uses "-1" sign */
    FFT_INVERSE     /* kernel uses "+1" sign */
} fft_dir;

class cppFFT {
public:
    //vars
    SFComplex *data;
    unsigned log2_N;
    fft_dir direction;
    SFComplex *res;
    //TO DO: Replace with Complex class
    cppFFT(SFComplex *indat, int N, fft_dir dir);
    //cppFFT(Complex<double> *indat, int N, fft_dir dir);
    static unsigned log2_u(unsigned v);
/* In-place FFT */
    void ffti_f();

private:
    void ffti_shuffle_f();
    void ffti_evaluate_f();
};


#endif //SFMATH_CPPFFT_H
