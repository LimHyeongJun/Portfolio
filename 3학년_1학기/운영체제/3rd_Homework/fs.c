#include "fs.h"
#include "disk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

FileSysInfo* pFileSysInfo;

int CreateFile(const char *szFileName) {
    int freeInodeNum = GetFreeInodeNum();
    int parentInodeNum = 0;

    char* path = (char*)malloc(sizeof(szFileName));
    strcpy(path, szFileName);

    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    int totalSlashNum = slashNum;

    strcpy(path, szFileName);
    char* ptr = strtok(path, "/");

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                
                for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++)
                    memcpy(dirEntry + k, pBuf + (k * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 빈 곳에다가 파일 만듦.
                    int nullCount = 0;
                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, "NULL") == 0)
                            nullCount++;
                        if(strcmp(dirEntry[k].name, ptr) == 0) { //이미 같은 파일이 있으면 -1리턴
                            return -1;
                        }
                    }

                    if(nullCount == 0) //만약 꽉 찬 것이라면 null이 하나도 없다.
                        continue;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, "NULL") == 0) {
                            strcpy(dirEntry[k].name, ptr);
                            dirEntry[k].inodeNum = freeInodeNum;
                            DevWriteBlock(pInode->dirBlockPtr[i], (char*)dirEntry);

                            GetInode(freeInodeNum, pInode);
                            pInode->size = 0;
                            pInode->type = FILE_TYPE_FILE;
                            pInode->allocBlocks = 0;
                            for(int j = 0; j < NUM_OF_DIRECT_BLOCK_PTR; j++)
                                pInode->dirBlockPtr[j] = -1;
                            PutInode(freeInodeNum, pInode);

                            SetInodeBytemap(freeInodeNum);

                            FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                            char* temppBuf = malloc(BLOCK_SIZE);
                            DevReadBlock(0, temppBuf);
                            memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));
                            
                            fileSysInfo->numAllocInodes++;

                            memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                            memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                            DevWriteBlock(0, temppBuf);

                            free(fileSysInfo);
                            free(temppBuf);

                            free(pBuf);
                            free(dirEntry);

                            File* pFile = (File*)malloc(sizeof(File));
                            pFile->inodeNum = freeInodeNum;
                            pFile->fileOffset = 0;

                            for(int index = 0; index < MAX_FD_ENTRY_MAX; index++) {
                                if(pFileDesc[index].bUsed == 0) {
                                    pFileDesc[index].bUsed = 1;
                                    pFileDesc[index].pOpenFile = pFile;

                                    return index;
                                }
                            }
                        }
                    }
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else if(pInode->dirBlockPtr[i] == -1 && slashNum == 1) { //-1인 곳에 남는 블록 가져와서 만들어주고 거기에 파일 만든다.
                int freeBlockNum = GetFreeBlockNum();
                pInode->dirBlockPtr[i] = freeBlockNum;
                pInode->size += BLOCK_SIZE;
                pInode->allocBlocks++;
                PutInode(parentInodeNum, pInode);

                SetBlockBytemap(freeBlockNum);

                int plusFreeBlockNum = GetFreeBlockNum();

                DirEntry* ddirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                if(totalSlashNum == 1) {
                    char* name = ".";
                    memcpy(ddirEntry[0].name, name, sizeof(name));
                    ddirEntry[0].inodeNum = 0;
                    name = "NULL";
                    memcpy(ddirEntry[1].name, name, sizeof(name));
                    ddirEntry[1].inodeNum = -1;
                } else if(totalSlashNum > 1) {
                    char* ppp = (char*)malloc(BLOCK_SIZE);
                    DirEntry* ddd = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                    DevReadBlock(pInode->dirBlockPtr[0], ppp);
                    
                    for(int l = 0; l < NUM_OF_DIRENT_PER_BLOCK; l++)
                        memcpy(ddd + l, ppp + (l * sizeof(DirEntry)), sizeof(DirEntry));
                    
                    char* name = ".";
                    memcpy(ddirEntry[0].name, name, sizeof(name));
                    ddirEntry[0].inodeNum = ddd[0].inodeNum;
                    name = "..";
                    memcpy(ddirEntry[1].name, name, sizeof(name));
                    ddirEntry[1].inodeNum = ddd[1].inodeNum;
                    free(ddd);
                    free(ppp);
                }

                char* empty = "NULL";
                for(int n = 2; n < NUM_OF_DIRENT_PER_BLOCK; n++)
                    memcpy(ddirEntry[n].name, empty, sizeof(empty));

                for(int n = 0; n < NUM_OF_DIRENT_PER_BLOCK; n++) {
                    if(strcmp(ddirEntry[n].name, "NULL") == 0) {
                        memcpy(ddirEntry[n].name, ptr, sizeof(ptr));
                        ddirEntry[n].inodeNum = freeInodeNum;

                        DevWriteBlock(pInode->dirBlockPtr[i], (char*)ddirEntry);

                        Inode* tempInode = (Inode*)malloc(sizeof(Inode));

                        GetInode(freeInodeNum, tempInode);
                        tempInode->allocBlocks = 0;
                        tempInode->size = 0;
                        tempInode->type = FILE_TYPE_FILE;
                        for(int b = 0; b < NUM_OF_DIRECT_BLOCK_PTR; b++)
                            tempInode->dirBlockPtr[b] = -1;

                        PutInode(freeInodeNum, tempInode);

                        FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                        char* temppBuf = malloc(BLOCK_SIZE);
                        DevReadBlock(0, temppBuf);
                        memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                        memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));

                        fileSysInfo->numAllocBlocks++;
                        fileSysInfo->numFreeBlocks--;
                        fileSysInfo->numAllocInodes++;

                        memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                        DevWriteBlock(0, temppBuf);

                        free(temppBuf);
                        free(fileSysInfo);
                        free(tempInode);
                        free(ddirEntry);
                        free(pInode);
                        free(path);

                        return 0;
                    }
                }
            } else if(pInode->dirBlockPtr[i] == -1 && slashNum > 1)
                return -1;
        }

        if(!middleDir) { //중간 디렉토리가 없는 경우 -1리턴
            return -1;
        }
    }
}

