#include "AddMethod.h"
#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"

//해당 pThread를 pReadyQueueEnt[priority]의 tail에 넣고 queueCount 1증가
void InsertThreadIntoTail(Thread *pThread, int priority) {
    if (pReadyQueueEnt[priority].queueCount == 0) {
        pReadyQueueEnt[priority].pHead = pThread;
        pReadyQueueEnt[priority].pTail = pThread;
        pThread->phPrev = NULL;
        pThread->phNext = NULL;
        ++pReadyQueueEnt[priority].queueCount;
    } else {
        Thread *temp = pReadyQueueEnt[priority].pTail;
        pThread->phPrev = temp;
        pThread->phNext = NULL;
        temp->phNext = pThread;
        pReadyQueueEnt[priority].pTail = pThread;
        ++pReadyQueueEnt[priority].queueCount;
    }
}

void InsertThreadIntoWaitingQueue(Thread *pThread) {
    if (pWaitingQueueHead == NULL && pWaitingQueueTail == NULL) {
        pWaitingQueueHead = pThread;
        pWaitingQueueTail = pThread;
        pThread->phPrev = NULL;
        pThread->phNext = NULL;
    } else {
        pWaitingQueueTail->phNext = pThread;
        pThread->phPrev = pWaitingQueueTail;
        pThread->phNext = NULL;
        pWaitingQueueTail = pThread;
    }
}

// ready queue에서 인자로 받은 pThread를 없애는 작업만 한다.
BOOL DeleteThreadFromReadyQueue(Thread *pThread) {
    int priority = pThread->priority;

    if (pReadyQueueEnt[priority].queueCount == 1) {
        if (pReadyQueueEnt[priority].pHead->pid == pThread->pid) {
            pReadyQueueEnt[priority].pHead = NULL;
            pReadyQueueEnt[priority].pTail = NULL;
            --pReadyQueueEnt[priority].queueCount;

            return 1;
        } else
            return 0;
    } else if (pReadyQueueEnt[priority].queueCount > 1) {
        Thread *temp = pReadyQueueEnt[priority].pHead;

        for (int i = 0; i < pReadyQueueEnt[priority].queueCount; ++i) {
            if (pThread->pid != temp->pid) {
                temp = temp->phNext;
            } else if (pThread->pid == temp->pid) {
                if (i == 0) {
                    pReadyQueueEnt[priority].pHead = pThread->phNext;
                    pReadyQueueEnt[priority].pHead->phPrev = NULL;
                } else if (i == pReadyQueueEnt[priority].queueCount - 1) {
                    pReadyQueueEnt[priority].pTail = pThread->phPrev;
                    pReadyQueueEnt[priority].pTail->phNext = NULL;
                } else {
                    Thread *tempPrev = pThread->phPrev;
                    Thread *tempNext = pThread->phNext;
                    tempPrev->phNext = tempNext;
                    tempNext->phPrev = tempPrev;
                }

                pThread->phPrev = NULL;
                pThread->phNext = NULL;
                --pReadyQueueEnt[priority].queueCount;

                return 1;
            }
        }
    }
    return 0;
}

// waiting queue에서 인자로 받은 pThread를 없애는 작업만 한다
// pThread를 ready queue로 보내거나 running을 시키는 건 다른 곳에서 해야 한다.
BOOL DeleteThreadFromWaitingQueue(Thread *pThread) {
    if(pWaitingQueueHead == pThread && pWaitingQueueTail == pThread) {
        pWaitingQueueHead = NULL;
        pWaitingQueueTail = NULL;
    }
    else if (pThread == pWaitingQueueHead) {
        pWaitingQueueHead = pThread->phNext;
        pWaitingQueueHead->phPrev = NULL;
    } else if (pThread == pWaitingQueueTail) {
        pWaitingQueueTail = pThread->phPrev;
        pWaitingQueueTail->phNext = NULL;
    } else {
        Thread *tempPrev = pThread->phPrev;
        Thread *tempNext = pThread->phNext;
        tempPrev->phNext = tempNext;
        tempNext->phPrev = tempPrev;
    }
    pThread->phNext = NULL;
    pThread->phPrev = NULL;

    return 1;
}
