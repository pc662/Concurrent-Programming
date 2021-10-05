#include "colors.h"

//Most of this code is taken from the example slides. setColors is adjusted to set colors based on the values of the mandelbrot calculations

char getByte(int value, int byte)
{
	int newValue = value;
	
	unsigned char rem;
	for(int i=0; i <= byte; i++)
	{
		rem = static_cast<unsigned char>( newValue%256 );
		newValue = newValue/256;
	}
	return rem;
}

//Convesion
//x pixels/inches * C inches/meter = y pixels/meter
int dpiToPPM(int dpi)
{
	float inchesPerMeter = 39.3701/1;
	float convert = dpi*inchesPerMeter;
	return static_cast<int>(convert);
}

void writeHeader(std::ofstream &image, int height, int width)
{
	//How many pixel does the image have
	int pixels = height*width;
	//Make the header. It is always 14 bytes
	int headerSize = 14;
	//Array to store the header
	char* header = new char[headerSize];
	//The header is 14 Bytes
	//The DBI is 40 bytes
	int offset = headerSize + 40;
	//Each Pixel is another 3 bytes
	int totalBits = pixels*3+offset;
	//Make the Header
	//First 2 Bytes are BM for bitmap
	header[0] = 'B';
	header[1] = 'M';
	//Next 4 bytes are the total size of the file
	header[2] = getByte(totalBits,0);
	header[3] = getByte(totalBits,1);
	header[4] = getByte(totalBits,2);
	header[5] = getByte(totalBits,3);
	//Next for bits are 0 (reserved for other uses)
	header[6] = 0;
	header[7] = 0;
	header[8] = 0;
	header[9] = 0;
	//Last 4 bytes are offset
	//Where do the pixels start
	header[10] = getByte(offset,0);
	header[11] = getByte(offset,2);
	header[12] = getByte(offset,2);
	header[13] = getByte(offset,3);
	//Write the Header to the file in binary
	image.write(header, headerSize);
	//Exit the Function
	return;
}

//Using the BITMAPINFOHEADER standard
void writeDBI(std::ofstream &image, int height, int width, int dpi)
{
	//Convert DPI to Pixels Per Meter
	int resolution = dpiToPPM(dpi);
	//Fixed Size of 40 Bytes
	int sizeDBI = 40;
	//Make array of bytes
	char* DBI = new char[sizeDBI];
	//Set Values
	//First 4 bytes are header size of this header (40)
	DBI[0] = getByte(40,0);
	DBI[1] = getByte(40,1);
	DBI[2] = getByte(40,2);
	DBI[3] = getByte(40,3);
	//Bitmap Width (4 bytes)
	DBI[4] = getByte(width,0);
	DBI[5] = getByte(width,1);
	DBI[6] = getByte(width,2);
	DBI[7] = getByte(width,3);
	//Height (4 bytes)
	DBI[8] = getByte(height,0);
	DBI[9] = getByte(height,1);
	DBI[10] = getByte(height,2);
	DBI[11] = getByte(height,3);
	//Color Plane (2 bytes) is always 1
	DBI[12] = 1;
	DBI[13] = 0;
	//Color Depth (2 bytes) we are using 24 (three 8 bit colors)
	DBI[14] = getByte(24,0);
	DBI[15] = getByte(24,1);
	//Compression (4 bytes) 0 means none
	DBI[16] = 0;
	DBI[17] = 0;
	DBI[18] = 0;
	DBI[19] = 0;
	//Uncompressed Size (4 bytes)
	//0 because we aren't using compression
	DBI[20] = 0;
	DBI[21] = 0;
	DBI[22] = 0;
	DBI[23] = 0;
	//Horizontal Resolution (4 bytes)
	//Pixel per meter
	DBI[24] = getByte(resolution, 0);
	DBI[25] = getByte(resolution, 1);
	DBI[26] = getByte(resolution, 2);
	DBI[27] = getByte(resolution, 3);
	//Vertical Resolution (4 bytes)
	//Pixel per meter
	DBI[28] = getByte(resolution, 0);
	DBI[29] = getByte(resolution, 1);
	DBI[30] = getByte(resolution, 2);
	DBI[31] = getByte(resolution, 3);
	//Color Pallet (4 bytes)
	//0 means all
	DBI[32] = 0;
	DBI[33] = 0;
	DBI[34] = 0;
	DBI[35] = 0;
	//Number of important colors
	//0 mean all equal
	DBI[36] = 0;
	DBI[37] = 0;
	DBI[38] = 0;
	DBI[39] = 0;
	//Write the Header to the file in binary
	image.write(DBI, sizeDBI);
	//Exit the Function
	return;
}

void writePixels(std::ofstream &image,
	unsigned char* red,
	unsigned char* green,
	unsigned char* blue,
	int pixels)
{
	char* pixel = new char[3];
	for(int i=0; i < pixels; i++)
	{
		pixel[2] = red[i];
		pixel[1] = green[i];
		pixel[0] = blue[i];
		image.write(pixel, 3);
	}
	return;
}


void setColor(unsigned char* colorArray, unsigned char* color, std::vector<int> &mandelbrotVector, int pixels)
{
	for(int i=0; i < pixels; i++)
	{
		if (mandelbrotVector[i] == 100) {
            colorArray[i] = color[0];
        }  else if (mandelbrotVector[i] > 90) {
            colorArray[i] = color[1];
        } else if (mandelbrotVector[i] > 80) {
            colorArray[i] = color[2];
        } else if (mandelbrotVector[i] > 70) {
            colorArray[i] = color[3];
        } else if (mandelbrotVector[i] > 50) {
            colorArray[i] = color[4];
        } else if (mandelbrotVector[i] > 30) {
            colorArray[i] = color[5];
        } else if (mandelbrotVector[i] > 20) {
            colorArray[i] = color[6];
        } else if (mandelbrotVector[i] > 10) {
            colorArray[i] = color[7];
        } else if (mandelbrotVector[i] > 4) {
            colorArray[i] = color[8];
        } else {
            colorArray[i] = color[9];
        }
	}
}