int OpenFile(const char *szFileName) {   
    int parentInodeNum = 0;
    char* path = (char*)malloc(sizeof(szFileName));
    strcpy(path, szFileName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    strcpy(path, szFileName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++)
                    memcpy(dirEntry + k, pBuf + (k * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 빈 곳에다가 디렉토리 만듦.
                    bool existFile = false;
                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            existFile = true;
                            break;
                        }
                    }

                    if(!existFile)
                        continue;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            int inodeNum = dirEntry[k].inodeNum;
                            int index = -1;

                            for(int z = 0; z < MAX_FD_ENTRY_MAX; z++) {
                                if(pFileDesc[z].bUsed == 0) {
                                    index = z;
                                    break;
                                }
                            }

                            File* pFile = (File*)malloc(sizeof(File));
                            pFile->inodeNum = inodeNum;
                            pFile->fileOffset = 0;

                            pFileDesc[index].pOpenFile = pFile;
                            pFileDesc[index].bUsed = 1;

                            free(path);
                            free(tempPtr);
                            free(pInode);
                            free(pBuf);
                            free(dirEntry);

                            return index;
                        }
                    }
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else {
                break;
            }
        }

        if(!middleDir) { //중간 디렉토리가 없는 경우 -1리턴
            return -1;
        }
    }

    return -1; //여기까지 왔다는건 해당 이름으로 들어온 파일이 없다는 뜻
}

int WriteFile(int fileDesc, char *pBuffer, int length) {
    int plusBlock = 0;
    char* pBuf = malloc(BLOCK_SIZE);

    File* pFile = (File*)malloc(sizeof(File));
    pFile = pFileDesc[fileDesc].pOpenFile; //pFile에 inodeNum, offset있다.

    if(pFileDesc[fileDesc].pOpenFile == NULL) //열려있는 파일이 없으면 -1 리턴
        return -1;

    Inode* pInode = (Inode*)malloc(sizeof(Inode));
    GetInode(pFile->inodeNum, pInode); //pInode에 파일의 inode가 들어감.


    int index = pFile->fileOffset / BLOCK_SIZE; //dirBlockPtr[]안에 들어갈 것
    int location = pFile->fileOffset % BLOCK_SIZE; //블록에서 쓰기 시작할 위치
    int remainSpace = BLOCK_SIZE - location; //블록 안에 남은 공간
    int remainByte = 0; //써야할 남은 바이트
    if(length <= remainSpace && location == 0) {
        if(pInode->dirBlockPtr[index] == -1) {
            int freeBlockNum = GetFreeBlockNum();
            pInode->dirBlockPtr[index] = freeBlockNum;
            pInode->size += 512;
            pInode->allocBlocks += 1;
            PutInode(pFile->inodeNum, pInode);
            plusBlock++;
        }
        memcpy(pBuf, pBuffer, length);
        DevWriteBlock(pInode->dirBlockPtr[index], pBuf);
        SetBlockBytemap(pInode->dirBlockPtr[index]);
    } else if(length > remainSpace && location == 0) {
        remainByte = length - BLOCK_SIZE;
        if(pInode->dirBlockPtr[index] == -1) {
            int freeBlockNum = GetFreeBlockNum();
            pInode->dirBlockPtr[index] = freeBlockNum;
            pInode->size += 512;
            pInode->allocBlocks += 1;
            PutInode(pFile->inodeNum, pInode);
            GetInode(pFile->inodeNum, pInode);
            plusBlock++;
        }
        memcpy(pBuf, pBuffer, BLOCK_SIZE);
        DevWriteBlock(pInode->dirBlockPtr[index], pBuf);
        SetBlockBytemap(pInode->dirBlockPtr[index]);
        
        int i = remainByte / BLOCK_SIZE;
        for(int j = 0; j <= i; j++) {
            int plusFreeBlockNum = GetFreeBlockNum();
            index++;
            pInode->dirBlockPtr[index] = plusFreeBlockNum;
            memset(pBuf, 0, BLOCK_SIZE);

            if(j == i)
                memcpy(pBuf, pBuffer + BLOCK_SIZE + (j * BLOCK_SIZE), remainByte % BLOCK_SIZE);
            else if(j < i)
                memcpy(pBuf, pBuffer + BLOCK_SIZE + (j * BLOCK_SIZE), BLOCK_SIZE);

            plusBlock++;
            pInode->size += 512;
            pInode->allocBlocks++;
            PutInode(pFile->inodeNum, pInode);
            GetInode(pFile->inodeNum, pInode);
            DevWriteBlock(pInode->dirBlockPtr[index], pBuf);
            SetBlockBytemap(pInode->dirBlockPtr[index]);    
        }
    } else if(length <= remainSpace && location > 0) {
        DevReadBlock(pInode->dirBlockPtr[index], pBuf);
        memcpy(pBuf + location, pBuffer, length);
        DevWriteBlock(pInode->dirBlockPtr[index], pBuf);
    } else if(length > remainSpace && location > 0) {
        remainByte = length - remainSpace;
        DevReadBlock(pInode->dirBlockPtr[index], pBuf);
        memcpy(pBuf + location, pBuffer, remainSpace);
        DevWriteBlock(pInode->dirBlockPtr[index], pBuf);

        int i = remainByte / BLOCK_SIZE;
        for(int j = 0; j <= i; j++) {
            int freeBlockNum = GetFreeBlockNum();
            index++;
            pInode->dirBlockPtr[index] = freeBlockNum;
            memset(pBuf, 0, BLOCK_SIZE);

            if(j == i)
                memcpy(pBuf, pBuffer + remainSpace + (j * BLOCK_SIZE), remainByte % BLOCK_SIZE);
            else if(j < i)
                memcpy(pBuf, pBuffer + remainSpace + (j * BLOCK_SIZE), BLOCK_SIZE);

            plusBlock++;
            pInode->size += 512;
            pInode->allocBlocks++;
            PutInode(pFile->inodeNum, pInode);
            GetInode(pFile->inodeNum, pInode);
            DevWriteBlock(pInode->dirBlockPtr[index], pBuf);
            SetBlockBytemap(pInode->dirBlockPtr[index]);
        }
    }

    FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
    char* temppBuf = (char*)malloc(BLOCK_SIZE);
    DevReadBlock(0, temppBuf);
    memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));
                           
    fileSysInfo->numAllocBlocks += plusBlock;
    fileSysInfo->numFreeBlocks -= plusBlock;

    memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
    memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
    DevWriteBlock(0, temppBuf);
    
    pFile->fileOffset += length;
    pFileDesc[fileDesc].pOpenFile = pFile;
    
    free(pInode);
    free(temppBuf);
    free(fileSysInfo);
    free(pBuf);

    return length;
}

