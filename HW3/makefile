CC = g++
STD = -std=c++17

main : main.cpp print.cpp random.cpp semaphore.cpp
	${CC} ${STD} -pthread main.cpp random.cpp semaphore.cpp print.cpp -o main

run : main
	./main 2
	./main 4
	./main 10

clean:
	rm -f main