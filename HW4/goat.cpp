#include "goat.h"
#include "wait.h"
#include "ioLockOut.h"

goat::goat(string givenName) {
    name = givenName;
}

void goat::forageOnWest() {
    
    startWestForage(name);
    std::this_thread::sleep_for(forageWait());
    endWestForage(name);

}

void goat::forageOnEast() {
    startEastForage(name);
    std::this_thread::sleep_for(forageWait());
    endEastForage(name);
}

void goat::crossFromWest() {
    startWestToEast(name);
    std::this_thread::sleep_for(bridgeWait());
    endWestToEast(name);
}

void goat::crossFromEast() {
    startEastToWest(name);
    std::this_thread::sleep_for(bridgeWait());
    endEastToWest(name);
}

void goat::nap() {
    napLock(name);
}



