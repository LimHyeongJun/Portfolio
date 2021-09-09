## 공유 메모리를 이용한 서버, 클라이언트간 통신
* 개발 환경 : C++ / Ubuntu 16.04 (VMware)
* 실행 결과

|server|client|
|-------|------|
|<img src = "https://user-images.githubusercontent.com/48857568/132691737-b0bbb764-0731-4c7d-b833-96e2bbfcca06.JPG" width="500" height="320">|<img src = "https://user-images.githubusercontent.com/48857568/132691740-c083f242-aa8c-4d41-9f04-ca230f084ed0.JPG" width="500" height="320">|


* Problem Description
  * 서버는 `server.c` 파일, 클라이언트는 `client.c` 파일에 작성함
  * Server
    * 클라이언트로부터 통신을 받기 전까지 대기
    * 클라이언트로부터 `[x] [op] [y]` 형식의 식을 받음
    * 클라이언트로부터 받은 식을 계산 후 클라이언트에게 전송하고 대기
    * `Ctrl + C`를 누르면 종료
  * Client
    * `[x] [op] [y]` 형식의 식을 입력
    * 해당 식이 서버로 전송되고 해당 식의 결과를 서버로부터 받아서 출력
    * `Ctrl + C`를 누르면 종료
