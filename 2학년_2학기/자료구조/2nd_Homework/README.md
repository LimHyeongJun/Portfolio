## Stack을 이용한 계산 프로그램 만들기
* 개발 환경 : C++ / Visual Studio 2017
* 실행 결과
<img src = "https://user-images.githubusercontent.com/48857568/123039116-87631800-d42c-11eb-93be-62caf015e4b3.PNG" width="600" height="300">

* Problem Description
  * 실제 계산식을 줄로 input을 해서 결과를 output으로 받는다.
  * `( ), { }, [ ]` 만 괄호로 입력받을 수 있다.
  * `*, /, +, -`의 4개 연산자만 input으로 받을 수 있다. `*, /`가 `+, -`보다 높은 우선 순위를 갖는다.
  * 결과는 항상 정수가 나오며, 음수도 될 수 있다.
  * 소수점 아래 세 번째 자리까지 반올림 한다.
* 유의 사항
  * 오로지 양수인 실수만이 피연산자로써 input이 될 수 있다.
  * 괄호가 맞지 않는 표현식과 “/0.0”을 하는 경우는 “Error!: {reason}\n"를 output으로 한다.
