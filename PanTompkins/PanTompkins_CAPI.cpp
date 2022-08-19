//
// Created by ttronrud on 2022-08-19.
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "../SFMathCAPI.h"
#include "PanTompkins_CAPI.h"
#include "PanTompkins.h"
#include <vector>

extern "C" {
    SFMATH_EXPORT void __stdcall RunPanTompkins(dataType *signal_data, int len_signal_data)
    {
        long int *r_bins = (long int*)malloc(1000*sizeof (long int));
        init(signal_data, len_signal_data, false, r_bins, 1000);
        panTompkins();
        //first element is end index
        printf("N = %lu\n",r_bins[0]);
        for(int i = 1; i < 1000; i++)
        {
            if(i > r_bins[0])
                break;
            printf("%lu\n",r_bins[i]);
        }
        return;
    }
};


