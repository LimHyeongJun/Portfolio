## Implementing The Relation of File System & Disk
* 개발 환경 : C / Ubuntu 18.04 (VMware)
* 전체적인 구조

<kbd><img src = "https://user-images.githubusercontent.com/48857568/133430963-044d3434-3a95-4a66-a58f-1d2bf4bc3c2b.JPG" width="500" height="350"></kbd>

###  Problem Description
* C언어를 이용하여 File System & Disk의 Relation을 구현한다.
* 위의 사진에서 각 블록은 다음과 같다.
  * `Block 0` : FileSystem 의 전체적인 정보가 들어있다. super block
    * `Block 1` : inode의 상태를 나태내는 inode bytemap
    * `Block 2` : block의 상태를 나타내는 block bytemap
    * `Block 3 ~ 6` : inode list가 배치됨
    * `Block 7 ~ n-1` : data 또는 data region이 배치된다.
* Free Space의 관리는 Byte vector를 이용한다.
  * byte[i]가 0이면 block i가 비어있고, byte[i]가 1이면 block i가 할당되어 있는 것이다.
  * 사이즈가 12인 block에 block 2, 3, 4, 5, 8, 9, 12가 할당되어 있으면 0011110011001 로 나타낸다.
* Block Disk Layout
  * 구조
    
  <kbd><img src = "https://user-images.githubusercontent.com/48857568/133432642-ff7ab79f-52d0-4189-9d97-758ab6c3d624.JPG" width="500" height="180"></kbd>
  * FileSys information
    * 파일시스템의 정보를 관리하는 Block
    * 생성된 Inode의 개수, 전체 디스크에서 할당된 Data block의 개수
    * FileSysInfo 구조체를 통해 구현된다.
    * FileSysInfo 멤버변수는 아래와 같다.
      * `int blocks` :  디스크에 저장된 전체 블록 개수
      * `int rootInodeNum` : 루트 inode의 번호
      * `int diskCapacity` : 디스크 용량(byte단위)
      * `int numAllocBlocks` : 파일 또는 디렉토리에 할당된 블록 개수
      * `int numFreeBlocks` : 할당되지 않은 블록 개수
      * `int numAllocInodes` : 할당된 Inode 개수
      * `int blockMapBlock` : block bytemap의 시작 블록 번호. 여기선 2임
      * `int inodeMapBlock` : inode bytemap의 시작 블록 번호. 여기선 1임
      * `int inodeListBlock` : inode list의 시작 블록 번호
    * 전체 Block 개수 = Block bytemap의 byte개수 = 512개
    * Data region의 블록 개수 = 512 - 7개 블록(Block 0~6) = 505개
  * Inode bytemap
    * inode 상태(할당 또는 비할당)에 대한 정보를 기록
    * 예로, inode 0이 할당되면, byte 0은 1로 설정. inode 10이 할당되면 byte 10이 1로 설정
  * Block bytemap
    * block 상태(할당 또는 비할당)에 대한 정보를 기록
    * 예로, block 20이 할당되면 byte 20은 1로 설정됨
* Inode List
  * 구조
    
  <kbd><img src = "https://user-images.githubusercontent.com/48857568/133432192-98e308fe-aec7-4ff0-8c4f-71a778ee92ba.JPG" width="500" height="220"></kbd>
  * Inode list
     * Inode들을 관리하는 목록
  * Inode 구조체
    * 파일을 대표하는 객체, 즉 파일 정보를 저장하는 객체
    * 파일에 포함되는 블록의 위치를 저장함. 크기는 32 bytes
    * Block 당 Inode 개수 = Block size / 32 bytes = `16개`, Block size = 512
    * 전제 inode 개수 = Block 당 Inode 개수 * Block 개수 → 16 * 4 = `64개`
    * 멤버 변수는 아래와 같다.
      * `int allocBlocks` : 할당된 블록 개수
      * `int size` : 파일 크기(byte 단위)
      * `FileType type` : 파일 타입. FileType형도 따로 정의되어 있다.
      * `int DirBlkPtr[NUM_OF_DIRECT_BLOCK_PTR]` : Direct block pointers

