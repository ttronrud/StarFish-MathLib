//
// Created by ttronrud on 2022-06-10.
// THIS IS A TESTING PROGRAM - It depends on the SFMath methods
//

#include <cstdlib>
#include <cstdio>
#include <fstream>
#include "SFMathConsole.h"
#include <iostream>
#include <vector>

int main()
{
    //SFMath_Hello();
    //TestFFT();
    //TestCSpline();
    //ComboCSplineFFTTest();
    //RRPracticeTest();
    ECG2RPractice();
    return 0;
}

void ECG2RPractice()
{
    FILE *file;
    file = fopen("ECG.txt", "r");
    int alloc_size = 3500;
    char buffer[16];
    std::vector<int> ECGPractice;
    ECGPractice.reserve(alloc_size);
    while(fgets(buffer,16,file)!=NULL && ECGPractice.size() < alloc_size)
    {
        int tmp = std::atoi(buffer);
        //std::cout << tmp << std::endl;
        ECGPractice.push_back(tmp);
    }
    fclose(file); //close file

    RunPanTompkins(ECGPractice.data(), alloc_size);
}

//Shows an example of reading in a list of R-R intervals
//Using a spline to re-sample the data,
//And calculation of the power spectrum
void RRPracticeTest()
{
    FILE *file;
    file = fopen("RRs.txt", "r");
    char buffer[16];
    int st = 75000;
    float recording_time = 128; //seconds
    int alloc_size = 250;
    int N;
    int i = 0;
    //malloc because I'm a C boi
    double *RRs = (double*)malloc(alloc_size*sizeof(double));
    double *T = (double *)malloc(alloc_size*sizeof(double));
    float t = 0;
    int _reali = 0;
    //Read through the RR list,
    //cumulative time T is our x-axis for spline fitting
    //we're pretending there's a recording "time" limit,
    //which we check in our loop
    while(fgets(buffer,16,file)!=NULL && t < recording_time && i < alloc_size)
    {
        //Skip ahead to starting index
        if(_reali < st)
        {
            _reali++;
            continue;
        }
        RRs[i] = std::atof(buffer);
        t += RRs[i]; //add to total time
        T[i] = t;
        i++;
    }
    fclose(file); //close file
    N = i; //The number of intervals

    //now, spline fit//
    //We'll resample at 1Hz
    //so our array length will be the number of seconds
    int L = int(t);
    //And our PSD window will be 64 second chunks
    int window_size = 64;
    //and allocate the spline X and Y arrays
    double *splX = (double *)malloc(L*sizeof(double));
    double *splY = (double *)malloc(L*sizeof(double));
    //Now, we add our evenly-spaced spline X points
    //and we'll just zero our spline Y, so that no weird shit happens
    for(i = 0; i < L; i++)
    {
        //For the default values (where L = int(t)), we just need 1.0*i for our time.
        //if you want to split more finely, however, you'll need the t/L term to normalize end time
        splX[i] = 1.0*i*t/L; //how much of the total time -- since we're sticking to one per second, up to the int
                    //      value of t, we can just use index as x domain
        splY[i] = 0; //just zero this array
    }
    //Run our spline interpolation!
    //This takes the unevenly-sampled RR data, fits a spline between the points,
    //and resamples at even time steps, which makes the data valid for an FFT!
    CSpline_Interp(T, RRs, (unsigned int)N, splX, splY, (unsigned int)L);

    //Now, the output spectrum, and the total spectrum
    //technically, the maximum number of bins will be the closest power of 2 to window_size
    //since our window_size *is* a power of two,
    //we'll just save window_size for total spec
    double* tot_spec = (double *)malloc((window_size)*sizeof(double));
    //zero this array
    for(int m = 0; m < window_size/2; m++)
    {
        tot_spec[m] = 0;
    }
    //Create a new array for the subsample of the spline in the window
    int out_len = 0;

    //try with our PSD windows method
    FFT_PSD_windows(splY, L, window_size, true,  tot_spec, &out_len);

    std::cout << out_len << std::endl;
    std::cout << "total t = " << t << std::endl;
    std::cout << "#bins/total t = Hz = " << (L/t) << std::endl;
    //FFT frequency range is based on the sampling frequency of the input data,
    //which is array length divided by the time domain extent (L/t, in this case)
    //The bins will be evenly spaced up to this max frequency
    float Hz_Max = (1.0*L)/(t); //max output frequency
    for(int i = 0; i < window_size/2; i++)
    {
        printf("[%.5f, %.5f],\n",Hz_Max*(1.0*i)/(1.0*window_size),tot_spec[i]);
    }
    //free everything
    free(RRs);
    free(T);
    free(splX);
    free(splY);
    free(tot_spec);

}
void ComboCSplineFFTTest()
{
    printf("Beginning CSpline generation. Going from 256s sine wave w/T=5.0s, Nsamp = 250\nto interpolate 1k values between t=(0,249).\n");
    float T = 5;
    float total_t = 2048.0; //seconds of "total elapsed time"
    int L = (int)(total_t*2/3); //how many samples for data
    float zeroval = 0.;

    double *initialX = (double*)malloc(L*sizeof (double));
    double *initialY = (double*)malloc(L*sizeof(double));
    //generate sin wave with specific frequency
    int n_zeros_base = 0;
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = 2.1 * sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
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
    int newL = total_t;
    double *predY = (double *)malloc(newL*sizeof(double));
    double *predX = (double *)malloc(newL*sizeof(double));
    //Keep start and end "time" values within those we've
    //set the spline to interpolate between
    float eval_end_t = total_t;
    float eval_start_t = 0.0;
    for(int i = 0; i < newL; i++)
    {
        predX[i] = eval_start_t + ((eval_end_t-eval_start_t)/(newL))*i;
        predY[i] = 0;
    }
    CSpline_Interp(initialX, initialY, (unsigned int)L, predX, predY, (unsigned int)newL);

    double* out_spec = (double *)malloc(newL*sizeof(double));
    int out_len = 0;
    unsigned window_size = 128;
    //FFT_PSD(predY,(unsigned)newL,true,out_spec,&out_len);
    FFT_PSD_windows(predY, (unsigned)newL, window_size, true, out_spec, &out_len);
    int max_b = 0;
    float max_val = 0;
    float Hz_Max = (1.0*newL)/(eval_end_t-eval_start_t); //max sample rate, which determines max output freq
    for(int i = 0; i < out_len/2; i++)
    {
        if(i > 2 && out_spec[i] > max_val)
        {
            max_val = out_spec[i];
            max_b = i;
        }
        printf("[%.3f, %.3f],\n",Hz_Max*(1.0*i)/(1.0*out_len),out_spec[i]);
    }
    printf("Peak at %.3f, with amplitude %.3f\n",Hz_Max*(1.0*max_b)/(1.0*out_len),max_val);
    printf("\n\n");

    free(initialX);
    free(initialY);
    free(predY);
    free(predX);
    free(out_spec);
}

