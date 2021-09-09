
## 시스템 호출을 이용하여 , 파일에 저장된 정보를 연결 리스트에 저장하고 정보를 출력하는 프로그램
* 개발 환경 : C++ / Ubuntu 16.04 (VMware)
* 실행 결과
<img src = "https://user-images.githubusercontent.com/48857568/132690596-2e770abc-3e84-46e8-928a-6c277804abc2.JPG" width="500" height="320">

* Problem Description
  * 파일에 저장된 학생 정보를 연결 리스트에 저장하고 출력하는 프로그램을 다음의 조건에 따라 작성
    * 해당 코드를 `myread.cpp`에 작성
    * `StudentList.dat`파일에 있는 내용을 읽음
    * 파일 입출력은 시스템 호출을 이용함.
      * `open()` 함수와 `read()` 함수
    * 파일에 저장된 다수의 `Student` 객체를 읽어 연결 리스트에 저장함
    * 저장된 정보를 `iterator`를 이용해 정보를 출력함
