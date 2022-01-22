#include "random.h"

//Wait a random time to simulate hard work
std::chrono::seconds waitTime(){
	int time2Wait = std::rand()%4 + 1;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	return t;
}

//Wait a random time to simulate threads being created earlier
std::chrono::seconds waitForExecution(){
	int time2Wait = std::rand()%3 + 2;
	std::chrono::seconds t
			= std::chrono::seconds(time2Wait);
	return t;
}

//Wait a few milliseconds
std::chrono::milliseconds waitInitialize() {
    int time2Wait = std::rand()%1000 + 500;
    std::chrono::milliseconds t = std::chrono::milliseconds(time2Wait);
    return t;

}