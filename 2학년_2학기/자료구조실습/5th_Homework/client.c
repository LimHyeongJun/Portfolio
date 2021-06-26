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

key_t mykey = 0;
int shmid = 0;
Calc *shmaddr = NULL;

int main(int argc, char const *argv[]) {
    struct shmid_ds buf;

    mykey = ftok("mykey4", 10);
    shmid = shmget(mykey, SHM_MAX_SIZE, IPC_CREAT | PERMS);
    shmaddr = (Calc *)shmat(shmid, NULL, 0);

    signal(SIGUSR1, signalHandler);

    puts("Input: [x] [op] [y]");
    while (1) {
        Calc calc;

        printf("<<< ");
        scanf("%d %c %d", &calc.x, &calc.op, &calc.y);

        fflush(stdout);
        fflush(stdin);

        memcpy((Calc *)shmaddr, &calc, sizeof(Calc));
        shmctl(shmid, IPC_STAT, &buf);
        kill(buf.shm_cpid, SIGUSR1);

        pause();
    }

    return 0;
}

void signalHandler(int signum) {
    int result;

    if (signum == SIGUSR1) {
        memcpy(&result, (int *)shmaddr, sizeof(int));
        printf(">>> %d\n", result);
    }
}
