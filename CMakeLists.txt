cmake_minimum_required(VERSION 3.20)
project(SFMath)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(FFT)

add_subdirectory(SFMathConsole)

add_library(SFMath SHARED SFMathCAPI.cpp SFMathCAPI.h FFT/FFT.cpp FFT/FFT.h FFT/complex.cpp FFT/complex.h FFT/FFT_CAPI.cpp FFT/FFT_CAPI.h)
add_library(SFMath_STAT STATIC SFMathCAPI.cpp SFMathCAPI.h FFT/FFT.cpp FFT/FFT.h FFT/complex.cpp FFT/complex.h FFT/FFT_CAPI.cpp FFT/FFT_CAPI.h)

