/*
 * Student ID: 2016726082
 * Name: 임형준
 */
#include "MyStudent.hpp"
#include <fcntl.h>
#include <iostream>
#include <list>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main(void) {
    list<Student> stuList; // Student 객체를 저장할 리스트 stuList
    list<Student>::iterator iter; // Student 객체 리스트 가리키는 iterator iter
    ssize_t rsize = 0;            //끝까지 읽을 때 필요한 변수 rsize
    int i = 1;

    string filepath = "./StudentList.dat";
    Student *student = new Student;
    //파일 읽어들일 때 필요한 Student형 포인터 변수 student 동적 선언

    int fd = open(filepath.c_str(), O_RDONLY, 0644); //읽기만 가능하게 파일 염.
    if (fd == -1) {
        perror("open() error!");
        return 1;
    }

    do {
        rsize = read(fd, (Student *)student, sizeof(Student));
        //열려있는 파일을 Student 크기만큼 읽어 Student 포인터 변수 student에
        //저장

        if (rsize == -1) { //-1이 뜨면 오류 뜬 것이므로 종료
            perror("read() error!");
            return 2;
        } else if (rsize == 0) //다 읽으면 반복문 빠져나감
            break;

        stuList.push_back(*student);
        // Student형 객체 저장하는 연결 리스트에 동적으로 받은 객체 저장
    } while (rsize > 0);

    for (iter = stuList.begin(); iter != stuList.end(); ++iter) {
        cout << i << "번째 학생 정보" << endl;
        cout << "ID: " << iter->getId() << ", Name: " << iter->getName()
             << ", Score: " << iter->getScore() << endl;
        ++i;
    }

    close(fd);
    delete student;

    return 0;
}
