#include "MsgQueue.h"
#include "AddMethod.h"
#include <string.h>
#include <stdio.h>

int printNum = 0;

pmqd_t pmq_open(const char* name, int flags, mode_t perm, pmq_attr* attr)
{
    int index = -1;

    for(int i = 0; i < MAX_QCB_NUM; i++) {
        if(strcmp(name, qcbTblEntry[i].name) == 0) {
            index = i;
            break;
        }
    }

    if(index == -1) { //같은 이름의 메시지 큐가 없는 경우
        for(int k = 0; k < MAX_QCB_NUM; k++) {
            if(qcbTblEntry[k].bUsed == 0) {
                qcbTblEntry[k].bUsed = 1;
                qcbTblEntry[k].openCount++;
                qcbTblEntry[k].mode = perm;
                strcpy(qcbTblEntry[k].name, name);
                Qcb* qcb = (Qcb*)malloc(sizeof(Qcb));
                qcb->msgCount = 0;
                qcb->pMsgHead = NULL;
                qcb->pMsgTail = NULL;
                qcb->waitThreadCount = 0;
                qcb->pWaitQHead = NULL;
                qcb->pWaitQTail = NULL;
                qcbTblEntry[k].pQcb = qcb;

                return k;
            }
        }
    } else if(index > -1) { //같은 이름의 메시지 큐가 있는 경우
        qcbTblEntry[index].openCount++;
        
        return index;
    }
}

int pmq_close(pmqd_t mqd)
{
    qcbTblEntry[mqd].openCount--;

    if(qcbTblEntry[mqd].openCount > 0) {
        return 0;
    } else if(qcbTblEntry[mqd].openCount == 0 && qcbTblEntry[mqd].pQcb->msgCount > 0) {
        return 0;
    } else if(qcbTblEntry[mqd].openCount == 0 && qcbTblEntry[mqd].pQcb->msgCount == 0) {
        free(qcbTblEntry[mqd].pQcb);
        qcbTblEntry[mqd].mode = -1;
        qcbTblEntry[mqd].bUsed = 0;
        
        char* name = "NULL";
        strcpy(qcbTblEntry[mqd].name, name);

        return 0;
    }
    return -1;
}

int pmq_send(pmqd_t mqd, char* msg_ptr, size_t msg_len, unsigned int msg_prio)
{
    Qcb* qcb = qcbTblEntry[mqd].pQcb;

    if(qcb->waitThreadCount == 0) { //waiting list에 스레드가 없는 경우
        Message* message = (Message*)malloc(sizeof(Message));
        memcpy(message->data, msg_ptr, msg_len);
        message->size = strlen(msg_ptr);
        message->priority = msg_prio;

        if(qcb->pMsgHead == NULL && qcb->pMsgTail == NULL) { //메시지 큐에 메시지가 없는 경우
            message->pNext = NULL;
            message->pPrev = NULL;

            qcb->pMsgHead = message;
            qcb->pMsgTail = message;
            qcb->msgCount++;

            //return 0;
        } else { //메시지 큐에 메시지가 있는 경우
            Message* tail = qcb->pMsgTail;
            Message* head = qcb->pMsgHead;

            if(msg_prio <= tail->priority) { //메시지가 메시지큐 꼬리의 우선순위보다 작음
                tail->pNext = message;
                message->pPrev = tail;
                message->pNext = NULL;
                qcb->pMsgTail = message;
                qcb->msgCount++;

                //return 0;
            } else if(msg_prio > head->priority) { //메시지가 메시지큐 Head의 우선순위보다 큼
                head->pPrev = message;
                message->pPrev = NULL;
                message->pNext = head;
                qcb->pMsgHead = message;
                qcb->msgCount++;

                //return 0;
            } else { //메시지가 메시지큐 중간에 들어가는 경우
                Message* prev = qcb->pMsgTail;

                while(msg_prio > prev->priority) {
                    prev = prev->pPrev;
                }
                Message* next = prev->pNext;

                message->pNext = next;
                message->pPrev = prev;
                prev->pNext = message;
                next->pPrev = message;

                qcb->msgCount++;

                //return 0;
            }
        }
        
        return 0;
    } else if(qcb->waitThreadCount > 0) { //waiting list에 스레드가 있는 경우
        Message* message = (Message*)malloc(sizeof(Message));
        memcpy(message->data, msg_ptr, msg_len);
        message->size = strlen(msg_ptr);
        message->priority = msg_prio;

        if(qcb->pMsgHead == NULL && qcb->pMsgTail == NULL) { //메시지 큐에 메시지가 없는 경우
            message->pNext = NULL;
            message->pPrev = NULL;

            qcb->pMsgHead = message;
            qcb->pMsgTail = message;
            qcb->msgCount++;
        } else { //메시지 큐에 메시지가 있는 경우
            Message* tail = qcb->pMsgTail;
            Message* head = qcb->pMsgHead;

            if(msg_prio <= tail->priority) { //메시지가 메시지큐 꼬리의 우선순위보다 작음
                tail->pNext = message;
                message->pPrev = tail;
                message->pNext = NULL;
                qcb->pMsgTail = message;
                qcb->msgCount++;
            } else if(msg_prio > head->priority) { //메시지가 메시지큐 Head의 우선순위보다 큼
                head->pPrev = message;
                message->pPrev = NULL;
                message->pNext = head;
                qcb->pMsgHead = message;
                qcb->msgCount++;
            } else { //메시지가 메시지큐 중간에 들어가는 경우
                Message* prev = qcb->pMsgTail;

                while(msg_prio > prev->priority) {
                    prev = prev->pPrev;
                }
                Message* next = prev->pNext;

                message->pNext = next;
                message->pPrev = prev;
                prev->pNext = message;
                next->pPrev = message;

                qcb->msgCount++;
            }
        }
            
        Thread* tempThread = qcb->pWaitQHead;
        tempThread->status = THREAD_STATUS_READY;
        int tempPriority = tempThread->priority;

        if(qcb->pWaitQHead == qcb->pWaitQTail) {
            qcb->pWaitQHead = NULL;
            qcb->pWaitQTail = NULL;
            qcb->waitThreadCount--;

            InsertThreadIntoTail(tempThread, tempPriority);
        } else {
            qcb->pWaitQHead = tempThread->phNext;
            qcb->pWaitQHead->phPrev = NULL;
            qcb->waitThreadCount--;
            tempThread->phNext = NULL;

            InsertThreadIntoTail(tempThread, tempPriority);
        }

        printNum = 1;

        return 0;
    }
}

