#Makefile for snake project

Snake: main.o Snakelib.o
	g++ -o ./bin/Debug/Snake ./obj/Debug/main.o ./obj/Debug/Snakelib.o

main.o: main.cpp
	g++ -c -o ./obj/Debug/main.o  main.cpp

Snakelib.o: Snakelib.cpp
	g++ -c -o ./obj/Debug/Snakelib.o Snakelib.cpp

clean:
	rm -f *.o ./bin/Debug/* ./obj/Debug/*
