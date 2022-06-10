//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCAPI_H
#define SFMATH_SFMATHCAPI_H
#define SFMATH_EXPORT __declspec(dllexport)

//Here is an example, to demonstrate how to define the CAPI for access from the DLL
extern "C" {
    SFMATH_EXPORT void __stdcall SFMath_Hello(); //Our text exposed method to print to console
};


#endif //SFMATH_SFMATHCAPI_H
