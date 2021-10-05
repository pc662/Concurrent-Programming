#ifndef _MERGE_SORT_
#define _MERGE_SORT_

//Main merge function to merge arrays back together
void merge(int arr[], int start, int middle, int stop);

//Helper function which splits the arrays recursively
void mSort(int array[], int start, int stop);

//Another helper function that calls upon mSort
void mergeSort(int array[], int arraySize);

#endif