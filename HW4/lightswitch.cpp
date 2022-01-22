#include "lightswitch.h"

lightswitch::lightswitch() {
    std::lock_guard<std::mutex> lock(countLock);
    goats = 0;
}

void lightswitch::enter(semaphore* sem) {
    std::lock_guard<std::mutex> lock(countLock);
    goats++;
    if (goats == 1) {
        sem->wait();
    }
}

void lightswitch::leave(semaphore* sem) {
    std::lock_guard<std::mutex> lock(countLock);
    goats--;
    if (goats == 0) {
        sem->signal();
    }
}

int lightswitch::getCounter() {
    return goats;
}

