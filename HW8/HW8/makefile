CC=g++
FLAGS=--std=c++17 -pthread

bintree: main.cpp binaryTree.h
	${CC} ${FLAGS} main.cpp binaryTree.h -o bintree

run: bintree
	./bintree -i $(i) -d $(d)

clean:
	rm -f bintree
	