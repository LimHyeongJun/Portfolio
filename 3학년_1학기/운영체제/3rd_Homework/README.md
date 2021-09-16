
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
  * Directory Entry
    * 디렉토리 안에 저장되는 파일 또는 디렉토리에 관한 정보가 기록된다.
    * 이에 해당하는 구조체 DirEntry의 멤버변수는 아래와 같다.
      * `char name[12]` : 디렉토리 안에 저장되는 file or directory 이름
      * `int inodeNum` : file or directory의 inode 번호
    * FileType
      * file의 타입을 나타내는 구조체이다.
      * 종류에는 아래의 3가지가 있다.
        * `FILE_TYPE_FILE` : regular file
        * `FILE_TYPE_DIR` : directory file
        * `FILE_TYPE_DEV` : device file
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
* File Descriptor Table
  * 파일에 관한 정보를 저장하는 테이블이다.
  * 구조 및 설명
  
  <kbd><img src = "https://user-images.githubusercontent.com/48857568/133606486-e86e29ca-bd19-4b9b-9021-cb9dee200a94.JPG" width="500" height="350"></kbd>
  
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
* `void CreateFileSystem(void);`
  * 파일 시스템을 포맷하고 초기화하는 동작을 수행한다.
  * 순서는 다음과 같다.
    1. 파일시스템 초기화 단계이기 때문에 `FileSysInit()`을 통해 Block 0부터 Block 511까지 0으로 초기화 한다(디스크 초기화).
    2. 디스크 초기화 후, 루트 디렉토리를 생성하고,`FileSysInfo`를 초기화한다.
    3. `GetFreeBlockNum()`함수를 이용하여 Block bytemap의 byte 7부터 검색하여 free block을 검색한다. free block을 Block 7이라고 가정하겠다.
    4. `GetFreeInodeNum()`함수를 이용하여 Inode bytemap의 byte 0부터 검색하여 free inode를 검색한다. 여기선 Inode 0이라고 가정하겠다.
    5. Block 크기의 메모리를 할당받은 뒤 이를 DirEntry 구조체의 배열로 변환한다.
    6. DirEntry[0]의 변수들을 설정한다. name: ".", inode no: 0으로 설정해준다.(자신에 대한 directory인 "."과 빈 inode 번호인 0을 지정해준 것임)
    7. DirEntry 구조체 배열로 변환된 블록을 DevWriteBlock을 이용하여 Block 7에 저장한다.
    8. Block 크기의 메모리를 할당받아 FileSysInfo 형으로 변환 후 Block 0을 읽는다. 
    9. 디렉토리 한 개 할당, 블록 한 개 할당이기 때문에 numAllocBlocks++, numFreeBlocks--, numAllocInodes++를 수행해준다.
    10. 해당 블록을 DevWriteBlock을 이용하여 Block 0에 저장한다.
    11. `SetBlockBytemap(7)`과 `SetInodeBytemap(0)`을 호출하여 Block 7과 Inode 0을 사용했다고 표시해준다.
* `void OpenFileSystem(void);`
  * 파일 시스템을 포맷이 아닌, 전원을 켰을 때 파일시스템 사용에 앞서 이루어지는 동작이다. 실제 파일시스템에서는 복잡한 동작이 이루어진다.
  * 포맷 대신 가상 디스크를 open하는 동작만 수행한다.
* `void CloseFileSystem(void);`
  * 전원을 끌 때 호출되는 함수라고 간주하면 된다.
  * 가상 디스크 파일을 close 한다.
