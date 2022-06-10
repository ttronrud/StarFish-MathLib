//
// Created by ttronrud on 2022-06-10.
//

#include <cstdlib>
#include <cstdio>
#include "SFMathConsole.h"
#include "../SFMathCAPI.h"
#include <iostream>

int main(int argc, char * argv[])
{
    //Hello();

    float T = 11.1111;
    float total_t = 256.0; //seconds of "total elapsed time"
    int L = 256; //how many samples for data
    float zeroval = 1.25;

    float *initialX = (float*)malloc(L*sizeof (float));
    float* initialY = (float*)malloc(L*sizeof(float));
    //generate sin wave with specific frequency
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
        //printf("[%.2f, %.2f] ,",initialX[i], initialY[i]);
    }
    float* out_spec = (float *)malloc(L*sizeof(float));
    int out_len = 0;

    FFTSpectrum(initialY,(unsigned)L,true,out_spec,&out_len);

    std::cout << out_spec << std::endl;
    std::cout << out_len << std::endl;
    //std::cout << "Done FFT" << std::endl;
    for(int i = 0; i < out_len/2; i++)
    {
        printf("%.2f %.2f\n",(1.0*i)/(1.0*out_len),out_spec[i]);
    }

    return 0;
}