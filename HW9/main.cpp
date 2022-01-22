#include <iostream>
#include <filesystem>
#include <mutex>
#include <thread>
#include <queue>
#include <fstream>
#include <istream>
#include <string>
#include "threadpool.h"

using std::ifstream;
using std::string;
using std::getline;
using std::cout;
using std::endl;
using std::filesystem::recursive_directory_iterator;

void parseFile(string fileName, string stringToBeSearched);


int main(int argv, char** argc) {

    string path = ".";

    //Command line handling
    //If more than the alloted arguments are given, return an error
    if (argv > 3) {
        cout << "Please do ./main [string to search for] [optional Folder to search]" << endl;
        return -1;
    }

    //If the user has provided a folder, use it. If not, it will default to current
    if (argv == 3) {
        path = argc[2];
    }

    //Needs at least 2 arguments
    if (argv < 2) {
        cout << "Please do ./main [string to search for] [optional Folder to search]" << endl;
        return -1;
    }

    //Check if the provided path is a folder name
    if (!std::filesystem::is_directory(path)) {
        cout << "Given folder name is not a directory." << endl;
        return -1;
    }


    string searchString = argc[1];
    threadpool* myPool = new threadpool(searchString);
    bool empty = true;

    //Producer thread will be looking for files here    
    for (const auto & entry : recursive_directory_iterator(path)) {
        if (entry.path().extension() == ".cc" ||
            entry.path().extension() == ".c"  ||
            entry.path().extension() == ".cpp"||
            entry.path().extension() == ".h"  ||
            entry.path().extension() == ".hpp"||
            entry.path().extension() == ".pl" ||
            entry.path().extension() == ".sh" ||
            entry.path().extension() == ".py" ||
            entry.path().extension() == ".txt")
            {
                myPool->addWork(entry.path());
            }
    }

    //Fancy text
    cout << "!---- Search Started ----!" << endl;
    cout << "Target Folder: " << path << endl;
    cout << "Target Text: " << searchString << endl;
    cout << "Using a Pool of " << myPool->getNumberOfThreads() <<  " threads to search." << endl << "--------------------" << endl;

    myPool->start();

    cout << "!---- Search Complete ----!" << endl;

    return 0;
}