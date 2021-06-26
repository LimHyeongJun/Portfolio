/*
 * Student ID : 2016726082
 * Name : 임형준(Lim Hyeong Jun)
 */
#include "MyShm.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

void signalHandler(int signum);
void myfunc(void);
int calculate(Calc calc);

key_t mykey = 0;
int shmid = 0;
Calc *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    mykey = ftok("mykey4", 10);
    shmid = shmget(mykey, SHM_MAX_SIZE, IPC_CREAT | PERMS);
    shmaddr = (Calc *)shmat(shmid, NULL, 0);

    signal(SIGINT, signalHandler);
    signal(SIGUSR1, signalHandler);

    while (1) {
        puts("Wait ...");
        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    struct shmid_ds buf;

    if (signum == SIGINT) {
        shmdt(shmaddr);
        shmctl(shmid, IPC_RMID, NULL);
        exit(0);
    } else if (signum == SIGUSR1) {
        myfunc();
    }
}

void myfunc(void) {
    struct shmid_ds buf;
    Calc calc;

    memcpy(&calc, shmaddr, sizeof(Calc));
    printf("Receive: %d %c %d\n", calc.x, calc.op, calc.y);

    int result = calculate(calc);

    memcpy((int *)shmaddr, &result, sizeof(int));
    printf("Send: %d\n", result);

    shmctl(shmid, IPC_STAT, &buf);
    kill(buf.shm_lpid, SIGUSR1);
}

int calculate(Calc calc) {
    switch (calc.op) {
    case '+':
        return calc.x + calc.y;
    case '-':
        return calc.x - calc.y;
    case '*':
        return calc.x * calc.y;
    case '/':
        return (int)(calc.x / calc.y);
    default:
        return 0;
    }
}
