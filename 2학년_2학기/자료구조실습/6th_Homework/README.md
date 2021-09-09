## 중위 표기법으로 표현된 식을 입력 받고 스택을 이용하여 후위 표기법으로 변환하여 출력하는 프로그램
* 개발 환경 : C++ / Ubuntu 16.04 (VMware)
* 실행 결과
<img src = "https://user-images.githubusercontent.com/48857568/132692837-8014d695-9f62-4bdb-82cf-1528f91d9861.JPG" width="500" height="320">


* Problem Description
  * 스택을 이용하여 후위 표기법으로 변환하여 화면에 출력함
  * 해당 코드를 `main.cpp` 에 작성
  * 후위 표기법을 표현하기 위해 반드시 `stack` 컨테이너를 사용
  * `알파벳`과 `+ - * / ( )` 로 이루어진 수식을 공백 없이 입력 받음
    * 예시) `A+B*C`, `(A+B)*(C+D)` 등
  * 잘못된 수식 입력은 고려하지 않음
