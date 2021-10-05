CC =g++
STD =-std=c++17

mergesort: main.cpp mergesort.cpp threadmerge.cpp
	${CC} -pthread ${STD} mergesort.cpp threadmerge.cpp main.cpp -o mergesort

clean:
	rm -f mergesort