//Name: 임형준
//ID: 2016726082

#include "MyDoubleVector.h"

MyDoubleVector::MyDoubleVector(size_t init_capacity) {
	data = new double[init_capacity];
	volume = init_capacity;
	used = 0;
}
//precondition: init_capacity >= 0인 정수
//postcondition: data가 double형의 값을 가질 수 있고 init_capacity만큼의 길이를 갖는 동적 배열을 가리킴
//동적 배열에 init_capacity만큼의 공간을 할당해주고 이를 volume에 저장
//동적 배열의 공간 중 실제로 사용하고 있는 공간의 개수를 저장하는 변수 used를 0으로 초기화

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v) {
	data = new double[v.volume];
	volume = v.volume;
	used = v.used;
	copy(v.data, v.data + used, data);
}
//precondition: X
//postcondition: 참조한 객체와 동일한 data 포인터, volume, used를 갖는 객체를 복사해서 생성한다.

MyDoubleVector::~MyDoubleVector() {
	delete[] data;
}
//precondition: X
//postcondition: 동적할당 된 배열 data의 메모리를 반납한다.

MyDoubleVector& MyDoubleVector::operator =(const MyDoubleVector& source) {
	if (this == &source)
		return *this;
	if (volume != source.volume) {
		delete[] data;
		data = new double[source.volume];
		volume = source.volume;
	}
	used = source.used;
	copy(source.data, source.data + used, data);
	return *this;
}
//precondition: X
//postcondition: LHS와 RHS가 같다면 그대로 리턴
//만약 LHS와 RHS의 공간의 개수가 다르다면 LHS의 동적 배열 반납 하고 RHS의 공간의 개수와 같은 동적 배열 재생성해주고,
//공간의 개수에 해당하는 변수인 volume도 RHS의 값으로 LHS의 값 바꿔준다.
//used도 RHS의 값으로 LHS의 값을 바꿔주고 RHS의 내용물을 LHS에 복사해주고 LHS 리턴

void MyDoubleVector:: operator +=(const MyDoubleVector& addend) {
	if (used + addend.used > volume)
		reserve(used + addend.used);
	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
}
//precondition: X
//postcondition: LHS의 used와 RHS의 used를 더한 값이 LHS의 volume값보다 크면 더한 값으로 공간 늘려준다.
//RHS의 내용물을 LHS뒤에 덧붙여주고 LHS의 used는 RHS의 used와 LHS의 used를 더한 값으로 갖는다.

double& MyDoubleVector:: operator [] (size_t n) {
	assert(n < volume);

	return data[n];
}
//precondition: 0 <= n <volume 인 정수
//postcondition: data가 가리키는 동적 배열의 n+1번째의 값 리턴

MyDoubleVector MyDoubleVector:: operator +(const MyDoubleVector& v2) {
	MyDoubleVector answer(used + v2.used);

	assert(used == v2.used);

	for (size_t i = 0; i < used; i++) {
		answer.data[i] = data[i] + v2.data[i];
		answer.used++;
	}
	return answer;
}
//precondition: +의 왼쪽, 오른쪽에 위치한 객체들의 used가 같다.
//postcondition: +양쪽에 위치한 객체들의 벡터합을 리턴한다.

MyDoubleVector MyDoubleVector:: operator -(const MyDoubleVector& v2) {
	MyDoubleVector answer(used + v2.used);

	assert(used == v2.used);

	for (size_t i = 0; i < used; i++) {
		answer.data[i] = data[i] - v2.data[i];
		answer.used++;
	}
	return answer;
}
//precondition: -의 왼쪽, 오른쪽에 위치한 객체들의 used가 같다.
//postcondition: -양쪽에 위치한 객체들의 벡터차를 리턴한다.

double MyDoubleVector:: operator *(const MyDoubleVector& v2) {
	MyDoubleVector answer(used + v2.used);
	double result = 0;

	assert(used == v2.used);

	for (size_t i = 0; i < used; i++) {
		answer.data[i] = data[i] * v2.data[i];
		answer.used++;
		result += answer.data[i];
	}
	return result;
}
//precondition: *의 왼쪽, 오른쪽에 위치한 객체들의 used가 같다.
//postcondition: *양쪽에 위치한 객체들의 스칼라 곱의 값을 리턴한다.