int ReadFile(int fileDesc, char *pBuffer, int length) {
    if(pFileDesc[fileDesc].pOpenFile == NULL)
        return -1;

    File* pFile = (File*)malloc(sizeof(File));
    pFile = pFileDesc[fileDesc].pOpenFile;
    
    Inode* pInode = (Inode*)malloc(sizeof(Inode));
    GetInode(pFile->inodeNum, pInode);

    int index = pFile->fileOffset / BLOCK_SIZE;
    int location = pFile->fileOffset / BLOCK_SIZE;
    int remainSpace = BLOCK_SIZE - location;
    int remainByte = 0;
    
    char* pBuf = (char*)malloc(BLOCK_SIZE);

    if(length <= remainSpace) {
        DevReadBlock(pInode->dirBlockPtr[index], pBuf);
        memcpy(pBuffer, pBuf + location, length);
    } else if(length > remainSpace) {
        remainByte = length - remainSpace;
        DevReadBlock(pInode->dirBlockPtr[index], pBuf);
        memcpy(pBuffer, pBuf + location, remainSpace);

        int i = remainByte / BLOCK_SIZE;
        
        for(int j = 0; j <= i; j++) {
            index++;
            memset(pBuf, 0, BLOCK_SIZE);
            DevReadBlock(pInode->dirBlockPtr[index], pBuf);

            if(j == i)
                memcpy(pBuffer + remainSpace + (j * BLOCK_SIZE), pBuf, remainByte % BLOCK_SIZE);
            else if(j < i)
                memcpy(pBuffer + remainSpace + (j * BLOCK_SIZE), pBuf, BLOCK_SIZE);
        }
    }

    pFile->fileOffset += length;
    pFileDesc[fileDesc].pOpenFile = pFile;
    
    free(pInode);
    free(pBuf);

    return length;
}

int CloseFile(int fileDesc) {
    if(pFileDesc[fileDesc].bUsed == 1) {
        free(pFileDesc[fileDesc].pOpenFile);
        pFileDesc[fileDesc].pOpenFile = NULL;
        pFileDesc[fileDesc].bUsed = 0;
    
        return 0;
    } else {
        return -1;
    }
}

