#ifndef _LIGHTSWITCH_H_
#define _LIGHTSWITCH_H_

#include <iostream>
#include <mutex>
#include "semaphore.h"

//Basically incorporated the lightswitch class from the slides into code format 
class lightswitch {
    private:
        //Counter for amount of goats in the room
        int goats;
        mutable std::mutex countLock;

    public:
        //New room
        lightswitch();
        //Enter and signal first goat to enter
        void enter(semaphore* sem);
        //Leave the bridge and signal if last to leave
        void leave(semaphore* sem);
        //Get the current counter
        int getCounter();
};

#endif
