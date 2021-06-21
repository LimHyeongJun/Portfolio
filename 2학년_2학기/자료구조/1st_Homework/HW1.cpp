//Name: 임형준
//ID: 2016726082

#include "MyDoubleVector.h"

int main() {
	MyDoubleVector v1; //객체 v1생성(디폴트 값 들어가면서 volume값 100, 동적 배열 공간 100개 할당)
	MyDoubleVector v2(10); //객체 v2생성(volume값 10, 동적 배열 공간 10개 할당)

	cout << "상태 출력 = 객체의 동적 배열, size, capacity 출력\n\n\n";

	cout << "---------v1, v2의 상태 출력---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << "\n\n\n";


	v1.push_back(1), v1.push_back(2); //v1 data가 가리키는 동적 배열의 1번째, 2번째 공간에 1과 3 할당
	v2.push_back(3), v2.push_back(4); //v2 data가 가리키는 동적 배열의 1번째, 2번째 공간에 2와 4 할당
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10

	cout << "---------push_back() 메소드를 사용한 후의 v1, v2의 상태 출력---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << "\n\n\n";


	MyDoubleVector v3(v2); //객체 v3 생성(v2를 복사한 객체)
	//v3 = (3, 4) capacity : 10
	cout << "---------ㅡMyDoubleVector v3(v2)로 v3 생성 후 v2, v3 비교---------" << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	cout << "v3의 동적 배열 : "; v3.print(); cout << ", v3의 size: " << v3.size();
	cout << ", v3의 capacity: " << v3.capacity() << "\n\n\n";


	MyDoubleVector v4(40);
	//v4 = () capacity : 40
	cout << "---------v4 = v3를 하기 전과 후의 상태 출력---------" << endl;
	cout << "v3의 동적 배열 : "; v3.print(); cout << ", v3의 size: " << v3.size();
	cout << ", v3의 capacity: " << v3.capacity() << endl;;
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	v4 = v3; //객체 v4를 v3로 다시 할당해줬다. v4 = (3, 4) capacity : 10
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";



	cout << "---------v4 += v1을 하기 전과 후의 상태---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	v4 += v1; //v4 = (3, 4), v1 = (1, 2)
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";
	//v4 = (3, 4, 1, 2) capacity : 10


	cout << "---------print()메소드 쓰지 않고 [ ]operator로  v4 동적 배열 값 출력---------" << endl;
	cout << "v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	cout << "v4[0] = " << v4[0] << ", v4[1] = " << v4[1] << ", v4[2] = " << v4[2] << ", v4[3] = " << v4[3] << "\n\n\n";


	MyDoubleVector v5 = v1 + v2; //객체 v5는 v1과 v2 더한 것
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2의 상태와 v5 = v1 + v2를 한 후의 v5 상태 출력---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	cout << "v5의 동적 배열 : "; v5.print(); cout << ", v5의 size: " << v5.size();
	cout << ", v5의 capacity: " << v5.capacity() << "\n\n\n";
	//v5 = (4, 6) capacity : 4


	MyDoubleVector v6 = v1 - v2; //객체 v6는 v1과 v2 뺀 것
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2의 상태와 v6 = v1 - v2를 한 후의 v6 상태 출력---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	cout << "v6의 동적 배열 : "; v6.print(); cout << ", v6의 size: " << v6.size();
	cout << ", v6의 capacity: " << v6.capacity() << "\n\n\n";
	//v6 = (-2, -2) capacity : 4


	double mul_result = v1 * v2; //v1과 v2 내적한 값 저장할 mul_result 값 선언 및 초기화
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2의 상태와 v1 * v2를 한 후의 내적값 출력---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	cout << "v1 * v2 = "; v1.print(); cout << " * "; v2.print();
	cout << " = " << mul_result << "\n\n\n"; //내적값 : 11


	cout << "---------  -v4를 하기 전과 후의 상태 출력---------" << endl;
	//v4 = (3, 4, 1, 2) capacity : 10
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	-v4; //v4에 -를 함으로써 동적 배열안의 모든 값의 부호를 반대로 해줬다.
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";
	//v4 = (-3, -4, -1, -2) capacity : 10


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (-3, -4, -1, -2) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4


	cout << "---------v1과 v2가 같은가?(operator == 사용)---------" << endl;
	cout << "v1의 동적 배열 : "; v1.print(); cout << ", v1의 size: " << v1.size();
	cout << ", v1의 capacity: " << v1.capacity() << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	if (v1 == v2)
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";


	cout << "---------v2과 v3가 같은가?(operator == 사용)---------" << endl;
	cout << "v2의 동적 배열 : "; v2.print(); cout << ", v2의 size: " << v2.size();
	cout << ", v2의 capacity: " << v2.capacity() << endl;
	cout << "v3의 동적 배열 : "; v3.print(); cout << ", v3의 size: " << v3.size();
	cout << ", v3의 capacity: " << v3.capacity() << endl;
	if (v2 == v3)
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";


	cout << "---------v4(1)를 하기 전과 후의 상태 출력---------" << endl;
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	v4(1);
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (1, 1, 1, 1) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4

	cout << "---------v4.pop_back()을 하기 전과 후의 v4 상태 출력---------" << endl;
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	v4.pop_back();
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";


	cout << "---------v4.reserve(50)을 하기 전과 후의 v4 상태 출력---------" << endl;
	cout << "전-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	v4.reserve(50);
	cout << "후-----> v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << "\n\n\n";


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (1, 1, 1, 1) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4


	cout << "---------v4가 비워져 있는가?(empty()메소드 사용)---------" << endl;
	cout << "v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	if (v4.empty())
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";

	cout << "---------v4를 비우고 비워져 있는지 확인하기(clear(), empty()메소드 사용)---------" << endl;
	cout << "v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	cout << "clear()메소드 사용!!!" << endl;
	v4.clear();
	cout << "v4의 동적 배열 : "; v4.print(); cout << ", v4의 size: " << v4.size();
	cout << ", v4의 capacity: " << v4.capacity() << endl;
	cout << "v4는 비워져 있는가? ";
	if (v4.empty())
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";
}