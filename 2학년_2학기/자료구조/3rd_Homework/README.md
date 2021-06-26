## Heap을 이용해 3가지 Form으로 출력
* 개발 환경 : C++ / Visual Studio 2017
* 실행 결과
<img src = "https://user-images.githubusercontent.com/48857568/123405866-3b0f0800-d5e5-11eb-9123-676b3e5f41d9.PNG" width="700" height="480">

* Problem Description
  * Console Input : Heap Operation의 사이즈 `n(1 <= n <= 200)`
  * Console Output : 주어진 3가지 Form으로 구성된 Constructed Heap의 최종 모양
  * 순서는 아스키코드상으로 0~z까지이다.
  * Input Operations
    * INS # : character #을 heap으로 넣는다.
    * DEL : 힙의 root node를 삭제한다.
    * EOI : input의 끝을 알린다.
  * Input Format(Console Input)
    * Example : INS 1 INS 2 INS 3 INS 4 INS 5 INS 6 INS 7 INS 8 INS 9 EOI
  * Output Format(Console Output)
    1. Rotated Form : Contructed Heap을 반시계 방향으로 90도 돌린 모양으로 출력.
    2. Non-rotated Form : 회전하지 않은 모양으로 출력. Leaf node 간의 width는 1이다.
    3. H-tree Form : H-tree 모양으로 출력한다.
