#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "AddMethod.h"

void myAlrmHandler(int signum);

int RunScheduler(void) {
    if (signal(SIGALRM, myAlrmHandler) == SIG_ERR) {
        perror("signal() error!");
    }
    int priority = -1;

    for (int i = 0; i < MAX_READYQUEUE_NUM; i++) {
        if (pReadyQueueEnt[i].queueCount != 0) {
            priority = i;
            break;
        }
    }
    
    if (priority != -1) {
        if (pCurrentThread == NULL) {
            Thread *temp = pReadyQueueEnt[priority].pHead;
            DeleteThreadFromReadyQueue(temp);
            temp->status = THREAD_STATUS_RUN;
            pCurrentThread = temp;
            kill(temp->pid, SIGCONT);
            alarm(TIMESLICE);
        } else if (priority == pCurrentThread->priority) {
            pid_t pCurrentThreadPid = pCurrentThread->pid;
            InsertThreadIntoTail(pCurrentThread, pCurrentThread->priority);
            pCurrentThread->status = THREAD_STATUS_READY;
            pCurrentThread = NULL;

            Thread* temp = pReadyQueueEnt[priority].pHead;
            temp->status = THREAD_STATUS_RUN;
            
            __ContextSwitch(pCurrentThreadPid, temp->pid);
            
            alarm(TIMESLICE);
        } else if (priority > pCurrentThread->priority) {
            alarm(TIMESLICE);
        }
    } else if (priority == -1) {
        if (pCurrentThread != NULL)
            alarm(TIMESLICE);
        else if (pCurrentThread == NULL)
            exit(1);
    }

    return 1;
}

//들어온 두 pid를 이용해 thread 테이블에서 thread를 찾고
//현재 실행중인 thread를 ready queue로 이동시킴
//새 thread를 실행시킴
void __ContextSwitch(int curpid, int newpid) {
    Thread *curThread = NULL;
    Thread *newThread = NULL;
    int decidenum = 2;
    for (int i = 0; i < MAX_THREAD_NUM; ++i) {
        if(decidenum == 0 )
            break;
        else if(pThreadTblEnt[i].bUsed == 0) {
            continue;
        } else if (pThreadTblEnt[i].pThread->pid == curpid) {
            curThread = pThreadTblEnt[i].pThread;
            --decidenum;
        } else if (pThreadTblEnt[i].pThread->pid == newpid) {
            newThread = pThreadTblEnt[i].pThread;
            --decidenum;
        }
    }

    pid_t pid = getpid();
    
    if (curThread->status != THREAD_STATUS_ZOMBIE && curpid != pid) {
        curThread->status = THREAD_STATUS_READY;
        kill(curpid, SIGSTOP);
    }

    if(curThread->status == THREAD_STATUS_ZOMBIE) {
        InsertThreadIntoWaitingQueue(curThread);
        DeleteThreadFromReadyQueue(newThread);
        newThread->phNext = NULL;
        newThread->phPrev = NULL;
        newThread->status = THREAD_STATUS_RUN;
        pCurrentThread = newThread;
        kill(newpid, SIGCONT);
    } else if (curThread->priority == newThread->priority) {
        Thread *temp = pReadyQueueEnt[newThread->priority].pHead->phNext;
        temp->phPrev = NULL;
        pReadyQueueEnt[newThread->priority].pHead = temp;
        --pReadyQueueEnt[newThread->priority].queueCount;
        newThread->phNext = NULL;
        newThread->phPrev = NULL;
        newThread->status = THREAD_STATUS_RUN;
        pCurrentThread = newThread;
        kill(newpid, SIGCONT);
    } else if(curThread->priority > newThread->priority) {
        InsertThreadIntoTail(curThread, curThread->priority);
        newThread->status = THREAD_STATUS_RUN;
        pCurrentThread = newThread;
        kill(newpid, SIGCONT);
    }
}

void myAlrmHandler(int signum) {
    if (signum == SIGALRM) {
        RunScheduler();
    }
}
