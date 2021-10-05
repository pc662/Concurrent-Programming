#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <chrono>
#include "mergesort.h"
#include "threadmerge.h"

using std::string;
using std::cout;
using std::endl;
using std::stoi;
using std::ifstream;
using std::vector;
using std::stringstream;
using std::ofstream;

//Helper function to determine if a string contains only digits
bool is_digits(const string &str);

bool is_digits(const string &str) {
    return std::all_of(str.begin(), str.end(),::isdigit);
}

int main(int argc, char** argv) {

    int opt;
    string inputFileName;
    string outputFileName;
    vector<int> integerStorage; 
    int numberOfThreads = 1;

    //Looks for any optional flags if available
    while ((opt = getopt(argc, argv, "i:o:t:")) != -1) {

        switch (opt) {

            //i flag option to input files
            case 'i': {
                inputFileName = optarg;
                
                //Open up a file
                ifstream inFile(optarg);
                
                if (inFile) 

                    {
                    int value;

                    //Parsing elements of the input file
                    while (inFile >> value) 
                        {
                        integerStorage.push_back(value);
                        }

                    }

                //If file is not found 
                else 
                
                {
                    cout <<"Enter a valid file name."<< endl;
                    cout << "Usage: ./mergesort -i [filename] -o [filename] -t [number of threads]" << endl;
                    return -1;
                }
                inFile.close();
                break;
                }

            //o flag to output results into a file
            case 'o':
                outputFileName = optarg;
                break;

            //t flag that represents the amount of threads
            case 't':
                //If user enters a non number, it'll catch the error and set threads to 1
                try {
                    numberOfThreads = stoi(optarg);
                } catch (std::invalid_argument e) {
                    numberOfThreads = 1;
                }

                //If the number of threads specified is not in range of 1-20, number of threads will default back to 1
                if (!((numberOfThreads >= 1) && (numberOfThreads <=20))) {
                    numberOfThreads = 1;
                }
                break;

            //If flag is unrecognized, print the usage
            case '?':
                cout << "Wrong flag" << endl;
                cout << "Usage: ./mergesort -i [filename] -o [filename] -t [number of threads]" << endl;
                return -1;

        }

    }

    if ( (argc = 1) && (opt == (-1))) {

        //Check if vector is empty or not
        //If empty, then prompt user to type in the numbers 
        if (integerStorage.empty()) {
            string userInput;
            cout << "Please enter numbers. Separate numbers by spaces:" << endl;
            getline(std::cin, userInput);
            
            //Using stringstream to parse integerStorage
            stringstream stream(userInput);
            int n;
            while (stream >> n) {
                integerStorage.push_back(n);
            }
        }

        //If vector is not empty, proceed to convert vector into array

        int array[integerStorage.size()];
        std::copy(integerStorage.begin(), integerStorage.end(), array);
        int arraySize = sizeof(array)/sizeof(array[0]);

        
        //Make sure that if thread is greater than array size, reduce thread size to size
        if (numberOfThreads > arraySize) 
             {
             numberOfThreads = arraySize;
             }

        //Tell the user how many threads are being used
        cout<< "Using " << numberOfThreads << " threads." << endl;


        //Creating the timer variables
        auto start = std::chrono::high_resolution_clock::now();
        tMergeSort(array, arraySize, numberOfThreads);
        auto end = std::chrono::high_resolution_clock::now();

        double time_taken = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
 
        //If there is no supplied output file name, then print the array out into console
        if (outputFileName.empty()) {
            for (int index = 0; index < arraySize; index++) {
                cout << array[index] << endl;
            }
        } 

        //If there is a supplied output file name, then print the results into that file
        else {
            ofstream outFile(outputFileName);
            for (int index = 0; index < arraySize; index++) {
                outFile << array[index] << endl;
            }
            outFile.close();
        }


        //Display how long the sorting took
        cout << "Sorting " << arraySize << " items took " 
            << time_taken << " microseconds." << endl;
        return 0;

    }
}