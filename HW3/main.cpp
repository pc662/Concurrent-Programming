//Using the semaphore code provided by Prof. Boady


#include <thread>
#include <queue>
#include "semaphore.h"
#include "random.h"
#include "print.h"

using std::thread;
using std::queue;
using std::cout;
using std::endl;
using std::string;

//This is the game master's function to produce dice rolls
void createData(queue<int> &diceRolls, semaphore* racer, semaphore* gameMaster, queue<int> &winners, int numberOfThreads);
//This is the racer's function to move spaces 
void processData(queue<int> &diceRolls, semaphore* racer, semaphore* gameMaster, queue<int> &winners, int i);

//Borrowed this string to digit converter from stackoverflow
bool has_only_digits(const string s);


int main(int argc, char** argv) {

    //Initialize random number generator
    std::srand(std::time(NULL));

    int numberOfThreads;

    if (argc < 2 || argc > 2) {
        cout << "Usage: ./main [number of threads]" <<  endl;
        return -1;
    }

    if (!has_only_digits(argv[1])) {
        cout << "Usage: ./main [number of threads]" <<  endl;
        return -1;
    }

    if (atoi(argv[1]) < 1) {
        cout << "Please have the number of threads be greater than 0" << endl;
        return -1;
    }





    //Create semaphores for the gameMaster and racer
    semaphore* gameMaster = new semaphore(1);
    semaphore* racer = new semaphore(0);

    //Initialize the queue
    queue<int> diceRolls;
    queue<int> winners;
    numberOfThreads = atoi(argv[1]);

    //Create array of threads
    //With + 1 for the gameMaster thread
    thread threadArray[numberOfThreads + 1];

    //Print out the initial amount of threads starting the race
    cout << "Starting race with " << numberOfThreads << " threads." << endl;


    //Make threads do something
    for (int i = 0; i < numberOfThreads + 1; i++) {

        //Game master thread
        if (i == 0) {
            threadArray[i] = thread(createData, std::ref(diceRolls), racer, gameMaster, std::ref(winners), numberOfThreads); 
        }
        //Racer threads 
        else {
            threadArray[i] = thread(processData, std::ref(diceRolls), racer, gameMaster, std::ref(winners), i);
        }
    }



    for (int i = 0; i < numberOfThreads + 1; i++) {
        threadArray[i].join();
    }

    int place = 1;
    while (!winners.empty()) {
        cout << place << ": Thread " << winners.front() << endl;
        winners.pop();
        place++;
    }
    //Just to be neater
    cout << "--------------------------------------------------------" << endl;

}


//Game master's function
void createData(queue<int> &diceRolls, semaphore* racer, semaphore* gameMaster, queue<int> &winners, int numberOfThreads) {

    int numberOfDice;
    int number; 

    while (winners.size() < numberOfThreads) {
        numberOfDice = randomNumberOfDice();
        //Locks the queue and adds the dice rolls
        gameMaster->wait();
        for (int i = 0; i < numberOfDice; i++) {
            number = rollDice();
            diceRolls.push(number);
        }
        //Unlocks the queue
        gameMaster->signal();
        racer->signal();
        std::this_thread::sleep_for(waitTime());
}
}


//Racer's function
void processData(queue<int> &diceRolls, semaphore* racer, semaphore* gameMaster, queue<int> &winners, int i) {
    int spacesMoved = 0;
    int tempMove;

    int threadName = i;

    //Prints that the thread has left the gate
    gatePrint(i);

    while (spacesMoved < 20) {
        racer->wait();
        //Locks the queue so the thread can get a dice roll and remove it from queue
        gameMaster->wait();
        tempMove = diceRolls.front();
        diceRolls.pop();
        //Unlocks the queue
        gameMaster->signal();
        spacesMoved = spacesMoved + tempMove;
        //Prints the amount of spaces moved
        movePrint(i, tempMove);
        std::this_thread::sleep_for(waitTime());
    }
    cout <<"Thread " << threadName << " has crossed the finish line." << endl;
    winners.push(threadName);

}


//Checks if string is a digit
bool has_only_digits(const string s){
  return s.find_first_not_of( "0123456789" ) == string::npos;
}








