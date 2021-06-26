/*
 * Student ID: 2016726082
 * Name: 임형준
 */
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX_PATH_LEN 1024

// void myError(const char *msg);
void fileMode(const struct stat *fileInfo);
void fileType(const struct stat *fileInfo);

int main(int argc, const char *argv[]) {
    struct stat
        fileInfo; // stat()함수에 들어갈 파일 정보 저장할 메모리 공간 포인터
    struct passwd *userInfo;    // UID로 사용자 정보 읽기 위한 변수
    char cwd[MAX_PATH_LEN + 1]; //작업 디렉토리 얻기 위한 변수

    DIR *dirp;              //디렉토리 스트림 핸들
    struct dirent *dirInfo; //입력된 디렉토리에 관한 변수

    printf("Directory to search: %s\n", argv[1]);

    if (argc != 2) { //터미널 상에서 입력해야되는 방법 설명
        printf("Usage: %s [pathname]\n", argv[0]);
        exit(-1);
    }

    dirp = opendir(
        argv[1]); //입력된 디렉토리의 정보를 읽고 디렉토리 스트림 핸들 반환

    if (chdir(argv[1]) == -1) { //입력된 디렉토리로 작업 디렉토리 변경
        perror("chdir() error!"); //오류 발생하면 에러 메시지 출력
        exit(-1);
    }

    if (getcwd(cwd, MAX_PATH_LEN) == NULL) { //현재 작업 디렉토리 경로를 얻음.
        perror("getcwd() error!"); //오류 발생하면 에러 메시지 출력
        exit(-1);
    }

    if (stat(cwd, &fileInfo) ==
        -1) { //현재 작업 디렉토리 정보를 읽고, fileInfo 메모리 공간에 저장
        perror("stat() error!"); //오류 발생하면 에러 메시지 출력
        exit(-1);
    }

    while ((dirInfo = readdir(dirp)) !=
           NULL) { //반복문 돌며 디렉토리 항목 끝까지 읽기
        char *name = dirInfo->d_name; //반복문 돌며 입력된 디렉토리에서 파일
                                      //이름 저장할 변수 선언
        struct stat fileInfo2;
        stat(name, &fileInfo2); // name에 저장된 파일 이름의 정보를
                                // 읽고,fileInfo2 메모리 공간에 저장

        fileType(&fileInfo2); //파일의 종류
        fileMode(&fileInfo2); //파일의 접근권한
        userInfo =
            getpwuid(fileInfo2.st_uid); // name의 UID정보 읽고 userInfo에 저장
        printf("   %-15s", userInfo->pw_name); //소유자(계정명) 출력
        printf("%9ld", fileInfo2.st_size);     //파일의 크기 출력
        printf("  %-12ld", fileInfo2.st_mtime); //파일의 마지막 수정시간 출력
        printf("%s\n", name);                   //파일의 이름 출력
    }

    closedir(dirp); //디렉토리 스트림 닫아주기

    return 0;
}

void fileMode(const struct stat *fileInfo) { //파일 접근권한 얻는 함수
    // User
    if (S_IRUSR & fileInfo->st_mode)
        printf("r");
    else
        printf("-");

    if (S_IWUSR & fileInfo->st_mode)
        printf("w");
    else
        printf("-");

    if (S_IXUSR & fileInfo->st_mode)
        printf("x");
    else
        printf("-");

    // Group
    if (S_IRGRP & fileInfo->st_mode)
        printf("r");
    else
        printf("-");

    if (S_IWGRP & fileInfo->st_mode)
        printf("w");
    else
        printf("-");

    if (S_IXGRP & fileInfo->st_mode)
        printf("x");
    else
        printf("-");

    // Others
    if (S_IROTH & fileInfo->st_mode)
        printf("r");
    else
        printf("-");

    if (S_IWOTH & fileInfo->st_mode)
        printf("w");
    else
        printf("-");

    if (S_IXOTH & fileInfo->st_mode)
        printf("x");
    else
        printf("-");
}

void fileType(const struct stat *fileInfo) { //파일의 종류 얻는 함수
    if (S_ISREG(fileInfo->st_mode)) {        //일반 파일일 경우 - 출력
        printf("-");
    } else if (S_ISDIR(fileInfo->st_mode)) { //디렉토리일 경우 d 출력
        printf("d");
    } else { //일반 파일이나 디렉토리가 아닐 경우 링크로 생각하고 l 출력
        printf("l");
    }
}