int RemoveFile(const char *szFileName) {
    int parentInodeNum = 0;

    char* path = (char*)malloc(sizeof(szFileName));
    strcpy(path, szFileName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    int totalSlashNum = slashNum;
    
    strcpy(path, szFileName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++)
                    memcpy(dirEntry + k, pBuf + (k * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 ptr이  파일 이름이다.
                    bool existFile = false;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            existFile = true;
                            break;
                        }
                    }
                    
                    if(!existFile)
                        continue;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {                            
                            int deskIndex = 0;

                            for(int p = 0; p < MAX_FD_ENTRY_MAX; p++) {
                                if(pFileDesc[p].bUsed == 0)
                                    continue;
                                if(dirEntry[k].inodeNum == pFileDesc[p].pOpenFile->inodeNum) { //파일이 open되어 있는 경우
                                    free(path);
                                    free(pInode);
                                    free(pBuf);
                                    free(dirEntry);
                                    return -1;
                                }
                            }
                            char* nullName = "NULL";

                            int inodeNum = dirEntry[k].inodeNum;
                            Inode* tempInode = (Inode*)malloc(sizeof(Inode));
                            GetInode(inodeNum, tempInode);

                            memcpy(dirEntry[k].name, nullName, sizeof(nullName));
                            dirEntry[k].inodeNum = -1;
                            DevWriteBlock(pInode->dirBlockPtr[i], (char*)dirEntry);

                            DirEntry* tempDirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                            
                            for(int l = 0; l < NUM_OF_DIRENT_PER_BLOCK; l++) {
                                memcpy(tempDirEntry[l].name, nullName, sizeof(nullName));
                                tempDirEntry[i].inodeNum = -1;
                            }

                            for(int ind = 0; ind < tempInode->allocBlocks; ind++) {
                               ResetBlockBytemap(tempInode->dirBlockPtr[ind]);
                               DevWriteBlock(tempInode->dirBlockPtr[ind], (char*)tempDirEntry); 
                            }
                            
                            GetInode(inodeNum, tempInode);
                            tempInode->allocBlocks = 0;
                            tempInode->size = 0;
                            tempInode->type = -1;
                            for(int d = 0; d < NUM_OF_DIRECT_BLOCK_PTR; d++)
                                pInode->dirBlockPtr[d] = -1;

                            PutInode(inodeNum, tempInode);
                            ResetInodeBytemap(inodeNum);

                            free(tempInode);
                            free(tempDirEntry);

                            char* temppBuf = malloc(BLOCK_SIZE);


                            memset(temppBuf, 0, BLOCK_SIZE);
                            DevReadBlock(0, temppBuf);

                            FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                            memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));

                            fileSysInfo->numAllocBlocks -= pInode->allocBlocks;
                            fileSysInfo->numFreeBlocks += pInode->allocBlocks;
                            fileSysInfo->numAllocInodes--;

                            memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                            memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                            DevWriteBlock(0, temppBuf);

                            if(i > 0 && totalSlashNum == 1) { //i가 0보다 크면 dirBlockPtr[1~4]까지에서 빈 곳은 없애야 한다.
                                int emptyNum = 0;
                                for(int v = 0; v < NUM_OF_DIRENT_PER_BLOCK; v++) {
                                    if(strcmp(dirEntry[v].name,"NULL") == 0)
                                        emptyNum++;
                                }
                                if(emptyNum == 31) {                                    
                                    DirEntry* ppp = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                                    char* tempName = "NULL";

                                    for(int x = 0; x < NUM_OF_DIRENT_PER_BLOCK; x++) {
                                        memcpy(ppp[x].name, tempName, sizeof(tempName));
                                        ppp[x].inodeNum = -1;
                                    }

                                    DevWriteBlock(pInode->dirBlockPtr[i], (char*)ppp);
                                    free(ppp);

                                    ResetBlockBytemap(pInode->dirBlockPtr[i]);

                                    pInode->dirBlockPtr[i] = -1;
                                    pInode->allocBlocks--;
                                    pInode->size -= BLOCK_SIZE;
                                    PutInode(parentInodeNum, pInode);

                                    FileSysInfo* tempFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                                    char* ttt = malloc(BLOCK_SIZE);
                                    DevReadBlock(0, ttt);
                                    memcpy(tempFileSysInfo, ttt, sizeof(FileSysInfo));
                            
                                    tempFileSysInfo->numAllocBlocks--;
                                    tempFileSysInfo->numFreeBlocks++;

                                    memcpy(pFileSysInfo, tempFileSysInfo, sizeof(FileSysInfo));
                                    memcpy(ttt, tempFileSysInfo, sizeof(FileSysInfo));
                                    DevWriteBlock(0, ttt);

                                    free(tempFileSysInfo);
                                    free(ttt);
                                }                                
                            } else if(i > 0 && totalSlashNum > 1) {
                                int emptyNum = 0;
                                for(int v = 0; v < NUM_OF_DIRENT_PER_BLOCK; v++) {
                                    if(strcmp(dirEntry[v].name, "NULL") == 0)
                                        emptyNum++;
                                }

                                if(emptyNum == 30) {
                                    DirEntry* ppp = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                                    char* tempName = "NULL";

                                    for(int x = 0; x < NUM_OF_DIRENT_PER_BLOCK; x++) {
                                        memcpy(ppp[x].name, tempName, sizeof(tempName));
                                        ppp[x].inodeNum = -1;
                                    }
                                    
                                    DevWriteBlock(pInode->dirBlockPtr[i], (char*)ppp);
                                    free(ppp);

                                    ResetBlockBytemap(pInode->dirBlockPtr[i]);
                                    pInode->dirBlockPtr[i] = -1;
                                    pInode->allocBlocks--;
                                    pInode->size -= BLOCK_SIZE;
                                    PutInode(parentInodeNum, pInode);


                                    FileSysInfo* tempFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                                    char* ttt = malloc(BLOCK_SIZE);
                                    DevReadBlock(0, ttt);
                                    memcpy(tempFileSysInfo, ttt, sizeof(FileSysInfo));
                            
                                    tempFileSysInfo->numAllocBlocks--;
                                    tempFileSysInfo->numFreeBlocks++;

                                    memcpy(pFileSysInfo, tempFileSysInfo, sizeof(FileSysInfo));
                                    memcpy(ttt, tempFileSysInfo, sizeof(FileSysInfo));
                                    DevWriteBlock(0, ttt);

                                    free(tempFileSysInfo);
                                    free(ttt);
                                }
                            }
                                                    
                            free(path);
                            free(pInode);
                            free(pBuf);
                            free(dirEntry);
                            free(fileSysInfo);
                            free(temppBuf);

                            return 0;
                        }
                    }
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else {
                break;
            }
        }
    }
    return -1;
}

