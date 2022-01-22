#ifndef _GOAT_H_
#define _GOAT_H_

#include <iostream>
#include <mutex>
#include <string>

using std::string;
using std::cout;
using std::endl;

class goat {
    private:
        //Name of the goat
        string name;
        mutable std::mutex ioLock;

    public:
        //Initialize goat
        goat(string name);
        //forage on west side
        void forageOnWest();
        //forage on east side
        void forageOnEast();
        //Cross the bridge from west side
        void crossFromWest();
        //Cross the bridge from east side
        void crossFromEast();
        //Nap and exit
        void nap();

};

#endif