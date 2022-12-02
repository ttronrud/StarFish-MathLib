/**
 * ------------------------------------------------------------------------------*
 * File: panTompkins.h                                                           *
 *       Header for an ANSI-C implementation of Pan-Tompkins real-time QRS detec-*
 *       tion algorithm                                                          *
 * Author: Rafael de Moura Moreira <rafaelmmoreira@gmail.com>                    *
 * License: MIT License                                                          *
 * ------------------------------------------------------------------------------*
 * MIT License                                                                   *
 *                                                                               *
 * Copyright (c) 2018 Rafael de Moura Moreira                                    *
 *                                                                               *
 * Permission is hereby granted, free of charge, to any person obtaining a copy  *
 * of this software and associated documentation files (the "Software"), to deal *
 * in the Software without restriction, including without limitation the rights  *
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell     *
 * copies of the Software, and to permit persons to whom the Software is         *
 * furnished to do so, subject to the following conditions:                      *
 *                                                                               *
 * The above copyright notice and this permission notice shall be included in all*
 * copies or substantial portions of the Software.                               *
 *                                                                               *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR    *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,      *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE   *
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER        *
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, *
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE *
 * SOFTWARE.                                                                     *
 *-------------------------------------------------------------------------------*
 */

#ifndef SFMATH_PANTOMPKINS_H
#define SFMATH_PANTOMPKINS_H

#define NOSAMPLE -32000 // An indicator that there are no more samples to read. Use an impossible value for a sample.
//#define FS 250          // Sampling frequency.
#define BUFFSIZE 415    // The size of the buffers (in samples). Must fit more than 1.66 times an RR interval, which
// typically could be around 1 second.

#define  MOVING_AVG_LEN 5

#define WINDOWSIZE 40

#define FS 250

class PanTompkins
{

    static int sample;
    static double signal[BUFFSIZE], dcblock[BUFFSIZE], lowpass[BUFFSIZE], highpass[BUFFSIZE], derivative[BUFFSIZE], squared[BUFFSIZE], integral[BUFFSIZE], outputSignal[BUFFSIZE];
    static int rr1[8], rr2[8], rravg1, rravg2, rrlow, rrhigh, rrmiss;
    static double peak_i, peak_f, threshold_i1, threshold_i2, threshold_f1, threshold_f2, spk_i, spk_f, npk_i, npk_f;
    static int i, j, lastQRS;
    static double lastSlope, currentSlope;
    static int current;
    static double last_avg[MOVING_AVG_LEN];
    static double avg;
    static bool qrs, regular, prevRegular;

public:
    static int DELAY;
    static void PanTompkins_init();
    static bool PanTompkins_SingleStep(double inputSample);
};




#endif //SFMATH_PANTOMPKINS_H