int MakeDir(const char *szDirName) {
    int freeBlockNum = GetFreeBlockNum();
    int freeInodeNum = GetFreeInodeNum(); //자기 자신 inode번호
    int parentInodeNum = 0; //자기 부모 inode 번호
    bool decide = true;

    char* path = malloc(sizeof(szDirName));
    strcpy(path, szDirName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    int totalSlashNum = slashNum;

    strcpy(path, szDirName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int index = 0; index < NUM_OF_DIRENT_PER_BLOCK; index++)
                    memcpy(dirEntry + index, pBuf + (index * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 빈 곳에다가 디렉토리 만듦.
                    bool isFull = false;
                    int allocNum = 0;
                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, "NULL") != 0)
                            allocNum++;
                    }
                    if(allocNum == 32)
                        continue;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, "NULL") == 0) {
                            memcpy(dirEntry[k].name, ptr, sizeof(ptr));
                            dirEntry[k].inodeNum = freeInodeNum;
                            DevWriteBlock(pInode->dirBlockPtr[i], (char*)dirEntry);
                            
                            char* temp = (char*)malloc(BLOCK_SIZE);
                            DirEntry* tempDir = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                            for(int b = 0; b < NUM_OF_DIRENT_PER_BLOCK; b++)
                                memcpy(tempDir + b, temp + (b * sizeof(DirEntry)), sizeof(DirEntry));

                            char* tempName = ".";
                            memcpy(tempDir[0].name, tempName, sizeof(tempName));
                            tempDir[0].inodeNum = freeInodeNum;
                            tempName = "..";
                            memcpy(tempDir[1].name, tempName, sizeof(tempName));
                            tempDir[1].inodeNum = parentInodeNum;
                            
                            tempName = "NULL";
                            for(int y = 2; y < NUM_OF_DIRENT_PER_BLOCK; y++) {
                                memcpy(tempDir[y].name, tempName, sizeof(tempName));
                                tempDir[y].inodeNum = -1;
                            }

                            DevWriteBlock(freeBlockNum, (char*)tempDir);

                            free(temp);
                            free(tempDir);
                            
                            Inode* ppInode = (Inode*)malloc(sizeof(Inode));
                            GetInode(freeInodeNum, ppInode);

                            ppInode->dirBlockPtr[0] = freeBlockNum;
                            for(int y = 1; y < NUM_OF_DIRECT_BLOCK_PTR; y++) {
                                ppInode->dirBlockPtr[y] = -1;
                            }
                            ppInode->allocBlocks = 1;
                            ppInode->size += 512;
                            ppInode->type = FILE_TYPE_DIR;
                            PutInode(freeInodeNum, ppInode);

                            free(ppInode);
                            SetBlockBytemap(freeBlockNum);
                            SetInodeBytemap(freeInodeNum);

                            FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                            char* temppBuf = malloc(BLOCK_SIZE);
                            DevReadBlock(0, temppBuf);
                            memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));
                            
                            fileSysInfo->numAllocBlocks++;
                            fileSysInfo->numFreeBlocks--;
                            fileSysInfo->numAllocInodes++;

                            memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                            memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                            DevWriteBlock(0, temppBuf);

                            free(fileSysInfo);
                            free(temppBuf);

                            free(pBuf);
                            free(dirEntry);

                            return 0;
                        }
                    }
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else if(pInode->dirBlockPtr[i] == -1 && slashNum == 1){
                pInode->dirBlockPtr[i] = freeBlockNum;
                pInode->size += BLOCK_SIZE;
                pInode->allocBlocks++;
                PutInode(parentInodeNum, pInode);

                SetBlockBytemap(freeBlockNum);

                int plusFreeBlockNum = GetFreeBlockNum();

                char* ppBuf = (char*)malloc(BLOCK_SIZE);
                DirEntry* ddirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                for(int m = 0; m < NUM_OF_DIRENT_PER_BLOCK; m++) {
                    memcpy(ddirEntry + m, ppBuf + (m * sizeof(DirEntry)), sizeof(DirEntry));
                }
                
                if(totalSlashNum == 1) { //root디렉토리에 바로 생성하는 경우                 
                    char* name = ".";
                    memcpy(ddirEntry[0].name, name, sizeof(name));
                    ddirEntry[0].inodeNum = 0;
                    name = "NULL";
                    memcpy(ddirEntry[1].name, name, sizeof(name));
                    ddirEntry[1].inodeNum = -1;
                } else { //더 들어가서 생성하는 경우
                    char* ppp = (char*)malloc(BLOCK_SIZE);
                    DirEntry* ddd = (DirEntry*)malloc(BLOCK_SIZE);
                    DevReadBlock(pInode->dirBlockPtr[0], ppp);

                    for(int l = 0; l < NUM_OF_DIRENT_PER_BLOCK; l++)
                        memcpy(ddd + l, ppp + (l * sizeof(DirEntry)), sizeof(DirEntry));

                    char* name = ".";
                    char* me = "..";
                    memcpy(ddirEntry[0].name, name, sizeof(name));
                    memcpy(ddirEntry[1].name, me, sizeof(me));
                    ddirEntry[0].inodeNum = ddd[0].inodeNum;
                    ddirEntry[1].inodeNum = ddd[1].inodeNum;

                    free(ddd);
                    free(ppp);
                }
                char* empty = "NULL";
                for(int n = 2; n < NUM_OF_DIRENT_PER_BLOCK; n++) {
                    memcpy(ddirEntry[n].name, empty, sizeof(empty));
                }

                for(int n = 0; n < NUM_OF_DIRENT_PER_BLOCK; n++) {
                    if(strcmp(ddirEntry[n].name, "NULL") == 0) {
                        memcpy(ddirEntry[n].name, ptr, sizeof(ptr));
                        ddirEntry[n].inodeNum = freeInodeNum;

                        DevWriteBlock(pInode->dirBlockPtr[i], (char*)ddirEntry);

                        char* temp = (char*)malloc(BLOCK_SIZE);
                        DirEntry* tempDir = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                        for(int b = 0; b < NUM_OF_DIRENT_PER_BLOCK; b++)
                            memcpy(tempDir + b, temp + (b * sizeof(DirEntry)), sizeof(DirEntry));

                        char* tempName = ".";
                        memcpy(tempDir[0].name, tempName, sizeof(tempName));
                        tempDir[0].inodeNum = freeInodeNum;
                        tempName = "..";
                        memcpy(tempDir[1].name, tempName, sizeof(tempName));
                        tempDir[1].inodeNum = parentInodeNum;
                        tempName = "NULL";

                        for(int t = 2; t < NUM_OF_DIRENT_PER_BLOCK; t++)
                            memcpy(tempDir[t].name, tempName, sizeof(tempName));

                        DevWriteBlock(plusFreeBlockNum, (char*)tempDir);

                        free(temp);
                        free(tempDir);

                        GetInode(freeInodeNum, pInode);
                        pInode->dirBlockPtr[0] = plusFreeBlockNum;
                        pInode->allocBlocks += 1;
                        pInode->size += 512;
                        pInode->type = FILE_TYPE_DIR;
                        PutInode(freeInodeNum, pInode);
                        SetBlockBytemap(plusFreeBlockNum);
                        SetInodeBytemap(freeInodeNum);

                        FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                        char* temppBuf = malloc(BLOCK_SIZE);
                        DevReadBlock(0, temppBuf);
                        memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));
                           
                        fileSysInfo->numAllocBlocks += 2;
                        fileSysInfo->numFreeBlocks -= 2;
                        fileSysInfo->numAllocInodes++;

                        memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                        memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                        DevWriteBlock(0, temppBuf);

                        free(temppBuf);
                        free(pInode);
                        free(path);
                        free(ppBuf);
                        free(ddirEntry);

                        return 0;
                    }
                }                
            } else if(pInode->dirBlockPtr[i] == -1 && slashNum > 1)
                return -1;
        }

        if(!middleDir) { //중간 디렉토리가 없는 경우 -1리턴
            return -1;
        }
    }
}