* `int MakeDir(const char* dirName);`
  * dirName의 디렉토리를 생성한다.
  * 패스의 깊이에 제한을 두지 않는다.
  * `MakeDir(“/dir1/dir2/dir3/dir4/…/dirN”)`이 있다고 했을 때 dirN을 생성할 때 dir4가 없다면 dir4를 생성하지 말고 실패해야 한다. 즉, 새로운 디렉토리는 반드시 부모 디렉토리가 존재할 때만 생성될 수 있다.
  * `MakeDir("/tmp")`를 예시로 들어 순서를 설명하겠다. 이 함수는 Root 디렉토리 블록에 "tmp" 디렉토리를 생성하는 것이다.
    1. `GetFreeBlockNum()` 함수를 이용하여 Block bytemap의 byte 7부터 free block을 검색한다. Block 8이라고 가정하겠다.
    2. `GetFreeInodeNum()`함수를 이용하여 Inode bytemap의 byte 0부터 검색하여 free inode를 검색한다. Inode 1이라고 가정하겠다.
    3. `GetInode(0, pInode)`를 사용하여 Root 디렉토리의 inode(0번)을 획득한다. Root 디렉토리 이므로 inode의 dirBlockPtr[0]에 7이 적혀있다.
    4. Block 7을 읽는다. 이 블록은 root 디렉토리의 블록이다. 이를 dirEntry 구조체 배열로 변환한다.
    5. DirEntry[1]의 변수들을 설정한다. name: "tmp", inode no: 1으로 설정해준다.(DirEntry[0]은 이미 root 디렉토리에 관한 것으로 저장되어 있음)
    6. Block 7을 디스크에 저장한다.
    7. Block 크기의 메모리를 할당받아 DirEntry 구조체 배열로 변환한다. 이를 dirEntry 구조체 배열로 변환한다.
    8. DirEntry[0]의 변수들은 name: ".", inode no: 1로 설정하고, DirEntry[1]의 변수들은 name: "..", inode no: 0으로 설정한다.(index 0번은 자기에 관한 것이고, index 1번은 부모인 root에 관한 것이다.)
    9. 변경된 블록은 DevWriteBlock을 사용하여 Block 8에 저장한다.
    10. `GetInode(1, pInode)`를 사용하여 tmp 디렉토리의 inode(1번)을 획득한다.
    11. pInode에서 dirBlockPtr[0]의 값을 8로 설정해준다.
    12. 변경된 pInode의 값을 `SetInode(1, pInode)`를 이용하여 디스크에 저장해준다.
    13. `SetBlockBytemap(8)`과 `SetInodeBytemap(1)`을 이용하여 사용한 Block과 Inode를 표시해준다.
    14. Block 크기의 메모리를 할당받아 FileSysInfo 형으로 변환 후 Block 0을 읽는다. 
    15. 디렉토리 한 개 할당, 블록 한 개 할당이기 때문에 numAllocBlocks++, numFreeBlocks--, numAllocInodes++를 수행해준다.
    16. 해당 블록을 DevWriteBlock을 이용하여 Block 0에 저장한다.
* `int CreateFile(const char* fileName);`
  * 해당 경로에 파일을 만드는 함수이다.
  * `CreateFile("/tmp/a.c")`를 한다고 가정하고 아래에 순서로 나타내겠다.
    1. `GetFreeInodeNum()`함수를 이용하여 Inode bytemap의 byte 0부터 검색하여 free inode를 검색한다. Inode 2이라고 가정하겠다.(0은 root, 1은 tmp에 쓰임. file에서는 Block bytemap에서 빈 블록을 할당하지 않음)
    2. `GetInode(0, pInode)`를 사용하여 Root 디렉토리의 inode(0번)을 획득한다. Root 디렉토리 이므로 inode의 dirBlockPtr[0]에 7이 적혀있다.
    3. Block 7을 읽는다. 이 블록은 root 디렉토리의 블록이다. 이를 dirEntry 구조체 배열로 변환한다.
    4. tmp의 inode 번호를 획득한다. DirEntry[1]의 name이 "tmp" 이므로 해당하는 inode를 획득한다. tmp는 inode가 1이다.
    5. `GetInode(1, pInode)`를 사용하여 tmp 디렉토리의 inode(1번)을 획득한다. tmp 디렉토리 이므로 inode의 dirBlockPtr[0]에 8이 적혀있다.
    6. Block 8을 읽는다. 이 블록은 root 디렉토리의 블록이다. 이를 dirEntry 구조체 배열로 변환한다.
    7. 디렉토리 블록에 "a.c"와 inode 번호를 추가한다. 현재 index 0은 ".", 1은 ".."으로 사용중이므로 dirEntry[2]에 name: "a.c", inode no: 2로 들어가게 된다.
    8. 변경한 tmp 디렉토리 블록을 디스크에 저장한다.
    9. `GetInode(2, pInode)`를 사용하여 a.c 파일의 inode(2번)을 획득한다.
    10. pInode에서 a.c 의 특성들을 설정한다.(file type : regular file, file size : 0 등)
    11.  변경된 pInode의 값을 `SetInode(2, pInode)`를 이용하여 디스크에 저장해준다.
    12. `SetInodeBytemap(2)`을 이용하여 사용한 Inode를 표시해준다.
    13. Block 크기의 메모리를 할당받아 FileSysInfo 형으로 변환 후 Block 0을 읽는다. 
    14. inode 1개 할당이기 때문에 numAllocInodes++를 수행해준다.
    15. FileSysInfo를 디스크에 저장한다.
    16. File Descriptor Table 의 index 0 부터 시작하여 빈 entry(bUsed = false)를 찾는다. index 0이라고 가정한다.
    17. Malloc 으로 File 객체를 할당하고 inodeNum은 a.c의 inode 번호인 2, fileOffset은 0으로 설정한다.
    18. entry 0의 bUsed를 true로 설정하고, 2와 0으로 바뀐 File 객체를 point하도록 한다.
    19. 마지막으로 빈 entry 번호였던 index 값인 0을 반환한다.
