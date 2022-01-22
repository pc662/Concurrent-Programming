CC = g++
STD = -std=c++17

.PHONY : run clean

goat: main.cpp semaphore.cpp lightswitch.cpp goat.cpp wait.cpp ioLockOut.cpp 
	${CC} ${STD} -pthread main.cpp semaphore.cpp lightswitch.cpp goat.cpp wait.cpp ioLockOut.cpp -o goats

run: goat
	./goats 12 21

clean:
	rm -f goats