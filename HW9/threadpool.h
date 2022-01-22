#ifndef _THREADPOOL_H_
#define _THREADPOOL_H_

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <string>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

//Going off of Prof. Boady's threadpool class structure and adding and adjusting based on own needs 
class threadpool {
    private:
        //Amount of threads
        int numberOfThreads;
        //Pointer to the array of threads
        std::thread** threadArray;
        //Boolean that tells if the entire threadpool is done to exit
        bool done;
        //Condition variable
        std::condition_variable timeToWork;
        //Mutex to protect the queue of work
        std::mutex lockQueue;
        //Task queue
        std::queue<std::string>* tasks;
        //String to be searched for
        string myString;
    public:
        //Initializer
        threadpool(string searchString);
        //Add some work to the queue
        void addWork(string filePath);
        //Start the pool up
        void start();
        //Function to parse the file for worker thread
        void parseFile(string fileName, int statusID);
        //Get number of threads
        int getNumberOfThreads();
        //Get size of queue
        int getQueueSize();
    private:
        //Thread that does the work
        void workerThread(int statusID);
        //Stop the pool
        void stop();

};

#endif