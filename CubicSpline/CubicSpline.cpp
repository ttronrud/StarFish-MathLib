//
// Created by ttronrud on 2022-06-10.
// Based on https://github.com/tomer953/cubic-spline
// Which is based on https://www.math.ntnu.no/emner/TMA4215/2008h/cubicsplines.pdf
//https://cse.engineering.nyu.edu/~mleung/CS3734/s03/ch07/cubicSpline.pdf
// and uses a double-derivative method to generate spline coefficients
//

#include <cstdlib>
#include "CubicSpline.h"
#include <iostream> //For debug priiints!

//Generates N-1 functions S(x) where
// S(x) = S_i(x-x_i) for x_i < x < x_i+1
// We'll use the numerical double-derivative of the data, ftt
CubicSpline::CubicSpline(float *xdat, float *ydat, unsigned int N)
{
    //h[i] is the dx between indices
    float *h = (float *)malloc((N-1)*sizeof(float ));
    //b[i] is dy between indices
    float *b = (float *)malloc((N-1)*sizeof(float ));
    //ftt is an estimation of S''(x_i), or the double-derivative of the function
    float *ftt = (float *)malloc((N)*sizeof(float ));
    //Here we allocate our object's variables
    coeffs = (float **)malloc((N-1)*sizeof(float *));
    xData = (float *)malloc(N*sizeof(float));
    yData = (float *)malloc(N*sizeof(float));
    datN = N-1;
    //Calculate dx and dy, while storing a copy of our input
    for(unsigned int i = 0; i < N-1; i++)
    {
        xData[i] = xdat[i];
        yData[i] = ydat[i];
        h[i] = (xdat[i+1] - xdat[i]);//dx
        b[i] = (ydat[i+1] - ydat[i]);//dy
    }
    //Set the edges
    xData[datN] = xdat[datN];
    yData[datN] = ydat[datN];
    ftt[0] = 0; //f''(0) = 0
    //Calculate z_i+1 (sectional second derivative) from our dx and dy values
    //This ends up being the change in dy (dy_i+1-dy_i) over x_i+2-x_i
    for(unsigned int i = 0; i < N-2; i++)
    {
        //Original source has a factor of 3 here that makes literally no difference,
        //besides making it impossible to motivate mathematically.
        //Now it's just a bog-standard 2nd derivative
        ftt[i+1] = (b[i+1]-b[i])/(h[i+1] + h[i]);
    }
    ftt[N-1] = 0; //f''(xn) = 0
    //now, the spline coeffs
    //From the double integral of S''_i(x) => S_i(x)
    for(unsigned int i = 0; i < N-1; i++)
    {
        //Allocate memory index to hold A,B,C, and D coeffs
        coeffs[i] = (float*)malloc(4*sizeof(float));
        coeffs[i][0] = (ftt[i+1]-ftt[i])/(6*h[i]); //A
        coeffs[i][1] = ftt[i]/2; //B
        coeffs[i][2] = b[i] - h[i]*(ftt[i+1] + 2*ftt[i])/6; //C
        coeffs[i][3] = ydat[i]; //D
    }
    free(ftt);
    free(b);
    free(h);
}

float CubicSpline::Interpolate(float x)
{
    float newY = 0.0f;
    float h = 0.0f;
    int guess_i = 0;
    //Boundary conditions -
    //We'll just extrapolate !!!*UNSAFE*!!! because that's all we can do
    if(x > xData[datN-1])
    {
        h = x-xData[datN-1];
        newY = coeffs[datN-1][3] + coeffs[datN-1][2]*h + coeffs[datN-1][1]*h*h + coeffs[datN-1][0]*h*h*h;
    }
    else if(x < xData[0])
    {
        h = x-xData[0];
        newY = coeffs[0][3] + coeffs[0][2]*h + coeffs[0][1]*h*h + coeffs[0][0]*h*h*h;
    }
    else
    {
        //find a guess for initial index to hunt from
        //Initial assumption of even spacing (which we adjust later!)
        guess_i = x/xData[datN]*datN - 1;
        if(guess_i < 0)
            guess_i = 0;
        else if(guess_i > datN-1)
            guess_i = datN-1;

        //check that value at initial guess is < x
        //Since we need our knot to precede x
        while(xData[guess_i] > x && guess_i > 0)
        {
            guess_i--; //decrement backwards until we've fixed the problem
        }
        //Start at that guess, and see if x_i <= x < x_i+1
        //if so, we use those coefficients to calculate the interpolated value
        for(int i = guess_i; i < datN; i++)
        {
            if(x >= xData[i] && x < xData[i+1])
            {
                h = x - xData[i];
                newY = coeffs[i][3] + coeffs[i][2]*h + coeffs[i][1]*h*h + coeffs[i][0]*h*h*h;
                break;
            }
        }
        //we didn't find it from the guess
    }

    return newY;
}