int RemoveDir(const char *szDirName) {
    int parentInodeNum = 0; //자기 부모 inode 번호
    bool decide = true;

    char* path = malloc(sizeof(szDirName));
    strcpy(path, szDirName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    int totalSlashNum = slashNum;
    
    strcpy(path, szDirName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int index = 0; index < NUM_OF_DIRENT_PER_BLOCK; index++)
                    memcpy(dirEntry + index, pBuf + (index * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 없앨 디렉토리 찾음
                    bool existDir = false;

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            existDir = true;
                            break;
                        }
                    }

                    if(!existDir) {
                        continue;
                    }

                    for(int k = 0; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            Inode* difInode = (Inode*)malloc(sizeof(Inode));
                            GetInode(dirEntry[k].inodeNum, difInode);

                            char* tempBuf = (char*)malloc(BLOCK_SIZE);
                            DevReadBlock(difInode->dirBlockPtr[0], tempBuf);

                            DirEntry* tempDirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                            for(int index = 0; index < NUM_OF_DIRENT_PER_BLOCK; index++)
                                memcpy(tempDirEntry + index, tempBuf + (index * sizeof(DirEntry)), sizeof(DirEntry));
                            for(int index = 2; index < NUM_OF_DIRENT_PER_BLOCK; index++) {
                                if(strcmp(tempDirEntry[index].name, "NULL") != 0) {
                                    free(tempBuf);
                                    free(tempDirEntry);
                                    free(path);
                                    free(pInode);
                                    free(pBuf);
                                    free(dirEntry);
                                    return -1;
                                }
                            }

                            memset(tempBuf, 0, BLOCK_SIZE);
                            DevWriteBlock(difInode->dirBlockPtr[0], tempBuf);
                            ResetBlockBytemap(difInode->dirBlockPtr[0]);

                            Inode* tempInode = (Inode*)malloc(sizeof(Inode));
                            tempInode->allocBlocks = 0;
                            tempInode->size = 0;
                            tempInode->type = -1;
                            for(int ind = 0; ind < 5; ind++)
                                tempInode->dirBlockPtr[ind] = -1;

                            PutInode(dirEntry[k].inodeNum, tempInode);
                            ResetInodeBytemap(dirEntry[k].inodeNum);

                            free(tempInode);
                            free(tempBuf);
                            free(tempDirEntry);
                            
                            char* nullName = "NULL";
                            memcpy(dirEntry[k].name, nullName, sizeof(nullName));
                            dirEntry[k].inodeNum = -1;
                            DevWriteBlock(pInode->dirBlockPtr[i], (char*)dirEntry);

                            FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                            char* temppBuf = malloc(BLOCK_SIZE);
                            DevReadBlock(0, temppBuf);
                            memcpy(fileSysInfo, temppBuf, sizeof(FileSysInfo));
                            
                            fileSysInfo->numAllocBlocks--;
                            fileSysInfo->numFreeBlocks++;
                            fileSysInfo->numAllocInodes--;

                            memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
                            memcpy(temppBuf, fileSysInfo, sizeof(FileSysInfo));
                            DevWriteBlock(0, temppBuf);

                            free(fileSysInfo);
                            free(temppBuf);

                            if(i > 0 && totalSlashNum == 1) { //i가 0보다 크면 dirBlockPtr[1~4]까지에서 빈 곳은 없애야 한다.
                                int emptyNum = 0;
                                for(int v = 0; v < NUM_OF_DIRENT_PER_BLOCK; v++) {
                                    if(strcmp(dirEntry[v].name,"NULL") == 0)
                                        emptyNum++;
                                }
                                if(emptyNum == 31) {                              
                                    DirEntry* ppp = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                                    char* tempName = "NULL";

                                    for(int x = 0; x < NUM_OF_DIRENT_PER_BLOCK; x++) {
                                        memcpy(ppp[x].name, tempName, sizeof(tempName));
                                        ppp[x].inodeNum = -1;
                                    }

                                    DevWriteBlock(pInode->dirBlockPtr[i], (char*)ppp);
                                    free(ppp);

                                    ResetBlockBytemap(pInode->dirBlockPtr[i]);
                                    pInode->dirBlockPtr[i] = -1;
                                    pInode->allocBlocks--;
                                    pInode->size -= BLOCK_SIZE;

                                    FileSysInfo* tempFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                                    char* ttt = malloc(BLOCK_SIZE);
                                    DevReadBlock(0, ttt);
                                    memcpy(tempFileSysInfo, ttt, sizeof(FileSysInfo));
                            
                                    tempFileSysInfo->numAllocBlocks--;
                                    tempFileSysInfo->numFreeBlocks++;

                                    memcpy(pFileSysInfo, tempFileSysInfo, sizeof(FileSysInfo));
                                    memcpy(ttt, tempFileSysInfo, sizeof(FileSysInfo));
                                    DevWriteBlock(0, ttt);

                                    free(tempFileSysInfo);
                                    free(ttt);
                                }                                
                            } else if(i > 0 && totalSlashNum > 1) {
                                int emptyNum = 0;
                                for(int v = 0; v < NUM_OF_DIRENT_PER_BLOCK; v++) {
                                    if(strcmp(dirEntry[v].name, "NULL") == 0)
                                        emptyNum++;
                                }

                                if(emptyNum == 30) {
                                    DirEntry* ppp = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

                                    char* tempName = "NULL";

                                    for(int x = 0; x < NUM_OF_DIRENT_PER_BLOCK; x++) {
                                        memcpy(ppp[x].name, tempName, sizeof(tempName));
                                        ppp[x].inodeNum = -1;
                                    }
                                    
                                    DevWriteBlock(pInode->dirBlockPtr[i], (char*)ppp);
                                    free(ppp);

                                    ResetBlockBytemap(pInode->dirBlockPtr[i]);
                                    pInode->dirBlockPtr[i] = -1;
                                    pInode->allocBlocks--;
                                    pInode->size -= BLOCK_SIZE;
                                    PutInode(parentInodeNum, pInode);


                                    FileSysInfo* tempFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
                                    char* ttt = malloc(BLOCK_SIZE);
                                    DevReadBlock(0, ttt);
                                    memcpy(tempFileSysInfo, ttt, sizeof(FileSysInfo));
                            
                                    tempFileSysInfo->numAllocBlocks--;
                                    tempFileSysInfo->numFreeBlocks++;

                                    memcpy(pFileSysInfo, tempFileSysInfo, sizeof(FileSysInfo));
                                    memcpy(ttt, tempFileSysInfo, sizeof(FileSysInfo));
                                    DevWriteBlock(0, ttt);

                                    free(tempFileSysInfo);
                                    free(ttt);
                                }
                            }

                            free(pBuf);
                            free(dirEntry);
                            free(path);
                            free(pInode);

                            return 0;
                        }
                    }
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else if(pInode->dirBlockPtr[i] == -1) {
                break;
            }
        }

        if(!middleDir) { //중간 디렉토리가 없는 경우 -1리턴
            return -1;
        }
    }
}

