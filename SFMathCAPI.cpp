//
// Created by ttronrud on 2022-06-10.
//

#include "SFMathCAPI.h"
#include <iostream>

//Basic exposed method to make sure DLL is imported
//correctly
extern "C" __declspec(dllexport) void __stdcall SFMath_Hello()
{
    std::cout << "Hello!" << std::endl;
}