* 다음 2개의 함수는 제공된다.
  * `DevReadBlock(int blkno, char* pBuf);` : 특정블록의 번호를 입력하고 그 블록에 대한 데이터를 파일에서 읽어서 파일시스템으로 전달한다.
  * `DevWriteBlock(int blkno, char* pBuf);` : 해당하는 버퍼에 있는 데이터를 파일로 저장한다.

<hr></hr>

###  구현함수
* `void FileSysInit(void)`
  * FileSys information, inode bytemap, block bytemap, inode list를 0으로 채워서 초기화한다.
  * 블록 크기의 메모리를 할당 받은 후 0으로 채우고 디스크로 저장하면 된다.
* `void SetInodeBytemap(int inodeno);`
  * Inode bytemap에서 byte inodeno를 1로 설정하고, 다시 디스크로 저장한다.
  * Inode bytemap은 block 1에 저장된다.
  * 순서
    1. Block 크기의 메모리 할당
    2. Block 1을 DevReadBlock 함수를 통해 메모리로 읽음
    3. inodeno를 가진 byte를 1로 설정함
    4. Block 1에 DevWriteBlock 함수를 통해 저장함
* `void ResetInodeBytemap(int inodeno);`
  * Inode bytemap에서 byte 6을 0으로 설정하고, 다시 디스크로 저장한다.
  * Inode bytemap은 block 1에 저장된다.
  * 순서는 SetInodeBytemap 함수와 동일하다. 다만 c번에서 byte를 0으로 설정한다.
* `void SetBlockBytemap(int blkno);`
  * Block bytemap에서 blkno의 번호를 가진 byte를 1로 설정하고, 다시 디스크로 저장한다.
  * Block bytemap은 block 2에 저장된다.
  * 순서는 SetInodeBytemap 함수와 동일하다. 다만 d번에서 Block 2로 저장한다.
* `void ResetBlockBytemap(int blkno);`
  * Block bytemap에서 blkno의 번호를 가진 byte를 0로 설정하고, 다시 디스크로 저장한다.
  * Block bytemap은 block 2에 저장된다.
  * 순서는 SetInodeBytemap 함수와 동일하다. c번에서 byte를 0으로 설정하고, d번에서 block 2에 저장한다.
* `void GetInode(int inodeno, Inode* pInode);`
  * inodeno 번호를 가진 Inode를 디스크에서 읽어서 pInode가 지정하는 메모리 공간으로 저장한다.
  * 순서는 아래와 같다
    1. Block 크기의 메모리 할당
    2. inodeno의 번호의 번호를 갖는 Inode가 저장된 Block 번호를 구한다. 예를 들어 inode 0이라고 가정해본다. inode에 관한 block은 3부터 시작되므로 inode 0은 block 3에 있으니 Block 번호는 3이 된다.
    3. 위에서 구한 Block 번호를 DevReadBlock 함수를 통해 메모리로 읽는다. 여기선 Block 3을 읽는다.
    4. inodeno의 번호를 갖는 Inode의 내용을 pInode로 복사한다. 여기선 inode 0의 내용을 pInode로 복사한다.
* `void PutInode(int inodeno, Inode* pInode);`
  * pInode 메모리 공간 안에 저장된 정보를 inodeno 번호를 가진 Inode의 위치로 저장한다.
  * 순서는 GetInode와 같다. 다만 pInode에 내용을 가져오는 것이 아니라 pInode에 있는 내용을 디스크에 저장하는 것이다.
* `int GetFreeInodeNum(void);`
  * 할당되지 않은 inode 번호를 획득한다.
  * Byte 0부터 1씩 증가하면서 0을 가지는 byte를 찾아서 return한다.
* `int GetFreeBlockNum(void);`
  * 할당되지 않은 Block 번호를 획득한다.
  * Byte 0부터 1씩 증가하면서 0을 가지는 byte를 찾아서 return한다.
