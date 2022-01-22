#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include "binaryTree.h"

using std::cout;
using std::endl;
using std::string;

void insertFunction(int threadNumber, std::vector<int> &listOfNumbers, binaryTree* &binTree, int numberOfInsertThreads);
void deleteFunction(int threadNumber, std::vector<int> &listOfNumbersToBeDeleted, binaryTree* &binTree, int numberOfDeleteThreads);

int main(int argc, char** argv) {

    int opt;
    string inputFileName;
    string numbersToBeDeleted;



    binaryTree* binTree = new binaryTree();
    std::vector<int> listOfNumbers;
    std::vector<int> listOfNumbersToBeDeleted;

    //1. Looks for the flags
    while ((opt = getopt(argc, argv, "i:d:")) != -1) {
        
        switch (opt) {

            //i flag for the input file
            case 'i' : {
                inputFileName = optarg;
                //Open up the file
                std::ifstream inFile(optarg);
                if (inFile) {
                    int value;
                    while (inFile >> value) {
                        listOfNumbers.push_back(value);
                    }
                }

                inFile.close();
                break;
            }

            //d flag for the deletion file
            case 'd' : {
                numbersToBeDeleted = optarg;
                //Open up the file
                std::ifstream inFile(optarg);
                if (inFile) {
                    int value;
                    while (inFile >> value) {
                        listOfNumbersToBeDeleted.push_back(value);
                    }
                }

                inFile.close();
                break;
            }
        }
    }

    //2. Finding first, middle, and last value
    int firstValue = listOfNumbersToBeDeleted.front();
    int lastValue = listOfNumbersToBeDeleted.back();
    int middleValue;

    //If size is odd
    if (listOfNumbersToBeDeleted.size() % 2 == 1) {
        middleValue = listOfNumbersToBeDeleted[((listOfNumbersToBeDeleted.size() + 1)/2) - 1];
    }
    //If size is even
    else {
        middleValue = listOfNumbersToBeDeleted[(listOfNumbersToBeDeleted.size()/2) - 1];
    }

    //3. Initiate inserting thread
    std::thread* insertThreads;
    int numberOfInsertThreads;

    //Determines the number of threads to use
    if (listOfNumbers.size() < 8) {
        insertThreads = new std::thread[listOfNumbers.size()];
        numberOfInsertThreads = listOfNumbers.size();
    } else {
        insertThreads = new std::thread[8];
        numberOfInsertThreads = 8;
    }

    //Initiates the threads and joins them
    for (int i = 0; i < numberOfInsertThreads; i++) {
        insertThreads[i] = std::thread(insertFunction, i, std::ref(listOfNumbers), std::ref(binTree), numberOfInsertThreads);
    }
    for (int i = 0; i < numberOfInsertThreads; i++) {
        insertThreads[i].join();
    }

    //4. Print the BST out after insertion
    binTree->inOrderTraversal();
    cout << endl;
    cout << endl;

    //5. Search for the three numbers
    cout << firstValue << ": " << binTree->searchTree(firstValue) << endl;
    cout << middleValue << ": " << binTree->searchTree(middleValue) << endl;
    cout << lastValue << ": " << binTree->searchTree(lastValue) << endl;

    //6. Deleting the numbers from the BST with 8 threads
    std::thread* deleteThreads;
    int numberOfDeleteThreads;

    //Determines the number of threads to use
    if (listOfNumbersToBeDeleted.size() < 8) {
        deleteThreads = new std::thread[listOfNumbersToBeDeleted.size()];
        numberOfDeleteThreads = listOfNumbersToBeDeleted.size();
    } else {
        deleteThreads = new std::thread[8];
        numberOfDeleteThreads = 8;
    }

    //Initiates the threads and joins them
    for (int i = 0; i < numberOfDeleteThreads; i++) {
        deleteThreads[i] = std::thread(deleteFunction, i, std::ref(listOfNumbersToBeDeleted), std::ref(binTree), numberOfDeleteThreads);
    }
    for (int i = 0; i < numberOfDeleteThreads; i++) {
        deleteThreads[i].join();
    }


    //7. Printing out the new updated BST
    cout << endl;
    binTree->inOrderTraversal();
    cout << endl;
    cout << endl;

    //8. Searching for the previous elements to see if they are still in the BST
    cout << firstValue << ": " << binTree->searchTree(firstValue) << endl;
    cout << middleValue << ": " << binTree->searchTree(middleValue) << endl;
    cout << lastValue << ": " << binTree->searchTree(lastValue) << endl;

    return 0;

}

void insertFunction(int threadNumber, std::vector<int> &listOfNumbers, binaryTree* &binTree, int numberOfInsertThreads) {
    for (int i = threadNumber; i < listOfNumbers.size(); i += numberOfInsertThreads) {
        binTree->insert(listOfNumbers[i]);
    }
}

void deleteFunction(int threadNumber, std::vector<int> &listOfNumbersToBeDeleted, binaryTree* &binTree, int numberOfDeleteThreads) {
    for (int i = threadNumber; i < listOfNumbersToBeDeleted.size(); i += numberOfDeleteThreads) {
        binTree->deleteFromTree(listOfNumbersToBeDeleted[i]);
    }
}