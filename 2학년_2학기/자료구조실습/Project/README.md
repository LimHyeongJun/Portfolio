
## 쉘의 명령어를 파일 번호를 활용하여 더 편리하게 작성
* 개발 환경 : C++ / Ubuntu 16.04 (VMware)
* 실행 결과
  * ls
  <br><img src = "https://user-images.githubusercontent.com/48857568/132358832-06fffed5-956d-4b0a-965d-1b544135e09a.jpg" width="500" height="130">
  * cd
  <br><img src = "https://user-images.githubusercontent.com/48857568/132358850-6aa72eea-ecfb-4ff3-ba51-25fc4aa6b72e.jpg" width="600" height="200">
  * mv
  <br><img src = "https://user-images.githubusercontent.com/48857568/132359192-a87854e3-bb47-47db-a565-a6a0ef9fc59b.jpg" width="600" height="200">
  * cat
  <br><img src = "https://user-images.githubusercontent.com/48857568/132358873-ce3a468f-bb2c-4b23-b874-cbabf2840d56.jpg" width="600" height="200">

* Problem Description
  * `파일 형식 구분`, `ls`, `cat` 기능들을 내가 구현했다.
  * ls
    * ls 명령어를 치면 자동으로 sort되어 출력, 디렉토리와 파일이 색깔로 구분.
    * 출력 시 파일명과 함께  출력된 순서에 따라 번호가 매겨져서 출력(출력 순서는 디렉토리가 먼저, 파일이 나중에 나오도록 설정)
    * 사용 방법
      * `ls` : 현재 디렉토리의 목록을 출력.
      * `ls [디렉토리번호]` : 디렉토리번호에 해당되는 파일의 목록을 출력.
      * `ls ..` : 상위 디렉토리에 있는 파일의 목록을 출력.
  * cd
    * 현재 디렉토리의 위치를 변경하고  변경된 디렉토리의 파일 목록을 출력.
    * 사용 방법
      * `cd  [디렉토리번호]`  : 해당 디렉토리로 이동.
      * `cd ..` : 상위 디렉토리로 이동.
      * ls에서 나온 번호를 이용해 `cd 1`을  입력하면  해당 번호에 해당하는 디렉토리로 이동.
  * mv
    * `mv [파일번호][디렉토리번호]`를 입력하면  파일이 해당 디렉토리로 이동.
    * 사용 방법
      * `mv 2 1` 입력하면 ls에서 2번 번호로 나왔던 파일을 1번 디렉토리로 옮김.
  * cat
    * `cat [내용을 확인할  파일번호]` 을 입력하면 파일의 내용을 출력.
      * `cat > [내용을 덧붙일 파일]`을  입력하면 파일의 내용을 추가.
      * `quit`을 입력하면 cat 명령어에 대한 활동을 종료.