ssize_t pmq_receive(pmqd_t mqd, char* msg_ptr, size_t msg_len, unsigned int* msg_prio)
{
    while(1) {
        Qcb* qcb = qcbTblEntry[mqd].pQcb;

        if(qcb->msgCount == 0) { //메시지큐에 메시지가 없는 경우
            pCurrentThread->status = THREAD_STATUS_WAIT;

            if(qcb->waitThreadCount == 0) {
                pCurrentThread->phNext = NULL;
                pCurrentThread->phPrev = NULL;
                qcb->pWaitQHead = pCurrentThread;
                qcb->pWaitQTail = pCurrentThread;
                qcb->waitThreadCount++;
            } else if(qcb->waitThreadCount > 0) {
                pCurrentThread->phPrev = qcb->pWaitQTail;
                pCurrentThread->phNext = NULL;
                qcb->pWaitQTail->phNext = pCurrentThread;
                qcb->pWaitQTail = pCurrentThread;
                qcb->waitThreadCount++;
            }
        
            Thread* temp = pCurrentThread;
            pCurrentThread = NULL;


            kill(temp->pid, SIGSTOP);

            if(qcb->msgCount == 0)
                continue;

            Message* headMessage = qcb->pMsgHead;

            if(qcb->msgCount == 1) {
                qcb->pMsgHead = NULL;
                qcb->pMsgTail = NULL;
            } else if(qcb->msgCount > 1) {
                qcb->pMsgHead = headMessage->pNext;
                qcb->pMsgHead->pPrev = NULL;
            }
            qcb->msgCount--;

            memcpy(msg_ptr, headMessage->data, msg_len);
            *msg_prio = headMessage->priority;
        
            int size = headMessage->size;
            free(headMessage);

            return size;
        } else if(qcb->msgCount > 0 && qcb->waitThreadCount > 0) {
            pCurrentThread->status = THREAD_STATUS_WAIT;

            if(qcb->waitThreadCount == 0) {
                pCurrentThread->phNext = NULL;
                pCurrentThread->phPrev = NULL;
                qcb->pWaitQHead = pCurrentThread;
                qcb->pWaitQTail = pCurrentThread;
                qcb->waitThreadCount++;
            } else if(qcb->waitThreadCount > 0) {
                pCurrentThread->phPrev = qcb->pWaitQTail;
                pCurrentThread->phNext = NULL;
                qcb->pWaitQTail->phNext = pCurrentThread;
                qcb->pWaitQTail = pCurrentThread;
                qcb->waitThreadCount++;
            }
        
            Thread* temp = pCurrentThread;
            pCurrentThread = NULL;


            kill(temp->pid, SIGSTOP);

            if(qcb->msgCount == 0)
                continue;

            Message* headMessage = qcb->pMsgHead;

            if(qcb->msgCount == 1) {
                qcb->pMsgHead = NULL;
                qcb->pMsgTail = NULL;
            } else if(qcb->msgCount > 1) {
                qcb->pMsgHead = headMessage->pNext;
                qcb->pMsgHead->pPrev = NULL;
            }
            qcb->msgCount--;

            memcpy(msg_ptr, headMessage->data, msg_len);
            *msg_prio = headMessage->priority;
        
            int size = headMessage->size;
            free(headMessage);

            return size;
        } else if(qcb->msgCount > 0 && qcb->waitThreadCount == 0) { //메시지큐에 메시지가 있는 경우
            Message* headMessage = qcb->pMsgHead;

            if(qcb->msgCount == 1) {
                qcb->pMsgHead = NULL;
                qcb->pMsgTail = NULL;
            } else if(qcb->msgCount > 1) {
                qcb->pMsgHead = headMessage->pNext;
                qcb->pMsgHead->pPrev = NULL;
            }
            qcb->msgCount--;

            memcpy(msg_ptr, headMessage->data, msg_len);
            *msg_prio = headMessage->priority;
        
            int size = headMessage->size;
            free(headMessage);

            printNum = 0;

            return size;
        }
    }
}
