//
// Created by ttronrud on 2022-08-19.
//

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include "../SFMathCAPI.h"
#include "PanTompkins_CAPI.h"
#include <vector>

extern "C" {
    SFMATH_EXPORT void __stdcall RunPanTompkins(double *signal_data, int len_signal_data)
    {
        int *r_bins = (int*)malloc(len_signal_data*sizeof (int));
        PanTompkins::PanTompkins_init();
        //first element is end index
        for(int i = 0; i < len_signal_data; i++)
        {
            if(PanTompkins::PanTompkins_SingleStep(signal_data[i]))
                printf("%d\n",i-PanTompkins::DELAY);
        }
        return;
    }
    SFMATH_EXPORT void __stdcall PanTompkinsInit()
    {
        PanTompkins::PanTompkins_init();
    }
    SFMATH_EXPORT bool __stdcall PanTompkins_SingleStep(double signal_datum)
    {
        return PanTompkins::PanTompkins_SingleStep(signal_datum);
    }
};