MyDoubleVector& MyDoubleVector:: operator -() {
	for (size_t i = 0; i < this->used; i++)
		data[i] = -(data[i]);

	return *this;
}
//precondition: X
//postcondition: data가 가리키는 동적 배열의 모든 값들의 부호를 반대로 한다.

bool MyDoubleVector:: operator ==(const MyDoubleVector& v2) {
	if (used != v2.used)
		return false;
	int result = 0;

	for (size_t i = 0; i < v2.used; i++) {
		if (data[i] != v2.data[i])
			result++;
	}
	if (result == 0)
		return true;
	else
		return false;

}
//precondition: X
//postcondition: 두 객체의 data의 동적 배열 값이 첫번째부터 마지막까지 모두 같으면 true, 아니라면 false 리턴

MyDoubleVector& MyDoubleVector:: operator ()(double k) {
	for (size_t i = 0; i < this->used; i++)
		data[i] = k;

	return *this;
}
//precondition: 실수 k를 입력한다.
//postcondition: 해당 객체의 data가 가리키는 동적 배열의 모든 값을 k로 바꿔준다.

void MyDoubleVector::pop_back() {
	data[--used] = NULL;
}
//precondition: X
//postcondition: 값이 들어가있는 data가 가리키는 동적 배열의 마지막 값을 제거하고, 실제 사용하는 공간의 크기를 하나 줄인다.

void MyDoubleVector::push_back(double x) {
	if (volume == used)
		volume *= 2;
	data[used++] = x;
}
//precondition: 실수 x를 입력한다.
//postcondition: 만약 동적 배열의 사용 가능한 공간의 개수와 실제 사용 중인 공간의 개수가 같다면 2배로 늘려준다.
//data가 기리키는 동적 배열의 마지막 값 뒤에 x의 값을 넣어주고 used의 값을 1 증가시킨다.

size_t MyDoubleVector::capacity() const {
	return volume;
}
//precondition: X
//postcondition: data가 가리키는 동적 배열에 할당된 공간의 개수를 리턴해준다.

size_t MyDoubleVector::size() const {
	return used;
}
//precondition: X
//postcondition: 동적 배열에서 실제로 사용하고 있는 공간의 개수를 리턴해준다.

void MyDoubleVector::reserve(size_t n) {
	double *larger_array;
	if (n <= volume)
		n = volume;

	larger_array = new double[n];
	copy(data, data + used, larger_array);
	delete[] data;
	data = larger_array;
	volume = n;
}
//precondition: n >= 0인 정수 입력해준다.
//postcondition: 입력된 n값이 할당되어 있는 공간보다 작을 경우 volume 값으로 할당해준다.
//기존 동적 배열에 할당되어 있던 공간을 n의 크기만큼으로 할당해준다.
//used의 값은 변화없고 volume값만 변화한다.

bool MyDoubleVector::empty() const {
	if (used == 0)
		return true;
	else
		return false;
}
//precondition: X
//postcondition: 만약 동적 배열에서 실제 사용하고 있는 공간이 없으면 true, 아니라면 false 리턴해준다.

void MyDoubleVector::clear() {
	int temp = used;
	for (int i = 0; i < temp; i++) {
		data[i] = NULL;
		used--;
	}
}
//precondition: X
//postcondition: 동적 배열의 모든 값을 제거하고, 사용하고 있는 공간을 없앤다.
//즉, used는 0이 되지만 volume은 값을 그대로 가진다.

void MyDoubleVector::print() const {
	cout << "(";
	for (size_t i = 0; i < used; i++) {
		if (i == used - 1) {
			cout << data[i];
			break;
		}
		cout << data[i] << ",";
	}
	cout << ")";
}
//precondition: X
//postcondition: 동적 배열 안의 값들을 ( )안에 넣어서 보기 좋게 출력한다.
