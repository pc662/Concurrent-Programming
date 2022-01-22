#ifndef _IO_LOCK_OUT_H
#define _IO_LOCK_OUT_H

#include <iostream>
#include <mutex>
#include <thread>
#include "wait.h"

using std::cout;
using std::endl;
using std::string;

//Start and end forage outputs
void startWestForage(string name);
void endWestForage(string name);

void startEastForage(string name);
void endEastForage(string name);


//Start and end crossing outputs
void startWestToEast(string name);
void endWestToEast(string name);

void startEastToWest(string name);
void endEastToWest(string name);


//Nap output
void napLock(string name);


#endif