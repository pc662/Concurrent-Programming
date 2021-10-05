#ifndef _COLORS_H_
#define _COLORS_H_

#include <iostream>
#include <complex>
#include <string>
#include <fstream>
#include <thread>
#include <vector>

//Write Header of a Bitmap Image
void writeHeader(std::ofstream &image, int height, int width);
//Write DBI header of a Bitmap Image
void writeDBI(std::ofstream &image, int height, int width, int dpi);
//Write Pixels from a collection of arrays
void writePixels(std::ofstream &image,
	unsigned char* red,
	unsigned char* green,
	unsigned char* blue,
	int pixels);

//Break an integer into individual bytes
char getByte(int value, int byte);
//Dots per inch to pixels per meter
int dpiToPPM(int dpi);
//Set every value in an array to be the same
void setColor(unsigned char* array, unsigned char* color, std::vector<int> &mandelbrotValue, int pixels);

#endif