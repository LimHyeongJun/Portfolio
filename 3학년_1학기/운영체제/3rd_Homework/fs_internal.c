#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "disk.h"
#include "fs.h"

void SetInodeBytemap(int inodeno)
{
    char* pBuf = malloc(BLOCK_SIZE);
    DevReadBlock(1, pBuf);

    pBuf[inodeno] = 1;
    DevWriteBlock(1, pBuf);

    free(pBuf);
}


void ResetInodeBytemap(int inodeno)
{
    char* pBuf = malloc(BLOCK_SIZE);
    DevReadBlock(1, pBuf);

    pBuf[inodeno] = 0;
    DevWriteBlock(1, pBuf);

    free(pBuf);
}


void SetBlockBytemap(int blkno)
{
    char* pBuf = malloc(BLOCK_SIZE);
    DevReadBlock(2, pBuf);

    pBuf[blkno] = 1;
    DevWriteBlock(2, pBuf);

    free(pBuf);
}

void ResetBlockBytemap(int blkno)
{
    char* pBuf = malloc(BLOCK_SIZE);
    DevReadBlock(2, pBuf);

    pBuf[blkno] = 0;
    DevWriteBlock(2, pBuf);

    free(pBuf);
}


void PutInode(int inodeno, Inode* pInode)
{
    char* pBuf = malloc(BLOCK_SIZE);
    int index = inodeno / NUM_OF_INODE_PER_BLOCK;

    index = 3 + index;
    DevReadBlock(index, pBuf);

    Inode* inode = (Inode*)malloc(sizeof(Inode) * 16);

    for(int i = 0; i < 16; i++) {
        memcpy(inode + i, pBuf + (i * 32), sizeof(Inode));
    }

    int number = inodeno % NUM_OF_INODE_PER_BLOCK;
    memcpy(inode + number, pInode, sizeof(Inode));

    DevWriteBlock(index, (char*)inode);

    free(inode);
    free(pBuf);
}


void GetInode(int inodeno, Inode* pInode)
{
    char* pBuf = malloc(BLOCK_SIZE);
    int index = inodeno / NUM_OF_INODE_PER_BLOCK;
    
    index = 3 + index;

    DevReadBlock(index, pBuf);

    Inode* inode = (Inode*)malloc(512);

    for(int i = 0; i < NUM_OF_INODE_PER_BLOCK; i++) {
        memcpy(inode + i, pBuf + (i * sizeof(Inode)), sizeof(Inode));
    }

    int number = inodeno % NUM_OF_INODE_PER_BLOCK;

    memcpy(pInode, inode + number, sizeof(Inode));

    free(inode);
    free(pBuf);
}


int GetFreeInodeNum(void)
{
    char* pBuf = malloc(BLOCK_SIZE);

    DevReadBlock(1, pBuf);
    for(int i = 0; i < BLOCK_SIZE; i++) {
        if(pBuf[i] == 0) {
            free(pBuf);
            return i;
        }
    }

    free(pBuf);
    return -1;
}


int GetFreeBlockNum(void)
{
    char* pBuf = malloc(BLOCK_SIZE);
    DevReadBlock(2, pBuf);

    for(int i = 7; i < BLOCK_SIZE; i++) {
        if(pBuf[i] == 0) {
            free(pBuf);
            return i;
        }
    }

    free(pBuf);
    return -1;
}
