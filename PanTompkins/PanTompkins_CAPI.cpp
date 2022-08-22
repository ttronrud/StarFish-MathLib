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
        int *r_bins = (int*)malloc(len_signal_data*sizeof (int));
        init(signal_data, len_signal_data, r_bins);
        panTompkins();
        //first element is end index
        for(int i = 0; i < len_signal_data; i++)
        {
            if(r_bins[i] > 0)
                printf("%d\n",i);
        }
        return;
    }
};

