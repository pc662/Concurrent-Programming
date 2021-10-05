#include "mandelbrot.h"
#include "colors.h"

int main(int argc, char** argv) {

	//Command line handling
	if (argc == 1 || argc > 6) {
		cout << "Usage: ./mandelbrot [minimum X] [maximum X] [minimum Y] [maximum Y] [output file]" << endl;
		return -1;
	}

	//Initialize the x and y values for command line passing
	long double minX;
    long double maxX;
	long double minY;
    long double maxY;


	//Error handling if given values are not numbers.
	//Also stores user input arguments as long doubles if no errors are found.
	try {
		minX = stold(argv[1]);
		maxX = stold(argv[2]);
		minY = stold(argv[3]);
		maxY = stold(argv[4]);
	} catch (std::invalid_argument e) {
		cout << "Invalid value type for values" << endl;
		return -1;
	}

	//Switching x values if one is greater than the other
	long double tempX;
	if (minX > maxX) {
		tempX = minX;
		minX = maxX;
		maxX = tempX;
	}
	//Switch y values if one is greater than the other
	long double tempY;
	if (minY > maxY) {
		tempY = minY;
		minY = maxY;
		maxY = tempY;
	}
	



	//Initial Setup
	int width = 1500;//pixels
	long double step = (maxX - minX)/width;	
    int height = (maxY - minY)/step;
	int dpi = 150;//pixel per inch



    //File name
    std::string filename= argv[5];  
	//The color part is taken from the example code
    //Open File
    std::ofstream image(filename,std::ios::binary);
    //Make the Bitmap Header
    writeHeader(image, height, width);
    writeDBI(image,height,width,dpi);

	//Number of pixels in the image and image array
	int pixels = height * width;

	unsigned char* red = new unsigned char[pixels];
	unsigned char* green = new unsigned char[pixels];
	unsigned char* blue = new unsigned char[pixels];

	//Create a vector to store mandelbrot values
    std::vector<int> mandelbrotVector(pixels);  

	//Using 8 threads
    int numberOfThreads = 8;
    std::thread* threadList = new std::thread[numberOfThreads];

	//Looping through threads to do their calculations
    for (int i = 0; i < numberOfThreads; i++) {
        threadList[i] = std::thread(insertIntoMandelbrot, std::ref(mandelbrotVector), pixels, minX, minY, step, numberOfThreads, i);
     }
	//Joining 8 threads
    for (int i = 0; i < numberOfThreads; i++) {
        threadList[i].join();
    }

	//Personal preference of colors. 
	//Each array has the same size, so to change the colors of a certain value, change the redColors, greenColors, or blueColors of the same index. 
	//I.e., index 0 is if the value is in the set. index 8 is if the value is very divergent. 
	unsigned char redColors[] = {  200, 25, 50, 75, 100, 125, 0, 5, 10, 15};
	unsigned char greenColors[] = { 0,  0,  0,   0,   0,   0, 0, 5, 10, 15};
	unsigned char blueColors[] = {  50, 25, 50, 75, 100, 125, 0, 5, 10, 15};

	//Setting pixels to be diff colors
	setColor(red,redColors,mandelbrotVector,pixels);
	setColor(green,greenColors,mandelbrotVector,pixels);
	setColor(blue,blueColors,mandelbrotVector,pixels);
	
	
	//Store all the Pixels into the file.
	writePixels(image,red,green,blue,pixels);
	//Close the File
	image.close();

	//End of main	
	return 0;
}



