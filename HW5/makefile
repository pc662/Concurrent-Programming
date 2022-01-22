CC = g++
STD = -std=c++17

.PHONY : run clean

island: main.cpp random.cpp
	${CC} ${STD} -pthread main.cpp random.cpp -o island

run: island
	./island 7 9

clean:
	rm -f island