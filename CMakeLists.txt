cmake_minimum_required(VERSION 3.20)
project(SFMath)

set(CMAKE_CXX_STANDARD 14)
add_subdirectory(FFT)
add_subdirectory(CubicSpline)
add_subdirectory(PanTompkins)


add_library(SFMath SHARED SFMathCAPI.cpp FFT/cppFFT.cpp FFT/complex.cpp FFT/FFT_CAPI.cpp CubicSpline/CubicSpline.cpp CubicSpline/CubicSpline_CAPI.cpp PanTompkins/PanTompkins.cpp PanTompkins/PanTompkins.h PanTompkins/PanTompkins_CAPI.cpp PanTompkins/PanTompkins_CAPI.h)
add_library(SFMath_STAT STATIC SFMathCAPI.cpp FFT/cppFFT.cpp FFT/complex.cpp FFT/FFT_CAPI.cpp CubicSpline/CubicSpline.cpp CubicSpline/CubicSpline_CAPI.cpp PanTompkins/PanTompkins.cpp PanTompkins/PanTompkins.h PanTompkins/PanTompkins_CAPI.cpp PanTompkins/PanTompkins_CAPI.h)

add_subdirectory(SFMathConsole)
