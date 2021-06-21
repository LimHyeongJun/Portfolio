//Name: ������
//ID: 2016726082

#include "MyDoubleVector.h"

int main() {
	MyDoubleVector v1; //��ü v1����(����Ʈ �� ���鼭 volume�� 100, ���� �迭 ���� 100�� �Ҵ�)
	MyDoubleVector v2(10); //��ü v2����(volume�� 10, ���� �迭 ���� 10�� �Ҵ�)

	cout << "���� ��� = ��ü�� ���� �迭, size, capacity ���\n\n\n";

	cout << "---------v1, v2�� ���� ���---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << "\n\n\n";


	v1.push_back(1), v1.push_back(2); //v1 data�� ����Ű�� ���� �迭�� 1��°, 2��° ������ 1�� 3 �Ҵ�
	v2.push_back(3), v2.push_back(4); //v2 data�� ����Ű�� ���� �迭�� 1��°, 2��° ������ 2�� 4 �Ҵ�
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10

	cout << "---------push_back() �޼ҵ带 ����� ���� v1, v2�� ���� ���---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << "\n\n\n";


	MyDoubleVector v3(v2); //��ü v3 ����(v2�� ������ ��ü)
	//v3 = (3, 4) capacity : 10
	cout << "---------��MyDoubleVector v3(v2)�� v3 ���� �� v2, v3 ��---------" << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	cout << "v3�� ���� �迭 : "; v3.print(); cout << ", v3�� size: " << v3.size();
	cout << ", v3�� capacity: " << v3.capacity() << "\n\n\n";


	MyDoubleVector v4(40);
	//v4 = () capacity : 40
	cout << "---------v4 = v3�� �ϱ� ���� ���� ���� ���---------" << endl;
	cout << "v3�� ���� �迭 : "; v3.print(); cout << ", v3�� size: " << v3.size();
	cout << ", v3�� capacity: " << v3.capacity() << endl;;
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	v4 = v3; //��ü v4�� v3�� �ٽ� �Ҵ������. v4 = (3, 4) capacity : 10
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";



	cout << "---------v4 += v1�� �ϱ� ���� ���� ����---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	v4 += v1; //v4 = (3, 4), v1 = (1, 2)
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";
	//v4 = (3, 4, 1, 2) capacity : 10


	cout << "---------print()�޼ҵ� ���� �ʰ� [ ]operator��  v4 ���� �迭 �� ���---------" << endl;
	cout << "v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	cout << "v4[0] = " << v4[0] << ", v4[1] = " << v4[1] << ", v4[2] = " << v4[2] << ", v4[3] = " << v4[3] << "\n\n\n";


	MyDoubleVector v5 = v1 + v2; //��ü v5�� v1�� v2 ���� ��
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2�� ���¿� v5 = v1 + v2�� �� ���� v5 ���� ���---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	cout << "v5�� ���� �迭 : "; v5.print(); cout << ", v5�� size: " << v5.size();
	cout << ", v5�� capacity: " << v5.capacity() << "\n\n\n";
	//v5 = (4, 6) capacity : 4


	MyDoubleVector v6 = v1 - v2; //��ü v6�� v1�� v2 �� ��
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2�� ���¿� v6 = v1 - v2�� �� ���� v6 ���� ���---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	cout << "v6�� ���� �迭 : "; v6.print(); cout << ", v6�� size: " << v6.size();
	cout << ", v6�� capacity: " << v6.capacity() << "\n\n\n";
	//v6 = (-2, -2) capacity : 4


	double mul_result = v1 * v2; //v1�� v2 ������ �� ������ mul_result �� ���� �� �ʱ�ȭ
	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	cout << "---------v1, v2�� ���¿� v1 * v2�� �� ���� ������ ���---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	cout << "v1 * v2 = "; v1.print(); cout << " * "; v2.print();
	cout << " = " << mul_result << "\n\n\n"; //������ : 11


	cout << "---------  -v4�� �ϱ� ���� ���� ���� ���---------" << endl;
	//v4 = (3, 4, 1, 2) capacity : 10
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	-v4; //v4�� -�� �����ν� ���� �迭���� ��� ���� ��ȣ�� �ݴ�� �����.
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";
	//v4 = (-3, -4, -1, -2) capacity : 10


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (-3, -4, -1, -2) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4


	cout << "---------v1�� v2�� ������?(operator == ���)---------" << endl;
	cout << "v1�� ���� �迭 : "; v1.print(); cout << ", v1�� size: " << v1.size();
	cout << ", v1�� capacity: " << v1.capacity() << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	if (v1 == v2)
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";


	cout << "---------v2�� v3�� ������?(operator == ���)---------" << endl;
	cout << "v2�� ���� �迭 : "; v2.print(); cout << ", v2�� size: " << v2.size();
	cout << ", v2�� capacity: " << v2.capacity() << endl;
	cout << "v3�� ���� �迭 : "; v3.print(); cout << ", v3�� size: " << v3.size();
	cout << ", v3�� capacity: " << v3.capacity() << endl;
	if (v2 == v3)
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";


	cout << "---------v4(1)�� �ϱ� ���� ���� ���� ���---------" << endl;
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	v4(1);
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (1, 1, 1, 1) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4

	cout << "---------v4.pop_back()�� �ϱ� ���� ���� v4 ���� ���---------" << endl;
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	v4.pop_back();
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";


	cout << "---------v4.reserve(50)�� �ϱ� ���� ���� v4 ���� ���---------" << endl;
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	v4.reserve(50);
	cout << "��-----> v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << "\n\n\n";


	//v1 = (1, 2) capacity : 100
	//v2 = (3, 4) capacity : 10
	//v3 = (3, 4) capacity : 10
	//v4 = (1, 1, 1, 1) capacity : 10
	//v5 = (4, 6) capacity : 4
	//v6 = (-2, -2) capacity : 4


	cout << "---------v4�� ����� �ִ°�?(empty()�޼ҵ� ���)---------" << endl;
	cout << "v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	if (v4.empty())
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";

	cout << "---------v4�� ���� ����� �ִ��� Ȯ���ϱ�(clear(), empty()�޼ҵ� ���)---------" << endl;
	cout << "v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	cout << "clear()�޼ҵ� ���!!!" << endl;
	v4.clear();
	cout << "v4�� ���� �迭 : "; v4.print(); cout << ", v4�� size: " << v4.size();
	cout << ", v4�� capacity: " << v4.capacity() << endl;
	cout << "v4�� ����� �ִ°�? ";
	if (v4.empty())
		cout << "true" << "\n\n\n";
	else
		cout << "false" << "\n\n\n";
}