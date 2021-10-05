#include "mergesort.h"
#include <iostream>

void merge(int arr[], int start, int middle, int stop)
{
    //Initiliazing and creating two temp arrays
    int firstHalfArraySize = middle - start + 1;
    int secondHalfArraySize = stop - middle;
    int firstHalfArray[firstHalfArraySize] = {};
    int secondHalfArray[secondHalfArraySize] = {};

    //copy over the data from the array starting at start and middle
    for (int i = 0; i < firstHalfArraySize; i++) {
        firstHalfArray[i] = arr[start + i];
    }
    for (int j = 0; j < secondHalfArraySize; j++) {
        secondHalfArray[j] = arr[middle + 1 + j];
    }

    //first half iterator
    int firstHalfIterator = 0;
    //second half iterator
    int secondHalfIterator = 0;
    //array iterator
    int arrayIterator = start;

    //rewrite the original array in increasing order by comparing the two temp array
    //while there is still something in the first and second arrays
    while (firstHalfIterator < firstHalfArraySize && secondHalfIterator < secondHalfArraySize) {

        //Compare the first element in the arrays to each other
        if (firstHalfArray[firstHalfIterator] <= secondHalfArray[secondHalfIterator]) {
            arr[arrayIterator] = firstHalfArray[firstHalfIterator];
            //increment the iterators
            firstHalfIterator++;
        }
        else {
            arr[arrayIterator] = secondHalfArray[secondHalfIterator];
            secondHalfIterator++;
        }
        //Moving to next element in merged array
        arrayIterator++;
    }


    //Check if any elements still in first half array and second half array
    while (firstHalfIterator < firstHalfArraySize || secondHalfIterator < secondHalfArraySize) {
        if (firstHalfIterator < firstHalfArraySize)
        {
            arr[arrayIterator] = firstHalfArray[firstHalfIterator];
            firstHalfIterator++;
        } else if (secondHalfIterator < secondHalfArraySize) {
            arr[arrayIterator] = secondHalfArray[secondHalfIterator];
            secondHalfIterator++;
        }
        arrayIterator++;
    }
    
}

void mSort(int array[], int start, int stop) {
    
    if (start < stop) {
        int middle = start + (stop - start)/2;
        mSort(array, start, middle);
        mSort(array, (middle + 1), stop);
        merge(array, start, middle, stop);
    }
}

void mergeSort(int array[], int arraySize) {
    mSort(array, 0, (arraySize - 1));
}