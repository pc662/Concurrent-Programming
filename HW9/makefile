CC=g++
CFLAGS=--std=c++17 -pthread

search : main.cpp threadpool.cpp threadpool.h
	${CC} ${CFLAGS} main.cpp threadpool.cpp threadpool.h -o search

clean:
	rm -f search