int EnumerateDirStatus(const char *szDirName, DirEntryInfo *pDirEntry, int dirEntrys) {
    int parentInodeNum = 0;
    char* path = (char*)malloc(sizeof(szDirName));
    strcpy(path, szDirName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    int totalSlashNum = slashNum;

    strcpy(path, szDirName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);
        bool middleDir = false;

        int fileCount = 0;

        bool last = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int index = 0; index < NUM_OF_DIRENT_PER_BLOCK; index++)
                    memcpy(dirEntry + index, pBuf + (index * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) { //slashNum이 1일 때 찾을 디렉토리 도착
                    if(totalSlashNum == 1) {
                        for(int k = 1; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                            if(strcmp(dirEntry[k].name, ptr) == 0) {
                                Inode* tempInode = (Inode*)malloc(sizeof(Inode));

                                GetInode(dirEntry[k].inodeNum, tempInode);
                                
                                for(int p = 0; p < tempInode->allocBlocks; p++) {
                                    char* tempBuf = (char*)malloc(BLOCK_SIZE);
                                    DirEntry* tempDir = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                                                                        
                                    DevReadBlock(tempInode->dirBlockPtr[p], tempBuf);

                                    for(int j = 0; j < NUM_OF_DIRENT_PER_BLOCK; j++)
                                        memcpy(tempDir + j, tempBuf + (j * sizeof(DirEntry)), sizeof(DirEntry));

                                    for(int o = 2; o < NUM_OF_DIRENT_PER_BLOCK; o++) {
                                        if(strcmp(tempDir[o].name, "NULL") != 0) {
                                            memcpy(pDirEntry[fileCount].name, tempDir[o].name, sizeof(tempDir[o].name));
                                            pDirEntry[fileCount].inodeNum = tempDir[o].inodeNum;
                                            Inode* ttt = (Inode*)malloc(sizeof(Inode));

                                            GetInode(tempDir[o].inodeNum, ttt);

                                            pDirEntry[fileCount].type = ttt->type;

                                            free(ttt);
                                            fileCount++;
                                        }
                                    }
                                    free(tempBuf);
                                    free(tempDir);
                                }

                                free(tempInode);
                                break;
                            }
                        }
                    } else if(totalSlashNum > 1) {
                        for(int k = 2; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                            if(strcmp(dirEntry[k].name, ptr) == 0) {
                                Inode* tempInode = (Inode*)malloc(sizeof(Inode));

                                GetInode(dirEntry[k].inodeNum, tempInode);
                                for(int p = 0; p < tempInode->allocBlocks; p++) {
                                    char* tempBuf = (char*)malloc(BLOCK_SIZE);
                                    DirEntry* tempDir = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                                    DevReadBlock(tempInode->dirBlockPtr[p], tempBuf);
                                    for(int j = 0; j < NUM_OF_DIRENT_PER_BLOCK; j++)
                                        memcpy(tempDir + j, tempBuf + (j * sizeof(DirEntry)), sizeof(DirEntry));

                                    for(int o = 2; o < NUM_OF_DIRENT_PER_BLOCK; o++) {
                                        if(strcmp(tempDir[o].name, "NULL") != 0) {
                                            memcpy(pDirEntry[fileCount].name, tempDir[o].name, sizeof(tempDir[o].name));
                                            pDirEntry[fileCount].inodeNum = tempDir[o].inodeNum;
                                            Inode* ttt = (Inode*)malloc(sizeof(Inode));

                                            GetInode(tempDir[o].inodeNum, ttt);

                                            pDirEntry[fileCount].type = ttt->type;
                                            free(ttt);
                                            fileCount++;
                                        }
                                    }
                                    free(tempBuf);
                                    free(tempDir);
                                }

                                free(tempInode);
                            }
                        }
                    }
                    last = true;
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else if(pInode->dirBlockPtr[i] == -1) {
                break;
            }
        }
        if(last) {
            return fileCount;
        }
        if(!middleDir)
            return -1;
    }
}

void CreateFileSystem() {
    FileSysInit();
    int freeBlockNum = GetFreeBlockNum();
    int freeInodeNum = GetFreeInodeNum();

    pFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
    
    for(int i = 0; i < 7; i++) {
        SetBlockBytemap(i);
    }

    for(int i = 0; i < MAX_FD_ENTRY_MAX; i++) {
        pFileDesc[i].bUsed = 0;
        pFileDesc[i].pOpenFile = NULL;
    }

    char* pBuf = (char*)malloc(BLOCK_SIZE);
    DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);

    for(int i = 0; i < NUM_OF_DIRENT_PER_BLOCK; i++) {
        memcpy(dirEntry + i, pBuf + (i * sizeof(DirEntry)), sizeof(DirEntry));
    }

    char* name = ".";
    memcpy(dirEntry[0].name, name, sizeof(name));
    dirEntry[0].inodeNum = freeInodeNum;
    char* empty = "NULL";
    for(int i = 1; i < NUM_OF_DIRENT_PER_BLOCK; i++) {
        memcpy(dirEntry[i].name, empty, sizeof(empty));
    }

    DevWriteBlock(freeBlockNum, (char*)dirEntry);

    for(int i = 0; i < NUM_OF_DIRENT_PER_BLOCK; i++) {
        memcpy(dirEntry[i].name, empty, sizeof(empty));
        dirEntry[i].inodeNum = -1;
    }

    for(int j = 8; j < 512; j++)
        DevWriteBlock(j, (char*)dirEntry);

    free(dirEntry);
    
    FileSysInfo* fileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
    memcpy(fileSysInfo, pBuf, sizeof(FileSysInfo));

    fileSysInfo->blocks = 512;
    fileSysInfo->rootInodeNum = freeInodeNum;
    fileSysInfo->diskCapacity = FS_DISK_CAPACITY;
    fileSysInfo->numAllocBlocks = 7;
    fileSysInfo->numFreeBlocks = 505;
    fileSysInfo->numAllocInodes = NUM_OF_INODE_PER_BLOCK * INODELIST_BLOCKS;
    fileSysInfo->blockBytemapBlock = BLOCK_BYTEMAP_BLOCK_NUM;
    fileSysInfo->inodeBytemapBlock = INODE_BYTEMAP_BLOCK_NUM;
    fileSysInfo->inodeListBlock = INODELIST_BLOCK_FIRST;
    fileSysInfo->dataRegionBlock = 7;

    fileSysInfo->numAllocBlocks++;
    fileSysInfo->numFreeBlocks--;
    fileSysInfo->numAllocInodes++;

    memcpy(pFileSysInfo, fileSysInfo, sizeof(FileSysInfo));
    memcpy(pBuf, fileSysInfo, sizeof(FileSysInfo));
    DevWriteBlock(0, pBuf);

    free(fileSysInfo);
    free(pBuf);

    SetBlockBytemap(freeBlockNum);

    SetInodeBytemap(freeInodeNum);

    Inode* pInode = (Inode*)malloc(sizeof(Inode));
    GetInode(0, pInode);
    pInode->dirBlockPtr[0] = freeBlockNum;
    for(int i = 1; i < NUM_OF_DIRECT_BLOCK_PTR; i++)
        pInode->dirBlockPtr[i] = -1;
    pInode->type = FILE_TYPE_DIR;
    pInode->size = 512;
    pInode->allocBlocks = 1;

    PutInode(0, pInode);
    
    Inode* tempInode = (Inode*)malloc(sizeof(Inode));

    for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++)
        tempInode->dirBlockPtr[i] = -1;
    tempInode->allocBlocks = 0;
    tempInode->size = 0;
    tempInode->type = 0;

    for(int i = 1; i < 64; i++)
        PutInode(i, tempInode);

    free(tempInode);
    free(pInode);
}

