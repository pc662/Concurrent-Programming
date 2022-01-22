#include <iostream>
#include <thread>
#include <chrono>
#include "semaphore.h"
#include "lightswitch.h"
#include "goat.h"


using std::string;
using std::cout;
using std::endl;

//Responsible for doing west goat functions
void westFunction(int i, semaphore* turnstile, semaphore* bridgeEmpty, lightswitch* bridgeSwitch);

//Responsible for doing east goat functions
void eastFunction(int i, semaphore* turnstile, semaphore* bridgeEmpty, lightswitch* bridgeSwitch);

//Borrowed this string to digit converter from stackoverflow
bool has_only_digits(const string s);



int main(int argc, char** argv) {


    if (argc != 3) {
        cout << "Usage: ./goats [number of west goats] [numebr of east goats]" << endl;
        return -1;
    }

    if (!has_only_digits(argv[1]) || !has_only_digits(argv[2])) {
        cout << "Usage: ./goats [number of west goats] [number of east goats]" << endl;
        return -1;
    }

    if (atoi(argv[1]) < 1 || atoi(argv[2]) < 1) {
        cout << "Please have the number of goats be greater than 0" << endl;
        return -1;
    }


    //Initialize random number generator
    std::srand(std::time(NULL));


    int westGoats = atoi(argv[1]);
    int eastGoats = atoi(argv[2]);

    std::thread* westThreads = new std::thread[westGoats];
    std::thread* eastThreads = new std::thread[eastGoats];


    

    //Lightswitch
    lightswitch* bridgeSwitch = new lightswitch();

    //Semaphore section
    semaphore* turnstile = new semaphore(1);
    semaphore* bridgeEmpty = new semaphore(1);



    //Responsible for creating the west goats
    for (int i = 0; i < westGoats; i++) {
        westThreads[i] = std::thread(westFunction, i, turnstile, bridgeEmpty, bridgeSwitch);
    }
    //Responsible for creating the east goats
    for (int i = 0; i < eastGoats; i++) {
        eastThreads[i] = std::thread(eastFunction, i, turnstile, bridgeEmpty, bridgeSwitch);
    }




    //Joining the threads
    for (int i = 0; i <westGoats; i++) {
        westThreads[i].join();
    }
    for (int i = 0; i < eastGoats; i++) {
        eastThreads[i].join();
    }


}



//We will say the west side are writers
void westFunction(int i, semaphore* turnstile, semaphore* bridgeEmpty, lightswitch* bridgeSwitch) 

{
    string goatName = "W" + std::to_string(i);
    goat* thisGoat = new goat(goatName);

    //Forage on the west
    thisGoat->forageOnWest();

    //Cross from west to east
    turnstile->wait();
    bridgeEmpty->wait();
    thisGoat->crossFromWest();
    turnstile->signal();
    bridgeEmpty->signal();

    //Forage on east
    thisGoat->forageOnEast();
    
    //Cross from east to west
    turnstile->wait();
    turnstile->signal();
    bridgeSwitch->enter(bridgeEmpty);
    thisGoat->crossFromEast();
    bridgeSwitch->leave(bridgeEmpty);

    //Nap 
    thisGoat->nap();


}


//We will say the east side are readers
void eastFunction(int i, semaphore* turnstile, semaphore* bridgeEmpty, lightswitch* bridgeSwitch)

 {
    string goatName = "E" + std::to_string(i);
    goat* thisGoat = new goat(goatName);

    //Forage on the east
    thisGoat->forageOnEast();

    //Cross from east to west
    turnstile->wait();
    turnstile->signal();
    bridgeSwitch->enter(bridgeEmpty);
    thisGoat->crossFromEast();
    bridgeSwitch->leave(bridgeEmpty);



    //Forage on West
    thisGoat->forageOnWest();

    //Cross from west to east
    turnstile->wait();
    bridgeEmpty->wait();
    thisGoat->crossFromWest();
    turnstile->signal();
    bridgeEmpty->signal();

    //Nap
    thisGoat->nap();

    

}

//Checks if string is a digit
bool has_only_digits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}