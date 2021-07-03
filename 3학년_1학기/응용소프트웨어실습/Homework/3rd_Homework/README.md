## 다중 사용자 그림판 프로그램 작성
* 개발 환경 : C# / Visual Studio 2017
* 실행 결과
  * 로그인 폼<br>
<kbd><img src = "https://user-images.githubusercontent.com/48857568/123039099-83cf9100-d42c-11eb-8348-bb1222fbdf34.PNG" width="400" height="250"></kbd>
  * 그림판 폼<br>
<kbd><img src = "https://user-images.githubusercontent.com/48857568/123039102-83cf9100-d42c-11eb-9f45-6782fbe2a3e1.PNG" width="800" height="450"></kbd>
* Problem Description
  * C#의 Windows Form을 이용한 프로그램 작성. 
  * Socket을 이용한 서버/클라이언트 다중 통신 및 다중 Thread 활용. 
  * GDI API 이용.
  * Server
    * 서버는 둘 이상의 클라이언트를 연결해 정보를 수신할 수 있어야 함.
    * 서버는 클라이언트가 보낸 그림 정보를 다른 클라이언트들에게도 전송해야 함.
    * 서버는 종료되면 화면 정보를 파일에 저장하고, 다시 켤 때 저장된 정보를 불러옴.
  * Client
    * 메뉴 목록의 작동 구현.
      1. Pencil : 지정한 선 굵기를 갖는 펜을 활성화하는 메뉴, 기본값은 최소 굵기.
      2. Line : 지정한 선 굵기로 마우스를 클릭한 곳에서 뗀 곳까지 선을 그리는 메뉴.
      3. Circle : 지정한 외곽선 굵기로 원을 그리는 메뉴.
      4. Rect : 지정한 외곽선 굵기로 사각형을 그리는 메뉴.
      5. 하나의 메뉴를 고르면 다른 메뉴는 비활성화.
      6. 나중에 그린 그림이 가장 위에 나타나야 함.
    * 1~5단계로 선 굵기 조절.
    * 색상 지정 및 채우기.
    * 더블 버퍼링 구현.
    * 나중에 들어온 클라이언트도 입장 전까지 그려진 그림 정보를 화면에 표시.
