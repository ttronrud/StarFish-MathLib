cmake_minimum_required(VERSION 3.20)
project(SFMath)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(SFMathConsole)

add_library(SFMath SHARED SFMathCAPI.cpp SFMathCAPI.h FFT.cpp FFT.h complex.cpp complex.h SFMathConsole/SFMathConsole.cpp SFMathConsole/SFMathConsole.h)

