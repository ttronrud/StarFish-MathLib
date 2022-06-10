StarFish Medical Math Library!

The beginning of a multi-purpose StarFish math library that we can use as a heavily-documented, efficient, fast, non-SOUP-y plugin.
The main goal will be to write the library in C++, generate a C DLL, and provide a C# interface file that can be added to any DotNet
project to expose the math functions to the higher-level program.

How to contribute:
1. Implement the methods that you want to include in a self-contained manner, as new cpp/h files, ideally named by
the method (e.g. FFT.cpp/h), in a new folder named [method].
2. Create the exposed interface methods in [method]/[method]_CAPI.cpp/h. Make sure to include the
"extern "C" __declspec(dllexport) void __stdcall" prefix. Here are some proposed "best practices":
    2a. The exposed methods should return "void" type, and instead provide their results by reference, through
        pointer arguments. These pointers should be defined/allocated by the caller, and I think it would be good
        practice to include methods to predict the number of items it will be necessary to allocate beforehand.
    2b. To prevent the exposed methods from colliding with each other, they should be named with the format
        [method]_[name], e.g. FFT_PredictN, FFT_PSD.
    2c. I think it would also be good practice to restrict input(/output by ref) parameters to native C/C++ types
        so no extra inclusions are necessary in programs that depend on this DLL.
    2d. Your CAPI implementation can contain as much handling as you need to make the native-type inputs the correct
        types required by the actual math methods (e.g. float -> complex_f in FFT).
This means your inclusion should be 4 files minimum - [method]/[method].cpp/h, and [method]/[method]_CAPI.cpp/h!

3. Finally, ensure that your new methods are added to the CMakeLists.txt "add_library" statement, so they will be
properly added to the DLL.
4. It would probably also be good to create an additional [method]/CMakeLists.txt, following the pattern in "FFT".
This will generate an additional single library with only the method-specific exposures, which could be useful in cases
where there's only one set of functions that we want out of the entire library.

