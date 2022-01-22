#include "ioLockOut.h"

std::mutex ioLock;


void startWestForage(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is foraging on the west side" << endl;
}
void endWestForage(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is done foraging on the west side" << endl;
}


void startEastForage(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is foraging on the east side" << endl;
}
void endEastForage(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is done foraging on the east side" << endl;
}



void startWestToEast(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is crossing from the west to the east --->" << endl;
}
void endWestToEast(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " has made it from the west to the east ->" << endl;
}

void startEastToWest(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " is crossing from the east to the west <---" << endl;
}
void endEastToWest(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " has made it from the east to the west <-" << endl;
}



void napLock(string name) {
    std::lock_guard<std::mutex> lk(ioLock);
    cout << name << " has finished all of its tasks and is now napping" << endl;
}