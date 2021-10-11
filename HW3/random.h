#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <chrono>
#include <iostream>


//From example code
//Wait a random time to simulate hard work
std::chrono::seconds waitTime();

//Roll a dice
int rollDice();

//Roll a number from 0-5 inclusive
int randomNumberOfDice();

#endif