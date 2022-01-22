#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>
#include <random>
#include <chrono>
#include "random.h"

using std::cout;
using std::endl;
using std::string;

std::mutex m;
std::condition_variable boatIsland;
std::condition_variable inDriverSeat;
std::condition_variable inPassengerSeat;
std::condition_variable movingBoat;
std::condition_variable waitForPassengerToGetOff;

//Main island function
void islandFunction(string age, int identifier);
//First child function
void firstChildFunction(string age, int identifier);
//Function to get on the boat
void getOnBoat(string age, int identifier);
//Function to wait for the rowing of boat
void waitForRow(string age, int identifier);
//Borrowed this string to digit converter from stackoverflow
bool has_only_digits(const string s);




//Where the boat is
bool onIsland = false;
bool onMainland = false;
//Number of threads counter
int numberOfThreads = 0;
//Global to identify whether the boat has a driver yet or not
bool hasDriver = false;
//Global to identify if there is someone in the passenger seat
bool hasPassenger = false;
//Global to see if passenger has gotten off
bool passengerOff;

//Summary variables
int numberOfTimesToMainland = 0;
int numberOfTimesToIsland = 0;
int boatsWithOne = 0;
int boatsWithTwoChildren = 0;
int boatsWithChildAndAdult = 0;


int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: ./island [number of adults] [number of children]" << endl;
        return -1;
    }

    if (!has_only_digits(argv[1]) || !has_only_digits(argv[2])) {
        cout << "Usage: ./island [number of adults] [number of children]" << endl;
        return -1;
    }

    if (atoi(argv[1]) <= 0 || atoi(argv[2]) <=0 ) {
        cout << "Please have adults and children be greater than 0" << endl;
        return -1;
    }

    //Initialize random number generator
    std::srand(std::time(NULL));

    //Number of adults and children
    int adults = atoi(argv[1]);
    int children = atoi(argv[2]);

    //Identifier for age
    string adult = "Adult";
    string child = "Child";


    std::thread* adultThreads = new std::thread[adults];
    std::thread* childrenThreads = new std::thread[children];

    //Boat has 2 seats:
    //driver
    //passenger
    //2 children can ride at the same time
    //1 child and 1 adult can ride at the same time
    //2 adults cannot ride at the same time

    //Adult threads
    for (int i = 0; i < adults; i++) {
        adultThreads[i] = std::thread(islandFunction, adult, i);
    }
    //Children threads
    for (int i = 0; i < children; i++) {
        if (i == (children - 1)) {
            childrenThreads[i] = std::thread(firstChildFunction, child, i);
        } else {
            childrenThreads[i] = std::thread(islandFunction, child, i);
        }
    }

    for (int i = 0; i < adults; i++) {
        adultThreads[i].join();
    }
    for (int i = 0; i < children; i++) {
        childrenThreads[i].join();
    }




}
void getOnBoat(string age, int identifier) {

    std::unique_lock<std::mutex> lock(m);
    //Wait until boat is on the island
    boatIsland.wait(lock, [&] {return onIsland;});
    //Set passenger
    std::cout << age << " " << identifier << " has gotten into the passenger seat." << std::endl;
    hasPassenger = true;
    passengerOff = false;
    if (age == "Adult") {
        boatsWithChildAndAdult += 1;
    } else {
        boatsWithTwoChildren += 1;
    }
    inPassengerSeat.notify_one();
    
}

void waitForRow(string age, int identifier) {

    std::unique_lock<std::mutex> lock(m);
    //Condition variable while boat is being rowed
    movingBoat.wait(lock, [&] {return onMainland;});
    //Passenger has gotten off
    hasPassenger = false;
    cout << age << " " << identifier << " has gotten off the boat to mainland." << endl;
    numberOfThreads -= 1;
    passengerOff = true;
    waitForPassengerToGetOff.notify_one();

}

void islandFunction(string age, int identifier) {

    std::this_thread::sleep_for(waitInitialize());
    numberOfThreads += 1;
    getOnBoat(age, identifier);
    waitForRow(age, identifier);

}


void firstChildFunction(string age, int identifier) {

    //If it is a child and there are no drivers, set the driver to be the first child to reach this section
    std::cout << age << " " << identifier << " has gotten into the driver seat." << std::endl;
    hasDriver = true;
        
    //Give a chance for the other threads to be created
    std::chrono::milliseconds t = std::chrono::milliseconds(2000);
    std::this_thread::sleep_for(t);


    while (true) {
        std::unique_lock<std::mutex> lock(m);
        //Notify that the boat is on the island
        onIsland = true;
        boatIsland.notify_one();;
        

        //Wait until there is a passenger
        inPassengerSeat.wait(lock, [&] {return hasPassenger;});
        onIsland = false;

        //Row boat from island to mainland
        cout << "Boat is traveling from island to mainland." << endl;
        std::this_thread::sleep_for(waitTime());
        numberOfTimesToMainland += 1;
        onMainland = true;
        movingBoat.notify_one();
        

        //Wait for passenger to get off
        waitForPassengerToGetOff.wait(lock, [&] { return passengerOff;});
        //If there are no more threads waiting, get off the boat too
        if (numberOfThreads == 0) {
            cout << age << " " << identifier << " has gotten off the boat to mainland." << endl;
            break;
        }


        //Row boat from mainland to island
        cout << "Boat is traveling from mainland to island." << endl;
        std::this_thread::sleep_for(waitTime());
        numberOfTimesToIsland += 1;
        boatsWithOne += 1;
        onMainland = false;

    }

    cout << " " << endl;
    cout << "Summary of Events:" << endl;
    cout << "Boat traveled to the mainland: " << numberOfTimesToMainland << endl;
    cout << "Boat traveled to the island: " << numberOfTimesToIsland << endl;
    cout << "Boats with 2 children: " << boatsWithTwoChildren << endl;
    cout << "Boats with 1 child and 1 adult: " << boatsWithChildAndAdult << endl;
    cout << "Boats with only 1 person: " << boatsWithOne << endl;
    cout << "Times where adult was the driver: " << 0 << endl;
    cout << "Times where child was the driver: " << numberOfTimesToIsland + numberOfTimesToMainland << endl;
    

}

bool has_only_digits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}

