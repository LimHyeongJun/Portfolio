#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <stdio.h>

using namespace std;
void evaluate_stack(stack<double>& numbers, stack<char>& operations, int& decide_num);

class DivideByZero { //0으로 나뉜 것 출력하는 클래스
public:
	void what() { cout << "Error!: divide by zero!" << endl; }
};
class UnbalancedParentheses { //괄호치기 잘못된 것 출력하는
public:
	void what() { cout << "Error!: unbalanced parentheses" << endl; }
};

void read_and_evaluate(istream& ins) {
	const char DECIMAL = '.';
	const char LEFT_PARENTHESIS = '('; //왼쪽 소괄호
	const char RIGHT_PARENTHESIS = ')'; //오른쪽 소괄호
	const char MIDDLE_LEFT_PARENTHESIS = '{'; //왼쪽 중괄호
	const char MIDDLE_RIGHT_PARENTHESIS = '}'; //오른쪽 중괄호
	const char BIG_LEFT_PARENTHESIS = '['; //왼쪽 대괄호
	const char BIG_RIGHT_PARENTHESIS = ']'; //오른쪽 대괄호

	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;
	int decide_num = 0;

	if (ins.peek() == '\n')
		ins.ignore();

	while (ins && ins.peek() != '\n') {
		if (decide_num == 1 || decide_num == 2) { //decide_num이 1 또는 2이면 에러가 난 것이므로 반복문 종료
			//아래 반복문 돌다가 decide_num이 1이나 2로 초기화되면 여기서 제일 먼저 걸리므로 예외처리 가능
			break;
		}
		else if (isdigit(ins.peek()) || ins.peek() == DECIMAL) {
			ins >> number;
			numbers.push(number);
		}
		else if (ins.peek() == LEFT_PARENTHESIS || ins.peek() == MIDDLE_LEFT_PARENTHESIS || ins.peek() == BIG_LEFT_PARENTHESIS) {
			ins >> symbol; //(, {, [ 중 하나일 경우 operation 스택에 push
			operations.push(symbol);
		}
		else if (strchr("+-*/", ins.peek()) != NULL) {
			ins >> symbol;
			if (operations.empty()) { //만약 operations스택이 비어있다면 그냥 연산자 넣음
				operations.push(symbol);
			}
			else { //비어있지 않다면 연산자 우선순위 계산해서 넣고 빼고 한 다음에 
				char top_operation = operations.top(); //연산자 스택의 top을 임시로 저장
				switch (symbol) {
				case '+':
				case '-':
					if (top_operation == '(' || top_operation == '{' || top_operation == '[') {
						operations.push(symbol);
						break;
					}
					else if (top_operation == '*' || top_operation == '/' || top_operation == '+' || top_operation == '-') {
						evaluate_stack(numbers, operations, decide_num);
						operations.push(symbol); break;
					}
				case '*':
				case '/':
					if (top_operation == '+' || top_operation == '-' || top_operation == '(' || top_operation == '{' || top_operation == '[') {
						operations.push(symbol); break;
					}
					else if (top_operation == '*' || top_operation == '/') {
						evaluate_stack(numbers, operations, decide_num);
						operations.push(symbol); break;
					}
				}
			}
		} //strchr("+-*/", ins.peek()) != NULL 닫는 괄호
		else if (ins.peek() == RIGHT_PARENTHESIS) { //오른쪽 괄호가 소괄호일 경우
			ins.ignore();
			while (1) {
				if (operations.empty()) { //오른쪽 소괄호가 나왔는데 스택이 비어있으면 괄호치기 잘못 되어있으므로 decide_num을 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS) { //왼쪽 괄소괄호일 경우 그냥 빼기만 한다.
					operations.pop();
					break;
				}
				else if (operations.top() == MIDDLE_LEFT_PARENTHESIS || operations.top() == BIG_LEFT_PARENTHESIS) {
					// 오른쪽 소괄호가 나왔는데 왼쪽 중괄호나 대괄호가 나왔으면 괄호치기 잘못 되어있으므로 decide_num = 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//사칙연산일 경우 계산해준다.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (ins.peek() == MIDDLE_RIGHT_PARENTHESIS) { //오른쪽 괄호가 중괄호일 경우
			ins.ignore();
			while (1) {
				if (operations.empty()) { //오른쪽 중괄호가 나왔는데 스택이 비어있으면 괄호치기 잘못 되어있으므로 decide_num을 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == MIDDLE_LEFT_PARENTHESIS) { //왼쪽 중괄호일 경우 그냥 스택에서 빼기만 함
					operations.pop();
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS || operations.top() == BIG_LEFT_PARENTHESIS) {
					// 오른쪽 중괄호가 나왔는데 왼쪽 소괄호나 대괄호가 나왔으면 괄호치기 잘못 되어있으므로 decide_num = 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//사칙연산일 경우 계산해준다.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (ins.peek() == BIG_RIGHT_PARENTHESIS) { //오른쪽 괄호가 대괄호일 경우
			ins.ignore();
			while (1) {
				if (operations.empty()) { //오른쪽 대괄호가 나왔는데 스택이 비어있으면 괄호치기 잘못 되어있으므로 decide_num을 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == BIG_LEFT_PARENTHESIS) { //왼쪽 대괄호일 경우 그냥 스택에서 빼기만 함
					operations.pop();
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS || operations.top() == MIDDLE_LEFT_PARENTHESIS) {
					// 오른쪽 대괄호가 나왔는데 왼쪽 소괄호나 중괄호가 나왔으면 괄호치기 잘못 되어있으므로 decide_num = 2로 초기화
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//사칙연산일 경우 계산해준다.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (isalpha(ins.peek())) {
			//만약 입력받은 것이 알파벳이라면 decide_num을 3으로 초기화하고 while문 종료
			decide_num = 3;
			break;
		}
		else {
			ins.ignore();
		}
	} //while(ins && ins.peek() == '\n') 닫는 괄호

	if (decide_num == 1) { //decide_num이 1이라면 입력버퍼 비워주고 메인함수에 에러문 throw
		ins.clear();
		ins.ignore(INT_MAX, '\n');
		throw DivideByZero();
	}
	else if (decide_num == 2) { //decide_num이 2라면 입력버퍼 비워주고 메인함수에 에러문 throw
		ins.clear();
		ins.ignore(INT_MAX, '\n');
		throw UnbalancedParentheses();
	}
	else if (decide_num == 3) { //decide_num이 3이라면 입력된 문자열이 EOI와 같은지 비교해서 같으면 종료, 아니면 안내문 출력
		string str;
		string eoi = "EOI";
		ins >> str;

		if (str.compare(eoi) == 0)
			exit(1);
		else
			cout << "종료를 원하면 'EOI'를 입력하세요" << endl;
	}
	else { //decide_num이 그대로 0이라면
		while (!operations.empty()) { //예를 들어 맨 마지막에 오른쪽 괄호가 안나왔으면 연산자 스택과 숫자 스택이
			//아직 차 있으므로 계산을 해줘야 한다. 그래서 연산자 스택이 비어있지 않으면 연산을 해준다.

			evaluate_stack(numbers, operations, decide_num);
			//문제는 여기서 남아있는 연산자 스택에 이상한게 들어있을 수도 있고, 맨 마지막에 0으로 나눠질 수도 있다.
			//그러므로 아래에서도 decide_num이 어떤 것으로 초기화되는지 계속 체크해준다.

			if (decide_num == 1) { //decide_num이 1이라면 입력버퍼 비워주고 메인함수에 에러문 throw
				ins.clear();
				ins.ignore(INT_MAX, '\n');
				throw DivideByZero();
			}
			else if (decide_num == 2) { //decide_num이 2라면 입력버퍼 비워주고 메인함수에 에러문 throw
				ins.clear();
				ins.ignore(INT_MAX, '\n');
				throw UnbalancedParentheses();
			}
		}
		if (ins.peek() == '\n')
			ins.ignore();

		printf("%.3f\n", numbers.top()); //위의 조건식을 다 통과했다면 제대로 된 계산식이므로 계산 결과를 출력해준다.
	}
}

void evaluate_stack(stack<double>& numbers, stack<char>& operations, int& decide_num) {
	//원래 코드에는 int& decide_num이 없었다
	//하지만 이 함수를 실행 중 0으로 나뉘는 경우, 숫자 스택에 2개가 없는 경우 등 여러가지 경우의 수가 발생했다.
	//그래서 이 함수를 빠져나갈 때 어떤 에러가 발생했는지 알 수 있도록 int& decide_num으로 함수의 인자를 추가하였다.

	if (numbers.empty()) { //숫자 스택이 비어있는 경우는 괄호치기기 잘못된 경우이므로 decide_num을 2로 초기화하고 함수 종료
		decide_num = 2;
		return;
	}
	double operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	if (numbers.empty()) { //숫자 스택에서 1개 빼고 나서 비어있는 경우도 괄호치기기 잘못된 경우이므로 decide_num을 2로 초기화하고 함수 종료
		decide_num = 2;
		return;
	}
	operand1 = numbers.top();
	numbers.pop();

	switch (operations.top()) {
	case '+': numbers.push(operand1 + operand2); break;
	case '-': numbers.push(operand1 - operand2); break;
	case '*': numbers.push(operand1 * operand2); break;
	case '/':
		if (operand2 == 0) { //나누는 수가 0일 경우 decide_num을 1로 초기화하고 함수 종료
			decide_num = 1;
			return;
		}
		numbers.push(operand1 / operand2);
		break;
	case '(':
	case '{':
	case '[':
		//연산자 스택에 왼쪽 괄호들이 들어가있는데 이 함수가 불려오는 경우가 있을수 있으므로 이럴 경우 decide_num을 2로 초기화하고 함수 종료
		decide_num = 2;
		return;
	}
	operations.pop();
}

int main() {
	while (1) {
		try {
			read_and_evaluate(cin);
		}
		catch (DivideByZero a) {
			a.what();
		}
		catch (UnbalancedParentheses b) {
			b.what();
		}
	}
}