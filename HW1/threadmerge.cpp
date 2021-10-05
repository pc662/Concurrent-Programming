#include "mergesort.h"
#include <iostream>
#include <thread>

void mergeAllSections(int array[], int size, int* startIndexes, int* stopIndexes, int numberOfThreads) {
    
    //A for loop requires the max size to be minus one to account for 0 index
    int numberOfSections = numberOfThreads - 1;

    //Using a rolling merge, we take the first section to keep comparing and merging as the starting point
    for (int section = 0; section < numberOfSections; section++) {
        merge(array, startIndexes[0], stopIndexes[section], stopIndexes[section+1]);
    }

}



void tMergeSort(int array[], int size, int numberOfThreads) {


    //If there exists only one thread, use the classic mergeSort algorithm
    if (numberOfThreads == 1) {
        mergeSort(array, size);
        return;
    }

    

    //Creating the arrays to store the start, stop indexes and an array of threads
    int startIndexes[numberOfThreads];
    int stopIndexes[numberOfThreads];
    std::thread* threadArray = new std::thread[numberOfThreads];

    //Declaring the sizes of each section based upon the amount of threads provided. lastSectionSize is the size of the last section in the case of odd and even numbers.
    int sectionSize = size/numberOfThreads;
    int lastSectionSize = size/numberOfThreads + (size % numberOfThreads);


    int start;
    int stop;

    //Looping until the number of threads is reached to put the start, stop, and arrays into their proper places
    for (int i = 0; i < numberOfThreads; i++) {
        //If last section
        if (i == numberOfThreads - 1) {
            int start = size - lastSectionSize;
            int stop = size - 1;
            startIndexes[i] = start;
            stopIndexes[i] = stop;
            threadArray[i] = std::thread (mergeSort, (array + start), lastSectionSize);
            }
        else {
            int start = i * sectionSize;
            int stop = (i+1) * sectionSize - 1;
            startIndexes[i] = start;
            stopIndexes[i] = stop;
            threadArray[i] = std::thread (mergeSort, (array + start), sectionSize);
        }
    }

    //Telling the program to wait until the threads are finished
    for (int i = 0; i < numberOfThreads; i++) {
        threadArray[i].join();
    }

    //Combine all sections into one
    mergeAllSections(array, size, startIndexes, stopIndexes, numberOfThreads);
    return;

}