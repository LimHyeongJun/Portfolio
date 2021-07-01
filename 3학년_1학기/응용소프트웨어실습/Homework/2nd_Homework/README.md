## 다중 채팅 프로그램 작성
* 개발 환경 : C# / Visual Studio 2017
* 실행 결과
<br><img src = "https://user-images.githubusercontent.com/48857568/123039095-8336fa80-d42c-11eb-848e-caede04076f5.PNG" width="800" height="450">
* Problem Description
  * C#의 Windows Form을 이용한 프로그램 작성.
  * Socket을 이용한 서버/클라이언트 다중 통신 및 다중 Thread를 활용.
  * 다중 채팅 프로그램 Form
    |Server|Client|
    |---------------|---------------|
    |<img src = "https://user-images.githubusercontent.com/48857568/124091292-a39c3000-da90-11eb-90d8-b094d7f4b21d.jpg" width="300" height="180">|<img src = "https://user-images.githubusercontent.com/48857568/124091296-a434c680-da90-11eb-8a83-4ecc0a1e33d3.jpg" width="300" height="180">|
  * 동작 순서 - Server
    * 본인의 IP와 임의로 설정한 Port Number를 텍스트 박스에 입력.
    * 서버 시작 버튼을 누르면 클라이언트의 연결을 기다림. 여러 클라이언트를 실시간으로 연결 가능함.
    * 서버에서 텍스트 박스에 입력하고 보내기를 누르면 전체 클라이언트에 채팅 전송.
    * 클라이언트에서 전송한 채팅 데이터를 서버에서 바로 확인할 수 있어야 함. 이 때 클라이언트가 입력한 닉네임으로 채팅 구별할 수 있어야 함.
    * 한 클라이언트가 서버에 채팅을 보내면 이 채팅을 다른 클라이언트들에도 전달.
    * 클라이언트가 접속하고 접속을 해지할 때 연결 상태를 자동으로 전달해야 됨.
  * 동작 순서 - Client
    * IP와 Port Number를 입력하고 클라이언트의 구분을 위한 닉네임을 입력함.
    * 서버 연결을 누를 경우 해당 IP와 Port를 가진 서버가 있는 경우 서버에 연결.
    * 텍스트 박스에 보낼 내용 입력하고 보내기를 누르면 서버에 내용이 전송됨.
    * 연결 해제나 종료 버튼을 누르면 접속을 해지할 수 있음.
