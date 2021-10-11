#include "random.h"

//From example code
//Wait a random time to simulate hard work
std::chrono::seconds waitTime(){
	int time2Wait = std::rand()%2;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	return t;
}

int rollDice() {
    int diceRoll = std::rand()% 6 + 1;
    return diceRoll;
}

int randomNumberOfDice() {
    int randomNum = std::rand()%5;
    return randomNum;
}