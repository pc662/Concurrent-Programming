#ifndef _MANDELBROT_H_
#define _MANDELBROT_H_

#include <iostream>
#include <complex>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::stold;

//Computation of the mandelbrot set
int mandelbrotComputation(long double x, long double y, int threshold);

//Populate the mandelbrot array
void insertIntoMandelbrot(std::vector<int> &mandelbrotSet,int sizeOfVector, long double x1, long double y1, long double step, int numberOfThreads, int remainder);

#endif


