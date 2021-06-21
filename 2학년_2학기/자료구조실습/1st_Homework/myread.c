/*
* Student ID: 2016726082 
* Name: 임형준
*/

 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "MyStudent.h"

#define PERMS 0644

int main(int argc, char *argv[]) {
    int fd = 0;
    char * pathName = "./student.dat";
    ssize_t rSize = 0;

    Student * student = (Student *)malloc(sizeof(Student));
    memset(student->id, '\0', MAX_ID_SIZE + 1);
    memset(student->name, '\0', MAX_NAME_SIZE + 1);
    student->score = 0;

    fd = open(pathName, O_RDONLY, PERMS);
    if(fd == -1) {
        perror("open() error!");
        exit(-1);
    }
    
    do {
    rSize = read(fd, (Student *)student, sizeof(Student));

    if(rSize == -1) {
        perror("read() error!");
        exit(-2);
    }
    else if(rSize == 0) 
        break;
    printf("ID: %s, Name: %s, Score: %d\n", student->id, student->name, student->score);
    } while(rSize > 0);

    close(fd);
    free(student);

    return 0;
}
