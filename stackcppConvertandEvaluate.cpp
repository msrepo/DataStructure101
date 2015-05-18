//============================================================================
// Name        : stackcpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;
#define STACKSIZE 20
#define MAXCOLUMNS 80
template<class X>
class stack {
private:
	int top;
	X *nodes;
public:
	stack();
	int empty(void);
	int full(void);
	void push(X);
	X pop(void);
	X pop(int &); //example of overloading pop to handle functions of popandtest
	X topofstack(void);
	~stack();
};
int isoperand(char c);
bool precedence(char topsymbol, char usersymbol);
void postfix(char *infix, char *postfix);
double operate(int symbol, double operand1, double operand2);
double evaluate(char *postr);

template<class T>
stack<T>::stack() {
	top = -1;
	nodes = new T[STACKSIZE];
}
template<class T>
stack<T>::~stack() {
	delete nodes;
}
template<class T>
int stack<T>::empty() {
	return top == -1;
}
template<class T>
int stack<T>::full() {
	return top == STACKSIZE - 1;
}
template<class T>
void stack<T>::push(T data) {
	if (full()) {
		cout << "Stack overflow!" << endl;
		return;
	}
	nodes[++top] = data;
}
template<class T>
T stack<T>::pop(void) {
	if (empty())
		cout << "stack empty!";
	return nodes[top--];
}
template<class T>
T stack<T>::topofstack(void) {
	if (empty())
		cout << "stack empty!";
	return nodes[top];
}
template<class T>
T stack<T>::pop(int &underflow) {
	char p;
	if (empty()) {
		underflow = true;
		return p; //return garbage
	} else {
		underflow = false;
		p = nodes[top--];

	}
	return p;
}

//returns true if topsymbol has higher precedence than usersymbol
bool precedence(char topsymbol, char usersymbol) {
	switch (usersymbol) {
	case '-':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
		case '^':
			return true;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}
		break;
	case '+':
		switch (topsymbol) {
		case '-':
		case '+':
			return false;
			break;
		case '*':
		case '/':
		case '^':
			return true;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}
		break;
	case '*':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
			return false;
			break;
		case '/':
		case '^':
			return true;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}

		break;
	case '/':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
			return false;
			break;
		case '^':
			return true;
			break;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}

		break;
	case '^':
	case '$':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
		case '^':
			return false;
			break;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}
		break;
	case '(':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
		case '^':
		case '(':
			//inner bracket has to be converted first, so ( has lower precedence than current (
			return false;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}
		break;
	case ')':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
		case '^':
			return true;
			//because we want to output the operators to the postfix string
			break;
		case '(':
			//false because we do not want to add parenthesis to the postfix string
			//also we wont add closing braces to the stack, instead we will neglect it
			return false;
			break;
		case ')':
			cout << "Found ) in the top of the stack, when inserting ')' "
					<< endl;
			exit(1);
			break;
		}
		break;
	default:
		cout << "unknown precedence USERSYMBOL=" << usersymbol << "\tTOPSYMBOL="
				<< topsymbol << endl;
		exit(1);
	}
	return false;
}

int isoperand(char c) {
	return isdigit(c) || isalpha(c);
}
void postfix(char *infix, char *postfix) {
	stack<char> operatorstack;

	int outposition = 0;
	int inposition = 0;
	char data;
	int underflow;
	char c;
	while ((c = infix[inposition++]) != '\0') {
		if (isoperand(c)) {
			postfix[outposition++] = c;

		} else {
			while (!operatorstack.empty()
					&& precedence(operatorstack.topofstack(), c)) {

				data = operatorstack.pop(underflow);
				postfix[outposition++] = data;
			}
			if (c != ')')

				operatorstack.push(c);
			else if (!operatorstack.empty())
				operatorstack.pop(); //pop corresponding opening braces for the closing brace we are dealing with right now

		}
	}
	while (!operatorstack.empty()) {
		postfix[outposition++] = operatorstack.pop();
	}
	postfix[outposition] = '\0';
	cout << "Postfix Expression:" << postfix << endl;

}

double evaluate(char *postfixstring) {
	int c, position;
	double operand1, operand2, value;
	stack<double> operandstack;

	for (position = 0; (c = postfixstring[position]) != '\0'; position++) {
		if (isdigit(c))
			operandstack.push((double) (c - '0'));
		else if (isalpha(c)) {
			cout
					<< "symbols could not be evaluated. Expression should consist of digits."
					<< endl;
		} else {
			operand2 = operandstack.pop();
			operand1 = operandstack.pop();
			value = operate(c, operand1, operand2);
			operandstack.push(value);
		}
	}
	return (operandstack.pop());
}

double operate(int symbol, double operand1, double operand2) {
	switch (symbol) {
	case '+':
		return operand1 + operand2;

	case '-':
		return operand1 - operand2;
	case '/':
		return operand1 / operand2;
	case '$':
	case '^':
		return pow(operand1, operand2);
	case '*':
		return operand1 * operand2;
	default:
		cout << "illegal operator" << symbol << endl;
		exit(1);
		break;
	}
}
int main() {
	char infixstr[MAXCOLUMNS];
	char postfixstr[MAXCOLUMNS];
	int position = 0;
	while ((infixstr[position++] = cin.get()) != '\n')
		;
	infixstr[--position] = '\0';
	cout << "Original Expression:" << infixstr << endl;
	postfix(infixstr, postfixstr);
	cout << "Postfix Expression:" << postfixstr << endl;
	cout << "Evaluated Value:" << evaluate(postfixstr) << endl;
	return 0;

}

