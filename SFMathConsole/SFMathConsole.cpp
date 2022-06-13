//
// Created by ttronrud on 2022-06-10.
// THIS IS A TESTING PROGRAM - It depends on the SFMath methods
//

#include <cstdlib>
#include <cstdio>
#include "SFMathConsole.h"
//#include "../FFT/FFT_CAPI.h"
#include <iostream>

int main(int argc, char * argv[])
{
    //SFMath_Hello();
    TestFFT();
    TestCSpline();
}

void TestCSpline()
{
    printf("Beginning CSpline test. Going from 250s sine wave w/T=24.0s, Nsamp = 250\nto interpolate 1k values between t=(1,249).\nExpected # of zeros should both = 10\n");
    float T = 24.0;//11.1111;
    float total_t = 250.0; //seconds of "total elapsed time"
    int L = 250; //how many samples for data
    float zeroval = 0;

    float *initialX = (float*)malloc(L*sizeof (float));
    float *initialY = (float*)malloc(L*sizeof(float));
    //generate sin wave with specific frequency
    int n_zeros_base = 0;
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
        //printf("[%.2f, %.2f], \n",initialX[i],initialY[i]);
        if(i > 0 && i < L-1)
        {
            if(initialY[i] <= 0 && initialY[i-1] >= 0)
            {
                n_zeros_base++;
            }
        }
    }
    printf("# training zeros: %d\n", n_zeros_base);
    int newL = 1000;
    float *predY = (float *)malloc(newL*sizeof(float));
    float *predX = (float *)malloc(newL*sizeof(float));
    //Keep start and end "time" values within those we've
    //set the spline to interpolate between
    float eval_end_t = 249.0;
    float eval_start_t = 1.0;
    for(int i = 0; i < newL; i++)
    {
        predX[i] = eval_start_t + ((eval_end_t-eval_start_t)/(newL))*i;
        predY[i] = 0;
    }
    CSpline_Interp(initialX, initialY, (unsigned int)L, predX, predY, (unsigned int)newL);
    int n_zeros_new = 0;
    for(int i = 0; i < newL; i++)
    {
        bool z = false;
        if(i > 0 && i < newL-1)
        {
            if(predY[i] <= 0 && predY[i-1] > 0)
            {
                n_zeros_new++;
                z = true;
            }
        }
        //printf("[%.2f, %.2f],",predX[i],predY[i]);

    }
    printf("# predicted zeros: %d", n_zeros_new);
}

void TestFFT()
{
    printf("Testing FFT functionality. Producing sine wave with T=0.09 Hz for t=256s @ 2 sample/s\nPeak should be at ~0.09 Hz bin\n");
    //This choice of period means the PSD peak will be at 0.09Hz!
    float T = 11.1111;
    float total_t = 256.0; //seconds of "total elapsed time"
    int L = 512; //how many samples for data
    float Hz_Max = (1.0*L)/total_t; //max sample rate, which determines max output freq
    float zeroval = 0;

    float *initialX = (float*)malloc(L*sizeof (float));
    float* initialY = (float*)malloc(L*sizeof(float));
    //generate sin wave with specific frequency
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
    }
    float* out_spec = (float *)malloc(L*sizeof(float));
    int out_len = 0;

    FFT_PSD(initialY,(unsigned)L,true,out_spec,&out_len);
    int max_b = 0;
    float max_val = 0;
    for(int i = 0; i < out_len/2; i++)
    {
        if(i > 2 && out_spec[i] > max_val)
        {
            max_val = out_spec[i];
            max_b = i;
        }
        //printf("%.2f %.2f\n",Hz_Max*(1.0*i)/(1.0*out_len),out_spec[i]);
    }
    printf("Peak at %.2f, with amplitude %.2f\n",Hz_Max*(1.0*max_b)/(1.0*out_len),max_val);
    printf("\n\n");
}