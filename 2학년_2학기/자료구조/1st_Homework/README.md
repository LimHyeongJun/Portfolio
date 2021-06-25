## 쉘 스크립트로 Linux 작업관리자 만들기 2
* 개발 환경 : C++ / Visual Studio 2017
* Problem Description
  * STL의 `vector<double>`클래스와 비슷한 MyDoubleVector 클래스를 만든다.
  * 구현해야하는 멤버 함수들
    * (Default) Constructor
    * Copy constructor for deep copy
    * Destructor
    * Assignment operator (=) for deep copy
    * Operator +=
    * Operator [] : Returns a reference to the element at the requested position in the vector container.
    * (Binary) operator +
    * (Binary) operator -
    * (Binary) operator *
    * (Unary) operator -
    * (Binary) operator ==
    * (Unary) operator () : Makes every element of this object be the value of the real-valued (double-type) operand.
    * void pop_back();
    * void push_back(double x);
    * size_t capacity() const;
    * size_t size() const;
    * void reserve(size_t n);
    * bool empty() const;
    * void clear();
* 유의 사항
  * private member는 `double*` 형의 변수 사용하고 new operator를 이용하여 동적 메모리 할당을 한다.
  * printf, scanf 사용 불가
  * 전역 변수 사용 불가
