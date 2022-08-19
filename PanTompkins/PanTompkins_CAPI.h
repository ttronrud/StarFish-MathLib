//
// Created by ttronrud on 2022-08-19.
//

#ifndef SFMATH_PANTOMPKINS_CAPI_H
#define SFMATH_PANTOMPKINS_CAPI_H

#include "PanTompkins.h"

extern "C" {
    SFMATH_EXPORT void __stdcall RunPanTompkins(dataType *signal_data, int len_signal_data);
};



#endif //SFMATH_PANTOMPKINS_CAPI_H
