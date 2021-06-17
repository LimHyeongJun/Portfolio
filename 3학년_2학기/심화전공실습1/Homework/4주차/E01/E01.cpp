#include <glm/glm.hpp>					//OpenGL Mathematics
#include <glm/gtx/string_cast.hpp>		//glm::to_string()
#include <glm/gtc/matrix_access.hpp>	//glm:column(), glm::row()
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <iostream>
using namespace std;

void part1() {
	cout << "Vector operations" << endl;

	//Vectors
	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 2, 1);
	cout << "v1 = " << to_string(v1) << endl;
	cout << "v2 = " << to_string(v2) << endl << endl;

	//Addition / subtraction
	cout << "v1 + v2 = " << to_string(v1 + v2) << endl;
	cout << "v1 - v2 = " << to_string(v1 - v2) << endl;

	//Negation
	cout << "-v1 = " << to_string(-v1) << endl;

	//Scalar multiplication and subtraction
	cout << "v1 - 2(v2) = " << to_string(v1 - 2.0f * v2) << endl;

	//Dot product
	cout << "dot(v1, v2) = " << dot(v1, v2) << endl;

	//Cross produect
	cout << "cross(v1, v2) = " << to_string(cross(v1, v2)) << endl;
}

void part2() {
	cout << "Matrix operations" << endl;

	//Matrices
	glm::mat3 A1(1.0, 2.0, 1.0, 2.0, 3.0, 1.0, 3.0, 2.0, 2.0);
	glm::mat3 A2(2.0, 2.0, 1.0, 1.0, 2.0, 1.0, 2.0, 1.0, 1.0);
	//A1 = 1.0   2.0   3.0		A2 = 2.0   1.0   2.0
	//	   2.0   3.0   2.0			 2.0   2.0   1.0
	//	   1.0   1.0   2.0		     1.0   1.0   1.0
	cout << "A1 = " << to_string(A1) << endl;
	cout << "A2 = " << to_string(A2) << endl << endl;

	//Vectors
	glm::vec3 v1(1, 2, 3);
	glm::vec3 v2(3, 2, 1);
	
	//Addtion / Subtraction
	cout << "A1 + A2 = " << to_string(A1 + A2) << endl;
	cout << "A1 - A2 = " << to_string(A1 - A2) << endl;

	//Negation
	cout << "-A1 = " << to_string(-A1) << endl;

	//Scalar multiplication and Subtraction
	cout << "A1 - 2(A2) = " << to_string(A1 - 2.0f * A2) << endl;

	//Matrix multiplication
	cout << "A1 x A2 = " << to_string(A1 * A2) << endl;
	cout << "A2 x A1 = " << to_string(A2 * A1) << endl;

	//Matrix and Vector multiplication
	cout << "A1 x v1 = " << to_string(A1 * v1) << endl;
	cout << "A2 x v2 = " << to_string(A2 * v2) << endl;
}

int main() {
	int e;
	cout << "Write the number 1 or 2 : ";
	cin >> e;
	cout << endl;

	switch (e) {
	case 1: part1(); break; //Vector operations
	case 2: part2(); break; //Matrix operations
	}

	system("pause");
	return 0;
}