void TestCSpline()
{
    printf("Beginning CSpline test. Going from 250s sine wave w/T=24.0s, Nsamp = 250\nto interpolate 1k values between t=(1,249).\nExpected # of zeros should both = 10\n");
    float T = 24.0;//11.1111;
    float total_t = 250.0; //seconds of "total elapsed time"
    int L = 250; //how many samples for data
    float zeroval = 0.25;

    double *initialX = (double*)malloc(L*sizeof (double));
    double *initialY = (double*)malloc(L*sizeof(double));
    //generate sin wave with specific frequency
    int n_zeros_base = 0;
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = 2.1 * sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
        printf("[%.2f, %.2f], \n",initialX[i],initialY[i]);
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
    double *predY = (double *)malloc(newL*sizeof(double));
    double *predX = (double *)malloc(newL*sizeof(double));
    //Keep start and end "time" values within those we've
    //set the spline to interpolate between
    double eval_end_t = 249.0;
    double eval_start_t = 1.0;
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
        printf("[%.2f, %.2f],\n",predX[i],predY[i]);

    }
    printf("# predicted zeros: %d", n_zeros_new);

    free(initialX);
    free(initialY);
    free(predY);
    free(predX);
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

    double *initialX = (double*)malloc(L*sizeof (double));
    double* initialY = (double*)malloc(L*sizeof(double));
    //generate sin wave with specific frequency
    for(int i = 0; i < L; i++)
    {
        initialX[i] = (total_t/L)*i; //X is the time, in the HRV implementation. We're using constant time.
        initialY[i] = sin(2*3.14159*initialX[i]/T) + zeroval; //shift all positive
    }
    double* out_spec = (double *)malloc(L*sizeof(double));
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

    free(initialX);
    free(initialY);
    free(out_spec);
}