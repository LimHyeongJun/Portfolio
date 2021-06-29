## DP를 이용한 알고리즘 문제 풀이
* 개발 환경 : C++ / Visual Studio 2017
* 실행 결과
  <br><img src = "https://user-images.githubusercontent.com/48857568/123039070-7dd9b000-d42c-11eb-9168-013bbe3f5812.PNG" width="700" height="350">
* Problem Description
  * 입력으로 실수값을 갖는 n×n정방행렬 array가 주어진다.(n <= 1000)
  * 입력받은 n×n정사각형 array에서 sub 직사각형 2개를 고른다. 하나는 sub 직사각형의 내용물의 합이 최소가 되는 것이고, 하나는 최대가 되는 것이다.
  * 1번째 줄은 최소 합산 값, 2번째 줄은 최소 합산 값일 때 직사각형의 좌상단과 우하단의 position을 출력한다. 3, 4번째 줄은 최대 합산 값일 때를 출력한다.
  * ex) n = 4, {{3, -3, -2, -1}, {2, 6, -5, 1}, {-3, -5, 2, 4}, {2, 4, 0, -2}}인 경우.
    |최대 합산 값|최소 합산 값|
    |---------------|---------------|
    |<img src = "https://user-images.githubusercontent.com/48857568/123817921-84d45700-d933-11eb-9284-f5d6a71062b4.JPG" width="250" height="100">|<img src = "https://user-images.githubusercontent.com/48857568/123817928-856ced80-d933-11eb-9a1c-a69c67bf5f5d.JPG" width="250" height="100">|
  * 예시 1
    <br><kbd>
    <img src = "https://user-images.githubusercontent.com/48857568/123818935-5905a100-d934-11eb-99aa-58443da106f0.jpg" width="300" height="180">
    </kbd>
    <br><br>
  
  * 예시 2
    <br><kbd>
    <img src = "https://user-images.githubusercontent.com/48857568/123818928-586d0a80-d934-11eb-81bb-15ae37a781e5.jpg" width="300" height="180">
    </kbd>
* 유의 사항
  * 시간 복잡도가 n<sup>6</sup>, n<sup>4</sup> 풀이 방법도 있지만 n<sup>3</sup>인 알고리즘으로 풀도록 한다.
