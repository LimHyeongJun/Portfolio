## BackTracking을 이용한 알고리즘 문제 풀이
* 개발 환경 : C++ / Visual Studio 2017
* 실행 결과
<br><nbsp><img src = "https://user-images.githubusercontent.com/48857568/123039074-7f0add00-d42c-11eb-9591-dad6e2c702dd.PNG" width="900" height="350">

* 풀어야 하는 5개의 Puzzle
<br><nbsp><img src = "https://user-images.githubusercontent.com/48857568/123969675-69308580-d9f3-11eb-99a0-e0f5bc9cb47c.jpg" width="550" height="250">

* Problem Description
  * Theseus and That Pesky Minotaur
  * 테세우스(빨간원🔴)와 미노타우로스(검은원⚫)가 미로에 있다.
  * 테세우스가 한 번 움직일 때마다, 미노타우로스는 두 번 움직일 수 있다.
  * 미노타우로스는 다음과 같은 규칙을 따른다.
    * 수평으로 테세우스에게 가까이 갈 수 있는지 확인한다.
    * 가능하다면 수평으로 한 칸 움직인다.
    * 불가능하다면, 수직으로 테세우스에게 가까이 갈 수 있는지 확인한다.
    * 그것이 가능하다면 수직으로 한 칸 움직인다.
    * 수평, 수직 모두 움직일 수 없다면 그 턴은 넘긴다.
  * 중요한 점은 미노타우로스는 한 턴 이상의 앞을 볼 수 없고 그는 수직 움직임 전에 수평으로 움직이는 것을 택한다.
  * Input은 없으며 움직임에 따라 utput으로 L, R, U, D, S를 출력한다.
  * 예시
   <br><kbd><img src = "https://user-images.githubusercontent.com/48857568/123969253-03dc9480-d9f3-11eb-9dc6-d342fff525e7.jpg" width="300" height="160"></kbd>  
