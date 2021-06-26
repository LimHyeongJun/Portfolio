/*
 * Student ID: 2016726082
 * Name: 임형준(Lim Hyeong Jun)
 */
#include <iostream>
#include <stack>
#include <string.h>
#include <string>

using namespace std;

void postfix(string str);
void evaluate_stack(stack<string> &numbers, stack<string> &operations);

int main(void) {
    while (1) {
        string str;
        cout << "Input exp(input 'q' to terminate): ";
        cin >> str;

        postfix(str);
    }

    return 0;
}

void postfix(string str) {
    stack<string> numbers;
    stack<string> operations;
    string temp;

    if (str == "q") {
        cout << ">> Terminate input." << endl;
        exit(0);
    }

    for (int i = 0; i < str.length(); i++) {
        if (isupper(str[i]) || islower(str[i])) {
            string temp = str.substr(i, 1);
            numbers.push(temp);
        } else if (str[i] == '(') {
            operations.push(str.substr(i, 1));
        } else if (strchr("+-*/", str[i]) != NULL) {
            if (operations.empty()) {
                operations.push(str.substr(i, 1));
            } else {
                string top = operations.top();
                switch (str[i]) {
                case '+':
                case '-':
                    if (top.compare("(") == 0) {
                        operations.push(str.substr(i, 1));
                        break;
                    } else if (top.compare("*") == 0 || top.compare("/") == 0 ||
                               top.compare("+") == 0 || top.compare("-") == 0) {
                        evaluate_stack(numbers, operations);
                        operations.push(str.substr(i, 1));
                        break;
                    }
                case '*':
                case '/':
                    if (top.compare("+") == 0 || top.compare("-") == 0 ||
                        top.compare("(") == 0) {
                        operations.push(str.substr(i, 1));
                        break;
                    } else if (top.compare("*") == 0 || top.compare("/") == 0) {
                        evaluate_stack(numbers, operations);
                        operations.push(str.substr(i, 1));
                        break;
                    }
                }
            }
        } // strchr("+-*/", str[i]) != NULL 끝나는 괄호
        else if (str[i] == ')') {
            while (1) {
                string top = operations.top();
                if (top.compare("(") == 0) {
                    operations.pop();
                    break;
                } else if (top.compare("*") == 0 || top.compare("/") == 0 ||
                           top.compare("+") == 0 || top.compare("-") == 0) {
                    evaluate_stack(numbers, operations);
                }
            }
        }
    } //큰 for문 닫는 괄호

    while (!operations.empty()) { //스택이 아직 차 있을 경우 계산을 해줘야 한다.
        evaluate_stack(numbers, operations);
    }

    cout << "Postfix notation: " << numbers.top() << endl;
}

void evaluate_stack(stack<string> &numbers, stack<string> &operations) {
    string operand1, operand2;
    operand2 = numbers.top();
    numbers.pop();
    operand1 = numbers.top();
    numbers.pop();

    operand1.append(operand2);
    operand1.append(operations.top());
    numbers.push(operand1);
    operations.pop();
}
