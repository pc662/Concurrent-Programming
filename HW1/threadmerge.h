#ifndef _THREAD_MERGE_
#define _THREAD_MERGE_

//Thread merge sorting to use threads to sort first into sections
void tMergeSort(int arr[], int size, int numberOfThreads);

//Merging all the sections sorted by the threads
void mergeAllSections(int* A, int size, int* startIndexes, int* stopIndexes, int numThreads);

#endif
