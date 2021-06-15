#include "Init.h"
#include "Scheduler.h"
#include "Thread.h"

void Init(void) {
    for (int i = 0; i < MAX_THREAD_NUM; ++i) {
        pThreadTblEnt[i].bUsed = 0;
        pThreadTblEnt[i].pThread = NULL;
    }

    for (int i = 0; i < MAX_READYQUEUE_NUM; ++i) {
        pReadyQueueEnt[i].queueCount = 0;
        pReadyQueueEnt[i].pHead = NULL;
        pReadyQueueEnt[i].pTail = NULL;
    }

    pWaitingQueueHead = NULL;
    pWaitingQueueTail = NULL;
    pCurrentThread = NULL;
}
