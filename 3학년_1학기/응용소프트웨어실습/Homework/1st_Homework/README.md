## PC방 프로그램 작성
* 개발 환경 : C# / Visual Studio 2017
* 실행 결과<br>
<nbsp><img src = "https://user-images.githubusercontent.com/48857568/123039091-829e6400-d42c-11eb-8f85-3c7b1c57735c.PNG" width="500" height="350"> 
* Problem Description
  * C#의 다각형배열, 프로퍼티, 상속, 추상화와 오버라이딩을 이용하여 PC방 프로그램을 작성한다.
  * Game 클래스
    * Action() 메소드가 있음. 각각의 하위 클래스 게임은 Action()을 호출하면 해당하는 게임명을 출력.
    * 자식 클래스는 MexonGame, MDGame, MetboardGame 3개가 있음.
    * 반드시 C#의 추상화 기능 사용, 미사용 시 점수 없음.
  * Computer 클래스
    * Computer 클래스는 Game과 좌석 번호를 가짐, priavate하다. 구체화된 자식클래스 Game을 가질 수 없음.
    * GameAction 메소드: Game의 Action을 활성화하는 기능
    * 외부에서 번호를 저장하고 불러올 수 있는 기능 작성. 반드시 property로 작성.
    * 외부에서 Game을 설치(=할당)할 수 있는 기능 작성. 반드시 property로 작성.
  * PCRoom 클래스
    * Computer를 삼각형 모양의 배열로 가짐. 행과 열의 수는 같으며 5행으로 구성됨. private함.
    * 위치에 맞게 Computer 배치. 컴퓨터 번호 설정 및 Game 설치. 1번은 MDGame, 2번은 MetboardGame, 3번은 MexonGame, 4번은 MDGame, 5번은 MetboardGame, 6번은 MexonGame의 패턴을 띄게 설치
    * printSeat 메소드: Computer 배치가 눈에 띄도록 출력.
    * TurnGameOn 메소드: 매 줄마다 Computer에 설치된 게임을 활성화.
