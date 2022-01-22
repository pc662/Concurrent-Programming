#include "threadpool.h"



//Initiate the threadpool
threadpool::threadpool(string searchString) {
    //String to be searched for
    myString = searchString;
    //Determine number of threads
    numberOfThreads = std::thread::hardware_concurrency();
    //If the number of threads is less than 2, default to 2
    if (numberOfThreads < 2) {
        numberOfThreads = 2;
    }
    //Make space for threads
    threadArray = new std::thread*[numberOfThreads];
    tasks = new std::queue<string>();
}


//Add a file path to the work queue
void threadpool::addWork(string filePath) {
    tasks->push(filePath);
}

//Start up all the threads
void threadpool::start() {
    if (tasks->empty()) {
        return;
    }

    //If the results given are less than the hardware concurrency amount of threads, then the number of threads used will be equal to the amount of items in the queue
    // if (tasks->size() < numberOfThreads) {
    //     numberOfThreads = tasks->size();
    // }

    //Starting the threads up
    for (int i=0; i < numberOfThreads; i++) {
        threadArray[i] = new std::thread(&threadpool::workerThread, this, i);
    }
    //Join the threads
    for (int i=0; i < numberOfThreads; i++) {
        threadArray[i]->join();
    }
}

//Stop the threadpool
void threadpool::stop() {
    done = true;
    //Wake all
    timeToWork.notify_all();
}

//Function for the threads to pop and process the task
//Used parts of the week 5 code in the worker thread for the locks. Changed the task processing to be my own.
void threadpool::workerThread(int statusID) {

    //Stores the filePath name for work
    string filePath;
    //Keep looping until a break
    while (true) {

        {//Lock scope
        //Create lock for condition variable
        std::unique_lock<std::mutex> lk(lockQueue);
        //Waiting for work
        timeToWork.wait(lk, [&] { return !tasks->empty() || done;});
        //If thread was woken upon done, then break away and program will end
        if (done) {
            break;
        }
        //Since there is work to do, then pop a path off the queue to do work with
        filePath = tasks->front();
        tasks->pop();
    } //End of lock scope

    //Do the task of parsing file
    parseFile(filePath, statusID);

    {//Lock scope
    //Checking if the queue is empty
    std::unique_lock<std::mutex> lk(lockQueue);
    //If the queue is empty, then that means there are no longer any files to parse through, which makes the done variable true
    if (tasks->empty()) {
        stop();
    }  //End of this lock scope
    }
}
}

//Function to parse the files provided and console output 
void threadpool::parseFile(std::string fileName, int statusID) {
    string line;
    string search = myString;
    ifstream fileInput(fileName);
    unsigned int currentLine = 0;
    while (getline(fileInput, line)) {
        currentLine++;
        if (line.find(search, 0) != string::npos) {
            {//Start of lock scope
            std::unique_lock<std::mutex> lk(lockQueue);
            cout << "Thread " << statusID << " found a match." << endl;
            cout << "File: " << fileName << endl;
            cout << "Line " << currentLine << ": " << line << endl << "--------------------" << endl << "--------------------" << endl;

            }//End of lock scope
        }
    }
}

//Helper function to get the number of threads
int threadpool::getNumberOfThreads() {
    return numberOfThreads;
}

//Helper function to get the queue size
int threadpool::getQueueSize() {
    return tasks->size();
}





