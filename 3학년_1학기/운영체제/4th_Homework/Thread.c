#include "Thread.h"
#include "AddMethod.h"
#include "Init.h"
#include "Scheduler.h"

int thread_create(thread_t *thread, thread_attr_t *attr, int priority, void *(*start_routine)(void *), void *arg) {
    Thread *thr = (Thread *)malloc(sizeof(Thread));
    thr->stackSize = STACK_SIZE; //스레드의 사이즈
    char *pStack = malloc(STACK_SIZE);
    thr->stackAddr = (char *)pStack + STACK_SIZE; //스택의 주소
    int flags = SIGCHLD | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_VM;
    thr->pid = clone(start_routine, (char *)thr->stackAddr, flags, arg); //스레드 생성
    
    kill(thr->pid, SIGSTOP);  // Thread 정지
    thr->priority = priority; // Thread priority 지정

    for (int i = 0; i < MAX_THREAD_NUM; ++i) {
        if (pThreadTblEnt[i].bUsed == 0) {
            *thread = i;
            pThreadTblEnt[i].bUsed = 1;
            pThreadTblEnt[i].pThread = thr;
            break;
        }
    }

    if (pCurrentThread == NULL) {
        thr->status = THREAD_STATUS_RUN;
        pCurrentThread = thr;
        kill(thr->pid, SIGCONT);
    } else if (pCurrentThread != NULL && pCurrentThread->priority <= thr->priority) {
        thr->status = THREAD_STATUS_READY;
        InsertThreadIntoTail(thr, priority);
    } else if (pCurrentThread != NULL && pCurrentThread->priority > thr->priority) {
        InsertThreadIntoTail(pCurrentThread, pCurrentThread->priority);
        pCurrentThread->status = THREAD_STATUS_READY;
        Thread *temp = pCurrentThread;
        pCurrentThread = NULL;

        thr->status = THREAD_STATUS_RUN;

        __ContextSwitch(temp->pid, thr->pid);
    }
}

int thread_suspend(thread_t tid) {
    Thread *suspendThread = pThreadTblEnt[tid].pThread;

    if (suspendThread == NULL) //일시정지 시킬 thread가 없을 경우 -1리턴
        return -1;

    if (suspendThread->status == THREAD_STATUS_RUN) { //정지시킬 thread가 run 상태라면
        //실행중인 스레드 우선 정지시키고 waiting queue로 넣기
        InsertThreadIntoWaitingQueue(suspendThread);
        suspendThread->status = THREAD_STATUS_WAIT;
        pCurrentThread = NULL;
        kill(suspendThread, SIGSTOP);

        int priority;
        for (int i = 0; i < MAX_READYQUEUE_NUM; ++i) {
            if (pReadyQueueEnt[i].queueCount > 0) {
                priority = i;
                break;
            }
        }
    } else if (suspendThread->status == THREAD_STATUS_READY) { //정지시킬 thread가 ready 상태라면
        DeleteThreadFromReadyQueue(suspendThread);
        InsertThreadIntoWaitingQueue(suspendThread);
        suspendThread->status = THREAD_STATUS_WAIT;
    } else if (suspendThread->status == THREAD_STATUS_WAIT) { //정지시킬 thread가 waiting 상태라면
        if (pWaitingQueueHead == pWaitingQueueTail || pWaitingQueueTail == suspendThread) {
            // waiting queue에 하나만 있거나 Tail과 정지시킬 thread가 같으면 바로 리턴
            return 0;
        } else if (pWaitingQueueHead == suspendThread) {
            //일시정지 시킬 스레드가 waiting queue의 Head라면
            pWaitingQueueHead = suspendThread->phNext;
            pWaitingQueueHead->phPrev = NULL;
            InsertThreadIntoWaitingQueue(suspendThread);
        } else {
            //일시정지 시킬 스레드가 waiting queue의 중간에 있으면
            Thread *tempPrev = suspendThread->phPrev;
            Thread *tempNext = suspendThread->phNext;
            tempPrev->phNext = tempNext;
            tempNext->phPrev = tempPrev;
            InsertThreadIntoWaitingQueue(suspendThread);
        }
    }
    return 0;
}

int thread_cancel(thread_t tid) {
    if(pThreadTblEnt[tid].pThread->pid != pCurrentThread->pid) {
        kill(pThreadTblEnt[tid].pThread->pid, SIGKILL);

        if (pThreadTblEnt[tid].pThread->status == THREAD_STATUS_READY) {
            DeleteThreadFromReadyQueue(pThreadTblEnt[tid].pThread);
            free(pThreadTblEnt[tid].pThread->stackAddr - STACK_SIZE);
            free(pThreadTblEnt[tid].pThread);
            pThreadTblEnt[tid].pThread = NULL;
            pThreadTblEnt[tid].bUsed = 0;

            return 0;
        } else if (pThreadTblEnt[tid].pThread->status == THREAD_STATUS_WAIT) {
            DeleteThreadFromWaitingQueue(pThreadTblEnt[tid].pThread);
            free(pThreadTblEnt[tid].pThread->stackAddr - STACK_SIZE);
            free(pThreadTblEnt[tid].pThread);
            pThreadTblEnt[tid].pThread = NULL;
            pThreadTblEnt[tid].bUsed = 0;

            return 0;
        }
    }
    return -1;
}

