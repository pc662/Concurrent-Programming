#include "print.h"

std::mutex ioLock;

void gatePrint(int name)
{
	std::lock_guard<std::mutex> lk(ioLock);
	std::cout << "Thread " << name
		<< " has left the gate." << std::endl;
}

void movePrint(int name, int spaces) {
    std::lock_guard<std::mutex> lk(ioLock);
    std::cout << "Thread " << name << " has moved " << spaces << " spaces." << std::endl;
}