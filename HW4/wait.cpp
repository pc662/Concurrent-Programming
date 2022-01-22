#include "wait.h"

std::chrono::seconds forageWait() {
    int timeToWait = std::rand()%4;
    std::chrono::seconds t = std::chrono::seconds(timeToWait);
    return t;
}

std::chrono::seconds bridgeWait() {
    int timeToWait = std::rand()%2;
    std::chrono::seconds t = std::chrono::seconds(timeToWait);
    return t;
}