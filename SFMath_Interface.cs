/*
Example C# interface for SFMath.dll
*/

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Threading.Tasks;

namespace SFMath_Interface
{
    /*
     * SFMath Interface class for implementing the C++ library consistently
     */
    public class SFAI_Interface
    {
        /*
         * External reference to "Hello" test method in SFMath.DLL
         */
        [DllImport(@"SFMath.dll")]
        public static extern void SFMath_Hello();
        //CSpline Methods
        [DllImport(@"SFMath.dll")]
        public static extern void CSpline_Interp(float[] X, float[] Y, unsigned int N, float[] intXs, float[] predYs, unsigned int NPreds);
        [DllImport(@"SFMath.dll")]
        public static extern void CSpline_Coeffs(float[] X, float[] Y, unsigned int N, float[][] coeffs);
        //FFT Methods
        [DllImport(@"SFMath.dll")]
        public static extern void FFT_PredictN(unsigned int data_len, IntPtr out_data_len);
        [DllImport(@"SFMath.dll")]
        public static extern void FFT_PSD(float[] data, unsigned int data_len, bool use_hanning, float[] out_data, IntPtr out_data_len);
        [DllImport(@"SFMath.dll")]
        public static extern void FFT_Spectrum(float[] data_re, float[] data_im, unsigned int data_len, bool use_hanning, float[] out_data_re, float[] out_data_im, IntPtr out_len);

        //Example interface function to call a SFMath method and get the output-by-reference result
        public static unsigned int FFT_PredictN_Example(unsigned int data_length)
        {
            //Allocate integer pointer
            IntPtr odatlen = Marshal.AllocHGlobal(sizeof(int));
            //Use as int* for method
            FFT_PredictN(data_length, odatlen);
            //Not sure if it's uint32 or not, but anyway...
            return (unsigned int)Marshal.ReadUInt32(odatlen);

        }
    }
}
