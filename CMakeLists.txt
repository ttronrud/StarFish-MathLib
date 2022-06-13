cmake_minimum_required(VERSION 3.20)
project(SFMath)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(FFT)
add_subdirectory(CubicSpline)


add_library(SFMath SHARED SFMathCAPI.cpp FFT/FFT.cpp FFT/complex.cpp FFT/FFT_CAPI.cpp CubicSpline/CubicSpline.cpp CubicSpline/CubicSpline_CAPI.cpp)
add_library(SFMath_STAT STATIC SFMathCAPI.cpp FFT/FFT.cpp FFT/complex.cpp FFT/FFT_CAPI.cpp CubicSpline/CubicSpline.cpp CubicSpline/CubicSpline_CAPI.cpp)

add_subdirectory(SFMathConsole)
