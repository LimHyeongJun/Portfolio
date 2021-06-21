#include <iostream>
#include <stack>
#include <stdexcept>
#include <string>
#include <stdio.h>

using namespace std;
void evaluate_stack(stack<double>& numbers, stack<char>& operations, int& decide_num);

class DivideByZero { //0���� ���� �� ����ϴ� Ŭ����
public:
	void what() { cout << "Error!: divide by zero!" << endl; }
};
class UnbalancedParentheses { //��ȣġ�� �߸��� �� ����ϴ�
public:
	void what() { cout << "Error!: unbalanced parentheses" << endl; }
};

void read_and_evaluate(istream& ins) {
	const char DECIMAL = '.';
	const char LEFT_PARENTHESIS = '('; //���� �Ұ�ȣ
	const char RIGHT_PARENTHESIS = ')'; //������ �Ұ�ȣ
	const char MIDDLE_LEFT_PARENTHESIS = '{'; //���� �߰�ȣ
	const char MIDDLE_RIGHT_PARENTHESIS = '}'; //������ �߰�ȣ
	const char BIG_LEFT_PARENTHESIS = '['; //���� ���ȣ
	const char BIG_RIGHT_PARENTHESIS = ']'; //������ ���ȣ

	stack<double> numbers;
	stack<char> operations;
	double number;
	char symbol;
	int decide_num = 0;

	if (ins.peek() == '\n')
		ins.ignore();

	while (ins && ins.peek() != '\n') {
		if (decide_num == 1 || decide_num == 2) { //decide_num�� 1 �Ǵ� 2�̸� ������ �� ���̹Ƿ� �ݺ��� ����
			//�Ʒ� �ݺ��� ���ٰ� decide_num�� 1�̳� 2�� �ʱ�ȭ�Ǹ� ���⼭ ���� ���� �ɸ��Ƿ� ����ó�� ����
			break;
		}
		else if (isdigit(ins.peek()) || ins.peek() == DECIMAL) {
			ins >> number;
			numbers.push(number);
		}
		else if (ins.peek() == LEFT_PARENTHESIS || ins.peek() == MIDDLE_LEFT_PARENTHESIS || ins.peek() == BIG_LEFT_PARENTHESIS) {
			ins >> symbol; //(, {, [ �� �ϳ��� ��� operation ���ÿ� push
			operations.push(symbol);
		}
		else if (strchr("+-*/", ins.peek()) != NULL) {
			ins >> symbol;
			if (operations.empty()) { //���� operations������ ����ִٸ� �׳� ������ ����
				operations.push(symbol);
			}
			else { //������� �ʴٸ� ������ �켱���� ����ؼ� �ְ� ���� �� ������ 
				char top_operation = operations.top(); //������ ������ top�� �ӽ÷� ����
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
		} //strchr("+-*/", ins.peek()) != NULL �ݴ� ��ȣ
		else if (ins.peek() == RIGHT_PARENTHESIS) { //������ ��ȣ�� �Ұ�ȣ�� ���
			ins.ignore();
			while (1) {
				if (operations.empty()) { //������ �Ұ�ȣ�� ���Դµ� ������ ��������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num�� 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS) { //���� ���Ұ�ȣ�� ��� �׳� ���⸸ �Ѵ�.
					operations.pop();
					break;
				}
				else if (operations.top() == MIDDLE_LEFT_PARENTHESIS || operations.top() == BIG_LEFT_PARENTHESIS) {
					// ������ �Ұ�ȣ�� ���Դµ� ���� �߰�ȣ�� ���ȣ�� �������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num = 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//��Ģ������ ��� ������ش�.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (ins.peek() == MIDDLE_RIGHT_PARENTHESIS) { //������ ��ȣ�� �߰�ȣ�� ���
			ins.ignore();
			while (1) {
				if (operations.empty()) { //������ �߰�ȣ�� ���Դµ� ������ ��������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num�� 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == MIDDLE_LEFT_PARENTHESIS) { //���� �߰�ȣ�� ��� �׳� ���ÿ��� ���⸸ ��
					operations.pop();
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS || operations.top() == BIG_LEFT_PARENTHESIS) {
					// ������ �߰�ȣ�� ���Դµ� ���� �Ұ�ȣ�� ���ȣ�� �������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num = 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//��Ģ������ ��� ������ش�.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (ins.peek() == BIG_RIGHT_PARENTHESIS) { //������ ��ȣ�� ���ȣ�� ���
			ins.ignore();
			while (1) {
				if (operations.empty()) { //������ ���ȣ�� ���Դµ� ������ ��������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num�� 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == BIG_LEFT_PARENTHESIS) { //���� ���ȣ�� ��� �׳� ���ÿ��� ���⸸ ��
					operations.pop();
					break;
				}
				else if (operations.top() == LEFT_PARENTHESIS || operations.top() == MIDDLE_LEFT_PARENTHESIS) {
					// ������ ���ȣ�� ���Դµ� ���� �Ұ�ȣ�� �߰�ȣ�� �������� ��ȣġ�� �߸� �Ǿ������Ƿ� decide_num = 2�� �ʱ�ȭ
					decide_num = 2;
					break;
				}
				else if (operations.top() == '+' || operations.top() == '-' || operations.top() == '*' || operations.top() == '/') {
					//��Ģ������ ��� ������ش�.
					evaluate_stack(numbers, operations, decide_num);
				}
				else {
					decide_num = 2;
					break;
				}
			}
		}
		else if (isalpha(ins.peek())) {
			//���� �Է¹��� ���� ���ĺ��̶�� decide_num�� 3���� �ʱ�ȭ�ϰ� while�� ����
			decide_num = 3;
			break;
		}
		else {
			ins.ignore();
		}
	} //while(ins && ins.peek() == '\n') �ݴ� ��ȣ

	if (decide_num == 1) { //decide_num�� 1�̶�� �Է¹��� ����ְ� �����Լ��� ������ throw
		ins.clear();
		ins.ignore(INT_MAX, '\n');
		throw DivideByZero();
	}
	else if (decide_num == 2) { //decide_num�� 2��� �Է¹��� ����ְ� �����Լ��� ������ throw
		ins.clear();
		ins.ignore(INT_MAX, '\n');
		throw UnbalancedParentheses();
	}
	else if (decide_num == 3) { //decide_num�� 3�̶�� �Էµ� ���ڿ��� EOI�� ������ ���ؼ� ������ ����, �ƴϸ� �ȳ��� ���
		string str;
		string eoi = "EOI";
		ins >> str;

		if (str.compare(eoi) == 0)
			exit(1);
		else
			cout << "���Ḧ ���ϸ� 'EOI'�� �Է��ϼ���" << endl;
	}
	else { //decide_num�� �״�� 0�̶��
		while (!operations.empty()) { //���� ��� �� �������� ������ ��ȣ�� �ȳ������� ������ ���ð� ���� ������
			//���� �� �����Ƿ� ����� ����� �Ѵ�. �׷��� ������ ������ ������� ������ ������ ���ش�.

			evaluate_stack(numbers, operations, decide_num);
			//������ ���⼭ �����ִ� ������ ���ÿ� �̻��Ѱ� ������� ���� �ְ�, �� �������� 0���� ������ ���� �ִ�.
			//�׷��Ƿ� �Ʒ������� decide_num�� � ������ �ʱ�ȭ�Ǵ��� ��� üũ���ش�.

			if (decide_num == 1) { //decide_num�� 1�̶�� �Է¹��� ����ְ� �����Լ��� ������ throw
				ins.clear();
				ins.ignore(INT_MAX, '\n');
				throw DivideByZero();
			}
			else if (decide_num == 2) { //decide_num�� 2��� �Է¹��� ����ְ� �����Լ��� ������ throw
				ins.clear();
				ins.ignore(INT_MAX, '\n');
				throw UnbalancedParentheses();
			}
		}
		if (ins.peek() == '\n')
			ins.ignore();

		printf("%.3f\n", numbers.top()); //���� ���ǽ��� �� ����ߴٸ� ����� �� �����̹Ƿ� ��� ����� ������ش�.
	}
}

void evaluate_stack(stack<double>& numbers, stack<char>& operations, int& decide_num) {
	//���� �ڵ忡�� int& decide_num�� ������
	//������ �� �Լ��� ���� �� 0���� ������ ���, ���� ���ÿ� 2���� ���� ��� �� �������� ����� ���� �߻��ߴ�.
	//�׷��� �� �Լ��� �������� �� � ������ �߻��ߴ��� �� �� �ֵ��� int& decide_num���� �Լ��� ���ڸ� �߰��Ͽ���.

	if (numbers.empty()) { //���� ������ ����ִ� ���� ��ȣġ��� �߸��� ����̹Ƿ� decide_num�� 2�� �ʱ�ȭ�ϰ� �Լ� ����
		decide_num = 2;
		return;
	}
	double operand1, operand2;
	operand2 = numbers.top();
	numbers.pop();
	if (numbers.empty()) { //���� ���ÿ��� 1�� ���� ���� ����ִ� ��쵵 ��ȣġ��� �߸��� ����̹Ƿ� decide_num�� 2�� �ʱ�ȭ�ϰ� �Լ� ����
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
		if (operand2 == 0) { //������ ���� 0�� ��� decide_num�� 1�� �ʱ�ȭ�ϰ� �Լ� ����
			decide_num = 1;
			return;
		}
		numbers.push(operand1 / operand2);
		break;
	case '(':
	case '{':
	case '[':
		//������ ���ÿ� ���� ��ȣ���� ���ִµ� �� �Լ��� �ҷ����� ��찡 ������ �����Ƿ� �̷� ��� decide_num�� 2�� �ʱ�ȭ�ϰ� �Լ� ����
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