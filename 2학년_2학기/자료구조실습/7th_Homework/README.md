## 트리 클래스에서 특정 값을 탐색하는 함수와 특정 값을 가진 노드를 삭제하는 함수를 구현하는 프로그램
* 개발 환경 : C++ / Ubuntu 16.04 (VMware)
* 실행 결과
<img src = "https://user-images.githubusercontent.com/48857568/132693356-26a30af9-9468-428c-b87b-07acae30ec87.JPG" width="500" height="450">

* Problem Description
  * 트리 클래스에서 특정 값을 탐색하는 함수와 특정 값을 가진 노드를 삭제하는 함수를 구현한다
    * 트리 클래스의 삽입과 출력은 제공되는 `TreeNode.hpp` , `TreeNode.cpp` , `Tree.hpp` , `Tree.cpp` 파일을 이용
    * 탐색하는 함수
      * `search(int value)` 형태
      * 루트 노드에서 시작해서 탐색하면서 거치는 노드의 값을 출력
    * 삭제하는 함수
      * `remove(int value)` 형태
      * 삭제하려는 노드의 left 와 right 모두 가리키는 노드가 있는 경우에는 좌측 서브 트리 중에서 가장 큰 값으로 삭제하려는 노드를대체하고 삭제
    * 실행 결과처럼 탐색을 실패하는 경우, 삭제를 실패하는 경우도 고려
