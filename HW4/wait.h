#ifndef _WAIT_H_
#define _WAIT_H_

#include <iostream>
#include <chrono>
#include <random>
#include <thread>

//Default waiting for foraging
std::chrono::seconds forageWait();
//Default time waiting for bridge crossing
std::chrono::seconds bridgeWait();

#endif
