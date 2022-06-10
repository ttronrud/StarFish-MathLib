//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCAPI_H
#define SFMATH_SFMATHCAPI_H

//Here is an example, to demonstrate how to define the CAPI for access from the DLL
extern "C" {
    __declspec(dllexport) void __stdcall SFMath_Hello(); //Our text exposed method to print to console
};


#endif //SFMATH_SFMATHCAPI_H
