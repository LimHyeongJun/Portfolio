CC = gcc

a.out : main.o AddMethod.o Init.o Scheduler.o TestCase1.o TestCase2.o TestCase3.o TestCase4.o Thread.o
	gcc main.o AddMethod.o Init.o Scheduler.o TestCase1.o TestCase2.o TestCase3.o TestCase4.o Thread.o -o a.out
main.o : main.c Init.h Scheduler.h TestCase1.h TestCase2.h TestCase3.h TestCase4.h Thread.h
	gcc -c main.c
AddMethod.o : AddMethod.c AddMethod.h Thread.h
	gcc -c AddMethod.c
Init.o : Init.c Init.h Thread.h Scheduler.h
	gcc -c Init.c
Scheduler.o : Scheduler.c Scheduler.h AddMethod.h Init.h
	gcc -c Scheduler.c
TestCase1.o : TestCase1.c TestCase1.h
	gcc -c TestCase1.c
TestCase2.o : TestCase2.c TestCase2.h
	gcc -c TestCase2.c
TestCase3.o : TestCase3.c TestCase3.h
	gcc -c TestCase3.c
TestCase4.o : TestCase4.c TestCase4.h
	gcc -c TestCase4.c
Thread.o : Thread.c Thread.h AddMethod.h Scheduler.h Init.h
	gcc -c Thread.c

clean:
	rm -f *.out *.o
