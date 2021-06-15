CC = gcc

main.out : main.o hw1.o
	gcc main.o hw1.o -o main.out
main.o : main.c hw1.h
	gcc -c main.c
hw1.o : hw1.c hw1.h
	gcc -c hw1.c
