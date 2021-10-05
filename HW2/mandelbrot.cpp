#include "mandelbrot.h"

//This code is taken from the lecture slides of week 2
int mandelbrotComputation(long double x, long double y, int threshold) {
    //Create the values
    std::complex<long double> c(x, y);
    std::complex<long double> current(0, 0);

    //Run iteratively
    for (int i = 0; i < threshold; i++) {
        current = current * current + c;
        if (std::abs(current) > 4) {
            return i;
        }
    }
    //Never got above 4
    return threshold;
}


//Using the logic presented in lecture, this function uses the formulas given to compute the mandelbrot values.
//Also takes into account that the work the threads do is i mod the number of threads
void insertIntoMandelbrot(std::vector<int> &mandelbrotSet,int sizeOfVector, long double x1, long double y1, long double step, int numberOfThreads, int remainder) {

    for (int i = 0; i < sizeOfVector; i++) {
        //Determines how to divy up the work between threads
        if ( i % numberOfThreads == remainder) {
            long double x = x1 + ((i % 1500) * step);
            long double y = y1 + ((i/1500) * step);
            mandelbrotSet[i] = mandelbrotComputation(x, y, 100);
        }
}
}


