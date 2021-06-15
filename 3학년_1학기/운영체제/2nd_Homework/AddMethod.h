#ifndef __ADDMETHOD_H__
#define __ADDMETHOD_H__

#include "Thread.h"

void InsertThreadIntoTail(Thread *pThread, int priority);
void InsertThreadIntoWaitingQueue(Thread *pThread);
BOOL DeleteThreadFromReadyQueue(Thread *pThread);
BOOL DeleteThreadFromWaitingQueue(Thread *pThread);

#endif
