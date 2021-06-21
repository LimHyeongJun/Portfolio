//Name: ������
//ID: 2016726082

#include "MyDoubleVector.h"

MyDoubleVector::MyDoubleVector(size_t init_capacity) {
	data = new double[init_capacity];
	volume = init_capacity;
	used = 0;
}
//precondition: init_capacity >= 0�� ����
//postcondition: data�� double���� ���� ���� �� �ְ� init_capacity��ŭ�� ���̸� ���� ���� �迭�� ����Ŵ
//���� �迭�� init_capacity��ŭ�� ������ �Ҵ����ְ� �̸� volume�� ����
//���� �迭�� ���� �� ������ ����ϰ� �ִ� ������ ������ �����ϴ� ���� used�� 0���� �ʱ�ȭ

MyDoubleVector::MyDoubleVector(const MyDoubleVector& v) {
	data = new double[v.volume];
	volume = v.volume;
	used = v.used;
	copy(v.data, v.data + used, data);
}
//precondition: X
//postcondition: ������ ��ü�� ������ data ������, volume, used�� ���� ��ü�� �����ؼ� �����Ѵ�.

MyDoubleVector::~MyDoubleVector() {
	delete[] data;
}
//precondition: X
//postcondition: �����Ҵ� �� �迭 data�� �޸𸮸� �ݳ��Ѵ�.

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
//postcondition: LHS�� RHS�� ���ٸ� �״�� ����
//���� LHS�� RHS�� ������ ������ �ٸ��ٸ� LHS�� ���� �迭 �ݳ� �ϰ� RHS�� ������ ������ ���� ���� �迭 ��������ְ�,
//������ ������ �ش��ϴ� ������ volume�� RHS�� ������ LHS�� �� �ٲ��ش�.
//used�� RHS�� ������ LHS�� ���� �ٲ��ְ� RHS�� ���빰�� LHS�� �������ְ� LHS ����

void MyDoubleVector:: operator +=(const MyDoubleVector& addend) {
	if (used + addend.used > volume)
		reserve(used + addend.used);
	copy(addend.data, addend.data + addend.used, data + used);
	used += addend.used;
}
//precondition: X
//postcondition: LHS�� used�� RHS�� used�� ���� ���� LHS�� volume������ ũ�� ���� ������ ���� �÷��ش�.
//RHS�� ���빰�� LHS�ڿ� ���ٿ��ְ� LHS�� used�� RHS�� used�� LHS�� used�� ���� ������ ���´�.

double& MyDoubleVector:: operator [] (size_t n) {
	assert(n < volume);

	return data[n];
}
//precondition: 0 <= n <volume �� ����
//postcondition: data�� ����Ű�� ���� �迭�� n+1��°�� �� ����

MyDoubleVector MyDoubleVector:: operator +(const MyDoubleVector& v2) {
	MyDoubleVector answer(used + v2.used);

	assert(used == v2.used);

	for (size_t i = 0; i < used; i++) {
		answer.data[i] = data[i] + v2.data[i];
		answer.used++;
	}
	return answer;
}
//precondition: +�� ����, �����ʿ� ��ġ�� ��ü���� used�� ����.
//postcondition: +���ʿ� ��ġ�� ��ü���� �������� �����Ѵ�.

MyDoubleVector MyDoubleVector:: operator -(const MyDoubleVector& v2) {
	MyDoubleVector answer(used + v2.used);

	assert(used == v2.used);

	for (size_t i = 0; i < used; i++) {
		answer.data[i] = data[i] - v2.data[i];
		answer.used++;
	}
	return answer;
}
//precondition: -�� ����, �����ʿ� ��ġ�� ��ü���� used�� ����.
//postcondition: -���ʿ� ��ġ�� ��ü���� �������� �����Ѵ�.

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
//precondition: *�� ����, �����ʿ� ��ġ�� ��ü���� used�� ����.
//postcondition: *���ʿ� ��ġ�� ��ü���� ��Į�� ���� ���� �����Ѵ�.

MyDoubleVector& MyDoubleVector:: operator -() {
	for (size_t i = 0; i < this->used; i++)
		data[i] = -(data[i]);

	return *this;
}
//precondition: X
//postcondition: data�� ����Ű�� ���� �迭�� ��� ������ ��ȣ�� �ݴ�� �Ѵ�.

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
//postcondition: �� ��ü�� data�� ���� �迭 ���� ù��°���� ���������� ��� ������ true, �ƴ϶�� false ����

MyDoubleVector& MyDoubleVector:: operator ()(double k) {
	for (size_t i = 0; i < this->used; i++)
		data[i] = k;

	return *this;
}
//precondition: �Ǽ� k�� �Է��Ѵ�.
//postcondition: �ش� ��ü�� data�� ����Ű�� ���� �迭�� ��� ���� k�� �ٲ��ش�.

void MyDoubleVector::pop_back() {
	data[--used] = NULL;
}
//precondition: X
//postcondition: ���� ���ִ� data�� ����Ű�� ���� �迭�� ������ ���� �����ϰ�, ���� ����ϴ� ������ ũ�⸦ �ϳ� ���δ�.

void MyDoubleVector::push_back(double x) {
	if (volume == used)
		volume *= 2;
	data[used++] = x;
}
//precondition: �Ǽ� x�� �Է��Ѵ�.
//postcondition: ���� ���� �迭�� ��� ������ ������ ������ ���� ��� ���� ������ ������ ���ٸ� 2��� �÷��ش�.
//data�� �⸮Ű�� ���� �迭�� ������ �� �ڿ� x�� ���� �־��ְ� used�� ���� 1 ������Ų��.

size_t MyDoubleVector::capacity() const {
	return volume;
}
//precondition: X
//postcondition: data�� ����Ű�� ���� �迭�� �Ҵ�� ������ ������ �������ش�.

size_t MyDoubleVector::size() const {
	return used;
}
//precondition: X
//postcondition: ���� �迭���� ������ ����ϰ� �ִ� ������ ������ �������ش�.

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
//precondition: n >= 0�� ���� �Է����ش�.
//postcondition: �Էµ� n���� �Ҵ�Ǿ� �ִ� �������� ���� ��� volume ������ �Ҵ����ش�.
//���� ���� �迭�� �Ҵ�Ǿ� �ִ� ������ n�� ũ�⸸ŭ���� �Ҵ����ش�.
//used�� ���� ��ȭ���� volume���� ��ȭ�Ѵ�.

bool MyDoubleVector::empty() const {
	if (used == 0)
		return true;
	else
		return false;
}
//precondition: X
//postcondition: ���� ���� �迭���� ���� ����ϰ� �ִ� ������ ������ true, �ƴ϶�� false �������ش�.

void MyDoubleVector::clear() {
	int temp = used;
	for (int i = 0; i < temp; i++) {
		data[i] = NULL;
		used--;
	}
}
//precondition: X
//postcondition: ���� �迭�� ��� ���� �����ϰ�, ����ϰ� �ִ� ������ ���ش�.
//��, used�� 0�� ������ volume�� ���� �״�� ������.

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
//postcondition: ���� �迭 ���� ������ ( )�ȿ� �־ ���� ���� ����Ѵ�.
