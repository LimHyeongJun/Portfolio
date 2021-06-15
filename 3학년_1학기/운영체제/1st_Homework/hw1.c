#include "hw1.h"
#include <stdlib.h>

void Init() {
	pFreeListHead = NULL;
	ppFreeListTail = NULL;

	for (int i = 0; i < HASH_TBL_SIZE; ++i) {
		pHashTableEnt[i].elmtCount = 0;
		pHashTableEnt[i].pHead = NULL;
		pHashTableEnt[i].pTail = NULL;
	}
}

void InsertObjectToTail(Object *pObj, int ObjNum) {
	int index = ObjNum % HASH_TBL_SIZE;
	pObj->objnum = ObjNum;

	if (pHashTableEnt[index].elmtCount == 0) {
		pHashTableEnt[index].pHead = pObj;
		pHashTableEnt[index].pTail = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
		++pHashTableEnt[index].elmtCount;
	}
	else {
		Object *temp = pHashTableEnt[index].pTail;
		pObj->phPrev = temp;
		pObj->phNext = NULL;
		temp->phNext = pObj;
		pHashTableEnt[index].pTail = pObj;
		++pHashTableEnt[index].elmtCount;
	}
}

void InsertObjectToHead(Object *pObj, int objNum) {
	int index = objNum % HASH_TBL_SIZE;
	pObj->objnum = objNum;

	if (pHashTableEnt[index].elmtCount == 0) { 
		pHashTableEnt[index].pHead = pObj;
		pHashTableEnt[index].pTail = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
		++pHashTableEnt[index].elmtCount;
	}
	else {
		Object *temp = pHashTableEnt[index].pHead;
		pObj->phPrev = NULL;
		pObj->phNext = temp;
		temp->phPrev = pObj;
		pHashTableEnt[index].pHead = pObj;
		++pHashTableEnt[index].elmtCount;
	}
}

Object *GetObjectByNum(int objnum) {
	int index = objnum % HASH_TBL_SIZE;
	Object *temp = pHashTableEnt[index].pHead;

	if (temp == NULL) 
		return NULL;

	for (int i = 0; i < pHashTableEnt[index].elmtCount; ++i) {
		if (temp->objnum == objnum) 
			return temp; 
		else 
			temp = temp->phNext;
	}
	return NULL;
}

Object *GetObjectFromObjFreeList() {
	if (ppFreeListTail == NULL) 
		return NULL;
	else if (pFreeListHead == ppFreeListTail) {
		Object* temp = pFreeListHead;
		pFreeListHead = NULL;
		ppFreeListTail = NULL;
		return temp;
	}

	Object *temp = ppFreeListTail->phPrev;
	temp->phNext = NULL;
	Object *pObj = ppFreeListTail;
	ppFreeListTail = temp;
	return pObj;
}

BOOL DeleteObject(Object *pObj) { 
	if (pObj == NULL) 
		return 0;

	int index = pObj->objnum % HASH_TBL_SIZE;
	
	if (pHashTableEnt[index].elmtCount == 0)
		return 0;
	else if (pHashTableEnt[index].elmtCount == 1) { 
		if (pObj->objnum == pHashTableEnt[index].pHead->objnum) {
			pHashTableEnt[index].pHead = NULL;
			pHashTableEnt[index].pTail = NULL;
			--pHashTableEnt[index].elmtCount;
			return 1;
		}
		else {
			return 0;
		}
	} else { 
		Object* temp = pHashTableEnt[index].pHead;
		for (int i = 0; i < pHashTableEnt[index].elmtCount; ++i) {
			if (pObj->objnum != temp->objnum)
				temp = temp->phNext;
			else { 
				if (i == 0) {
					pHashTableEnt[index].pHead = temp->phNext;
					pHashTableEnt[index].pHead->phPrev = NULL;
					temp->phNext = NULL;
					--pHashTableEnt[index].elmtCount;
					return 1;
				} else if (i == pHashTableEnt[index].elmtCount - 1) {
					pHashTableEnt[index].pTail = temp->phPrev;
					pHashTableEnt[index].pTail->phNext = NULL;
					temp->phPrev = NULL;
					--pHashTableEnt[index].elmtCount;
					return 1;
				} else { 
					Object *tempPrev = temp->phPrev;
					Object *tempNext = temp->phNext;
					tempPrev->phNext = tempNext;
					tempNext->phPrev = tempPrev;
					temp->phNext = NULL;
					temp->phPrev = NULL;
					--pHashTableEnt[index].elmtCount;
					return 1;
				}
			}
		}
	}
	return 0;
}

void InsertObjectIntoObjFreeList(Object *pObj) {
	if (pFreeListHead == NULL && ppFreeListTail == NULL) { 
		pFreeListHead = pObj;
		ppFreeListTail = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = NULL;
	}
	else {
		pFreeListHead->phPrev = pObj;
		pObj->phPrev = NULL;
		pObj->phNext = pFreeListHead;
		pFreeListHead = pObj;
	}
}