int thread_resume(thread_t tid) {
    if (pThreadTblEnt[tid].pThread->status != THREAD_STATUS_WAIT)
        return -1; //해당 스레드가 wait상태가 아니면 안되므로 -1 return

    int resumePriority = pThreadTblEnt[tid].pThread->priority;

    if (resumePriority >= pCurrentThread->priority) {
        DeleteThreadFromWaitingQueue(pThreadTblEnt[tid].pThread);
        pThreadTblEnt[tid].pThread->status = THREAD_STATUS_READY;
        InsertThreadIntoTail(pThreadTblEnt[tid].pThread, resumePriority);
        return 0;
    } else if (resumePriority < pCurrentThread->priority) {
        pCurrentThread->status = THREAD_STATUS_READY;
        Thread *temp = pCurrentThread;

        DeleteThreadFromWaitingQueue(pThreadTblEnt[tid].pThread);
        pThreadTblEnt[tid].pThread->status = THREAD_STATUS_RUN;

        __ContextSwitch(temp->pid, pThreadTblEnt[tid].pThread->pid);
        return 0;
    }

    return -1; //여기까지 온 경우 문제가 있으므로 -1 리턴
}

thread_t thread_self() {
    pid_t tempPid = getpid();
    
    for (int i = 0; i < MAX_THREAD_NUM; ++i) {
        if(pThreadTblEnt[i].pThread == NULL || pThreadTblEnt[i].bUsed == 0) {
            continue;
        } else if (tempPid == pThreadTblEnt[i].pThread->pid) {
            return i;
        }
    }
    return -1;
}

void signalHandler(int signum);

int thread_join(thread_t tid, void **retval) {
    if(pThreadTblEnt[tid].pThread->status != THREAD_STATUS_ZOMBIE) {
        struct sigaction action;
        action.sa_flags = SA_NOCLDSTOP;
        action.sa_handler = signalHandler;

        if(sigaction(SIGCHLD, &action, NULL) == SIG_ERR) {
            perror("signal() error!");
        }
        pid_t pid = getpid();

        int index = -1;
        for (int i = 0; i < MAX_THREAD_NUM; i++) {
            if (pThreadTblEnt[i].bUsed == 1 && pid == pThreadTblEnt[i].pThread->pid) {
                index = i;
                break;
            }
        }
        pThreadTblEnt[index].pThread->status = THREAD_STATUS_WAIT;
        InsertThreadIntoWaitingQueue(pThreadTblEnt[index].pThread);
        pCurrentThread = NULL;
        
        if(pThreadTblEnt[tid].pThread->status == THREAD_STATUS_WAIT) {
            DeleteThreadFromWaitingQueue(pThreadTblEnt[tid].pThread);
            InsertThreadIntoTail(pThreadTblEnt[tid].pThread, pThreadTblEnt[tid].pThread->priority);
        }

        pause();
     
        int otherPriority = -1;   
        for(int i = 0; i < MAX_THREAD_NUM; i++) {
            if(pReadyQueueEnt[i].queueCount > 0) {
                otherPriority = i;
                break;
            }
        }
        int parentPriority = pThreadTblEnt[index].pThread->priority;

        if(pCurrentThread == NULL && parentPriority < otherPriority) {
            pCurrentThread = pThreadTblEnt[index].pThread;
            pCurrentThread->status = THREAD_STATUS_RUN;
        } else if(pCurrentThread == NULL && parentPriority >= otherPriority) {
            InsertThreadIntoTail(pThreadTblEnt[index].pThread, pThreadTblEnt[index].pThread->priority);
            pThreadTblEnt[index].pThread->status = THREAD_STATUS_READY;
        } else if(pCurrentThread != NULL && parentPriority < otherPriority) {
            __ContextSwitch(pCurrentThread->pid, pThreadTblEnt[index].pThread->pid);
        } else if(pCurrentThread != NULL && parentPriority >= otherPriority) {
            InsertThreadIntoTail(pThreadTblEnt[index].pThread, pThreadTblEnt[index].pThread->priority);
            pThreadTblEnt[index].pThread->status = THREAD_STATUS_READY;
        }
        *retval = &pThreadTblEnt[tid].pThread->exitCode;
        
        free(pThreadTblEnt[tid].pThread->stackAddr - STACK_SIZE);
        free(pThreadTblEnt[tid].pThread);
        pThreadTblEnt[tid].pThread = NULL;
        pThreadTblEnt[tid].bUsed = 0;

        return 0;
    } else if(pThreadTblEnt[tid].pThread->status == THREAD_STATUS_ZOMBIE) {
        *retval = &pThreadTblEnt[tid].pThread->exitCode;
        free(pThreadTblEnt[tid].pThread->stackAddr - STACK_SIZE);
        free(pThreadTblEnt[tid].pThread);
        pThreadTblEnt[tid].pThread = NULL;
        pThreadTblEnt[tid].bUsed = 0;
        
        return 0;
    }
}

int thread_exit(void *retval) {
    Thread *temp = pCurrentThread;

    temp->exitCode = 0;
    
    temp->status = THREAD_STATUS_ZOMBIE;
    pCurrentThread = NULL;

    Thread *newThread;
    for (int i = 0; i < MAX_READYQUEUE_NUM; i++) {
        if (pReadyQueueEnt[i].queueCount > 0) {
            newThread = pReadyQueueEnt[i].pHead;
            newThread->status = THREAD_STATUS_RUN;
            break;
        }
    }

    if(newThread != NULL) {
        __ContextSwitch(temp->pid, newThread->pid);
    }

    exit(1);
}

void signalHandler(int signum) {
    if(signum == SIGCHLD) {
        
    }
}
