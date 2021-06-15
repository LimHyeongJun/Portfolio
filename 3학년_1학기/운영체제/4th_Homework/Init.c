#include "Init.h"
#include "Thread.h"
#include "Scheduler.h"
#include "MsgQueue.h"
#include <string.h>


void Init(void)
{
    char* name = "NULL";
    for(int i = 0; i < MAX_QCB_NUM; i++) {
        memcpy(qcbTblEntry[i].name, name, sizeof(name));
        qcbTblEntry[i].mode = -1;
        qcbTblEntry[i].openCount = 0;
        qcbTblEntry[i].pQcb = NULL;
        qcbTblEntry[i].bUsed = 0;
    }

    for(int i = 0; i < MAX_READYQUEUE_NUM; i++) {
        pReadyQueueEnt[i].queueCount = 0;
        pReadyQueueEnt[i].pHead = NULL;
        pReadyQueueEnt[i].pTail = NULL;
    }

    for(int i = 0; i < MAX_THREAD_NUM; i++) {
        pThreadTblEnt[i].bUsed = 0;
        pThreadTblEnt[i].pThread = NULL;
    }

    pWaitingQueueHead = NULL;
    pWaitingQueueTail = NULL;
    pCurrentThread = NULL;
}
