cc = gcc

a.out : testcase.o fs.o fs_internal.o disk.o
	gcc testcase.o fs.o fs_internal.o disk.o -o a.out
testcase.o : testcase.c disk.h fs.h
	gcc -c testcase.c
fs.o : fs.c fs.h disk.h
	gcc -c fs.c
fs_internal.o : fs_internal.c disk.h fs.h
	gcc -c fs_internal.c
disk.o : disk.c disk.h
	gcc -c disk.c

clean:
	rm -f *.out *.o