* `int WriteFile(int fileDesc, char* pBuffer, int length);`
  * fileDesc : fileDescriptor, pBuffer : 메모리 공간의 시작주소, length : 파일의 쓰고자하는 데이터 크기
  * `WriteFile(0, pBuf, BLOCK_SIZE)`라고 가정하고 아래에 순서로 나타내겠다.
    1. `GetFreeBlockNum()` 함수를 이용하여 Block bytemap의 byte 7부터 free block을 검색한다. Block 9이라고 가정하겠다.
    2. File Descriptor Table에서 fileDesc가 0인 file object의 inode 번호를 획득한다. a.c의 fileDesc가 0이였고 해당 File 객체의 inodeNum이 2였으므로 inode 번호 2를 획득한다.
    3. `GetInode(2, pInode)`를 이용하여 a.c의 Inode(2번)을 획득한다.
    4. Inode의 dirBlockPtr[0]을 free block으로 얻었던 9로 설정한다. 9는 데이터를 저장하기 위해 할당된 Block이다.
    5. 변경된 pInode의 값을 `SetInode(2, pInode)`를 이용하여 디스크에 저장해준다.
    6. Block 크기의 메모리를 할당받아 FileSysInfo 형으로 변환 후 Block 0을 읽는다. 
    7. Block이 할당되었기 때문에 numAllocBlocks++, numFreeBlocks를 수행해준다.
    8. 해당 블록을 DevWriteBlock을 이용하여 Block 0에 저장한다.
    9. File Descriptor Table의 index 0의 File 객체의 fileOffset은 512로 바꿔준다. BLOCK_SIZE가 512고 그 전의 fileOffset이 0이였으니 0 + 512 = 512가 되기 때문이다.
    10. BLOCK_SIZE의 메모리를 할당받아 이 메모리 공간에 pBuf의 데이터를 복사한다.
    11. 할당된 Block 9를 디스크로 저장한다. 
