#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <chrono>
#include <iostream>


//From example code
//Wait a random time to simulate hard work
std::chrono::seconds waitTime();

//Wait a random time to simulate threads being initialized earlier
std::chrono::seconds waitForExecution();

//Wait for randomness
std::chrono::milliseconds waitInitialize();


#endif