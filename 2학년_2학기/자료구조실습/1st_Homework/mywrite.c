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
    /* 아래에 코드를 작성하세요. */
    int fd = 0;
    char * pathName = "./student.dat";

    ssize_t wSize = 0;

    char studentId[MAX_ID_SIZE + 1];
    char studentName[MAX_NAME_SIZE + 1];
    int studentScore = 0;

    Student* student = (Student *)malloc(sizeof(Student));
    memset(student->id, '\0', MAX_ID_SIZE + 1);
    memset(student->name, '\0', MAX_NAME_SIZE + 1);
    student->score = 0;

    printf("ID: ");
    scanf("%s", studentId);
    strcpy(student->id, studentId);

    printf("Name: ");
    scanf("%s", studentName);
    strcpy(student->name, studentName);

    printf("Score: ");
    scanf("%d", &studentScore);
    student->score = studentScore;

    fd = open(pathName, O_WRONLY | O_CREAT | O_APPEND, PERMS);
    if (fd == -1) {
        printf("open() error!");
        exit(-1);
    }

    wSize = write(fd, (Student *)student, sizeof(Student));
    if(wSize == -1) {
        perror("write() error!");
        exit(-2);
    }

    printf("Saved at ./student.dat.\n");

    close(fd);
    free(student);

    return 0;
}