* `int ReadFile(int fileDesc, char* pBuffer, int length);`
  * 파일을 읽는 함수이다.
  * fileDesc : fileDescriptor(여기선 0이라고 가정), pBuffer : 읽어서 저장할 메모리 주소, length : 파일의 읽고자하는 데이터 크기
  * `ReadFile(0, pBuf, BLOCK_SIZE)`라고 가정하겠다. fileDesc가 0이니 File Descriptor Table의 index 0번을 본다. a.c 파일이 있고 inodeNum은 2, fileOffset은 1024라고 가정하고 순서를 아래에 설명하겠다.
    1. File Descriptor Table에서 index가 0인 File 객체를 읽는다. 
    2. fileOffset을 1024라고 가정했으니 1024 위치부터 BLOCK_SIZE인 512만큼 읽어야한다.
    3. `GetInode(2, pInode)`를 이용하여 a.c의 Inode(2번)을 획득한다.
    4. 1024라는 byte가 몇번째 블록에 있는지 검사해야 한다. 1024 / 512를 하면 2번째 블록이 나오게 되는 것을 알 수 있다. 그럼 a.c의 Inode에서 dirBlockDir[2]를 확인해서 block pointer를 획득하면 된다. dirBlockDir[0]이 9였으므로 index 2는 11이 되겠다.
    5. 블록 크기의 메모리를 할당하고, 이 메모리 공간으로 Block 11을 읽는다.
    6. 읽어진 메모리의 내용을 pBuf로 복사해준다.
    7. 512 byte만큼 읽어줬으니 fileOffset에 512만큼 더해줘야 한다.
    8. 읽은 파일 사이즈만큼 리턴해준다.
* `int CloseFile(int fileDesc);`
  * fileDesc를 가진 file을 닫는 것이다.
  * `CloseFile(0)`이라고 가정하고 순서를 아래에 나타내겠다.
    1. File Descriptor Table의 index 0의 bUsed를 false로 변환한다.
    2. File 객체 malloc 해놓은 것을 free시키고 주소값은 null로 바꿔준다.
* `int OpenFile(const char* fileName);`
  * 이미 생성된 fileName에 대해 열기 동작을 수행하는 함수이다.
  * `OpenFile("/tmp/a.c")`에 관해서 한다고 가정하고 아래에 순서를 나타내겠다.
    1. `GetInode(0, pInode)`를 이용하여 Root 디렉토리의 Inode(0번)을 획득한다.
    2. Inode 0의 dirBlockPtr[0]에 7이 있으므로 Block 7을 디스크에서 읽는다. 이 블록이 root 디렉토리가 된다.
    3. root 디렉토리 블록에서 "tmp"를 검색한다. 그 뒤 tmp의 inode 번호(1번)를 획득한다.
    4. `GetInode(1, pInode)`를 이용하여 tmp 디렉토리의 Inode(1번)을 획득한다.
    5. Inode 0의 dirBlockPtr[0]에 8이 있으므로 Block 8을 디스크에서 읽는다. 이 블록이 tmp 디렉토리가 된다.
    6. tmp 디렉토리 블록에서 "a.c"를 검색한다. 그 뒤 a.c의 inode 번호(2번)를 획득한다.
    7. File Descriptor Table에서 index 0부터 시작하여, 빈 entry(bUsed == false)를 찾는다. Index 0에서 찾았다고 가정한다.
    8. Malloc으로 File 객체를 할당한다.
    9. File 객체의 변수들을 설정한다. a.c의 inode번호가 2번이니 inodeNum은 2, fileOffset은 처음이니 0으로 설정한다.
    10. File Descriptor Table의 index 0의 bUsed는 true로 설정하고, Malloc한 File 객체를 가리키도록 한다.
    11. index 값을 반환해준다. Index 0이 빈 곳이였으므로 0을 반환해준다.
* `int RemoveDir(const char* dirName);`
  * 빈 디렉토리만 삭제할 수 있다. 즉 디렉토리에 한 개의 파일(or 디렉토리)가 있다면 삭제할 수 없다.
  * 만일 비어있지 않은 디렉토리를 삭제하고자 할 때는 -1을 반환한다.
  * Linux의 rmdir()와 동일한 동작을 수행한다.
* `int GetFileStatus(const char* pathName, FileStatus* pStatus);`
  * pathName이 지정하는 regular file 또는 directory file의 상태를 획득한다.
  * 성공하면 0, 실패하면 -1을 반환한다. 실패의 경우는 pathName이 지정하는 file이 없을 때이다.
  * FileStatus 구조체는 Inode 구조체와 똑같은 멤버 변수를 갖는다. 따라서 pathName이 지정하는 inode를 찾아서 해당하는 inode의 내용을 이 pStatus에 채워주면 된다.
