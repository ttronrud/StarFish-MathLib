//
// Original: https://github.com/RussellHaley/FFT-C by Russell Haley
// With contributions from rshuston
// Added to SFMath library by ttronrud
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
#ifndef SFMATH_FFT_H
#define SFMATH_FFT_H

#include "complex.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum fft_dir {
    FFT_FORWARD,    /* kernel uses "-1" sign */
    FFT_INVERSE     /* kernel uses "+1" sign */
} fft_dir;

unsigned log2_u(unsigned v);
/* In-place FFT */
void ffti_f(complex_f data[], unsigned log2_N, fft_dir direction);

/* ... In-place FFT stage functions ... */
void ffti_copy_shuffle_f(complex_f src[], complex_f dst[], unsigned log2_N);
void ffti_shuffle_f(complex_f data[], unsigned log2_N);
void ffti_evaluate_f(complex_f data[], unsigned log2_N, fft_dir direction);

/* Recursive FFT */
void fftr_f(complex_f data[], unsigned log2_N, fft_dir direction);

/* Recursive FFT, user-supplied scratchpad buffer */
void fftrb_f(complex_f data[], unsigned log2_N, fft_dir direction, complex_f scratch[]);


#ifdef __cplusplus
}
#endif


#endif //SFMATH_FFT_H
