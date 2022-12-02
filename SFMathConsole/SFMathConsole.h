//
// Created by ttronrud on 2022-06-10.
//

#ifndef SFMATH_SFMATHCONSOLE_H
#define SFMATH_SFMATHCONSOLE_H

//Functions imported from DLL
extern "C"
{
    //DLL Import of FFT_PSD from DLL

    //These two exposed methods are probably the most useful -- the power spectrum density windows,
    //and the spline interpolation.
    //
    //For the FFT_PSD_windows, the data, length, window_size, and use_hanning are inputs.
    //For an FFT, the window size must be a power of 2, and only a chunk of data divisible
    //by this size will be used (handled by integer division in the FFT_CAPI file).
    //The output data length is window_size long, and should be alloc'd before being provided to
    //the method.
    __declspec(dllimport) void __stdcall FFT_PSD_windows(double *data, unsigned int data_len, unsigned int window_size, bool use_hanning, double *out_data, int*out_data_len);
    //The spline interpolation method takes known X and Y coordinates, of length N,
    //and a pointer to an already-alloc'd set of new X values (intXs) for which to
    //predict Y values based on the spline. NPreds must be less than or equal to the length of predYs.
    __declspec(dllimport) void __stdcall CSpline_Interp(double *X, double*Y, unsigned int N, double *intXs, double *predYs, unsigned int NPreds);

    //Other methods
    __declspec(dllimport) void __stdcall FFT_PSD(double *data, unsigned int data_len, bool use_hanning, double *out_data, int*out_data_len);
    __declspec(dllimport) void __stdcall SFMath_Hello();
    __declspec(dllimport) void __stdcall RunPanTompkins(double *signal_data, int len_signal_data);
    __declspec(dllimport) bool __stdcall PanTompkins_SingleStep(double signal_datum);
    __declspec(dllimport) void __stdcall PanTompkinsInit();

};

//Test functions
void TestFFT();
void TestCSpline();
void ComboCSplineFFTTest();
void RRPracticeTest();
void ECG2RPractice();
#endif //SFMATH_SFMATHCONSOLE_H
