//
// Created by ttronrud on 2022-06-10.
//

#include "SFMathCAPI.h"
#include <stdio.h>
#include <iostream>
extern "C" __declspec(dllexport) void __stdcall Hello()
{
    std::cout << "Hello!" << std::endl;
}