void OpenFileSystem() {
    DevOpenDisk();
    pFileSysInfo = (FileSysInfo*)malloc(sizeof(FileSysInfo));
    char* pBuf = (char*)malloc(BLOCK_SIZE);
    DevReadBlock(0, pBuf);
    memcpy(pFileSysInfo, pBuf, sizeof(FileSysInfo));
    free(pBuf);
}

void CloseFileSystem() {
    char* pBuf = (char*)malloc(BLOCK_SIZE);
    memset(pBuf, 0, BLOCK_SIZE);
    memcpy(pBuf, pFileSysInfo, sizeof(FileSysInfo));
    DevWriteBlock(0, pBuf);

    DevCloseDisk();

    free(pBuf);
    free(pFileSysInfo);
}

int GetFileStatus(const char* szPathName, FileStatus* pStatus) {
    int parentInodeNum = 0;
    char* path = (char*)malloc(sizeof(szPathName));
    strcpy(path, szPathName);
    int slashNum = 0;
    char* tempPtr = strtok(path, "/");

    while(tempPtr != NULL) {
        slashNum++;
        tempPtr = strtok(NULL, "/");
    }

    int totalSlashNum = slashNum;

    strcpy(path, szPathName);
    char* ptr = strtok(path, "/");

    Inode* pInode = (Inode*)malloc(sizeof(Inode));

    while(ptr != NULL) {
        GetInode(parentInodeNum, pInode);

        bool middleDir = false;

        bool find = false;

        for(int i = 0; i < NUM_OF_DIRECT_BLOCK_PTR; i++) {     
            if(pInode->dirBlockPtr[i] != -1) {
                char* pBuf = (char*)malloc(BLOCK_SIZE);
                DevReadBlock(pInode->dirBlockPtr[i], pBuf);
                DirEntry* dirEntry = (DirEntry*)malloc(sizeof(DirEntry) * NUM_OF_DIRENT_PER_BLOCK);
                for(int index = 0; index < NUM_OF_DIRENT_PER_BLOCK; index++)
                    memcpy(dirEntry + index, pBuf + (index * sizeof(DirEntry)), sizeof(DirEntry));

                bool breakDecide = false;

                if(slashNum > 1) {                    
                    for(int w = 0; w < NUM_OF_DIRENT_PER_BLOCK; w++)    {
                        if(strcmp(dirEntry[w].name, ptr) == 0) {
                            parentInodeNum = dirEntry[w].inodeNum;
                            breakDecide = true;
                            ptr = strtok(NULL, "/");
                            slashNum--;
                            middleDir = true;
                            break;
                        }
                    }
                } else if(slashNum == 1) {
                    bool isExist = false;
                    for(int k = 2; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            isExist = true;
                            break;
                        }
                    }

                    if(!isExist) 
                        continue;

                    for(int k = 2; k < NUM_OF_DIRENT_PER_BLOCK; k++) {
                        if(strcmp(dirEntry[k].name, ptr) == 0) {
                            Inode* tempInode = (Inode*)malloc(sizeof(Inode));

                            GetInode(dirEntry[k].inodeNum, tempInode);

                            pStatus->allocBlocks = tempInode->allocBlocks;
                            pStatus->size = tempInode->size;
                            pStatus->type = tempInode->type;
                            for(int q = 0; q < NUM_OF_DIRECT_BLOCK_PTR; q++) {
                                pStatus->dirBlockPtr[q] = tempInode->dirBlockPtr[q];
                            }
                            free(tempInode);

                            find = true;
                            breakDecide = true;
                            break;
                        }
                    }
                    slashNum--;
                }
                
                free(pBuf);
                free(dirEntry);
                if(breakDecide) {
                    break;
                }
            } else if(pInode->dirBlockPtr[i] == -1) {
                break;
            }
        }
        if(find)
            return 0;
        if(!middleDir)
            return -1;
        if(slashNum == 0 && !find)
            return -1;
    }
}

void FileSysInit(void) {
    char *pBuf = (char *)malloc(BLOCK_SIZE);

    DevCreateDisk();

    memset(pBuf, 0, sizeof(pBuf));

    for (int i = 0; i < 512; i++) {
        DevWriteBlock(i, pBuf);
    }

    free(pBuf);
}
