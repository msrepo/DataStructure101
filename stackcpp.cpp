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
using namespace std;
#define STACKSIZE 20
#define MAXCOLUMNS 80
class stack {
private:
	int top;
	char *nodes;
public:
	stack();
	int empty(void);
	int full(void);
	void push(char &);
	char pop(void);
	char pop(int &); //example of overloading pop to handle functions of popandtest
	char topofstack(void);
	~stack();
};
stack::stack() {
	top = -1;
	nodes = new char[STACKSIZE];
}

stack::~stack() {
	delete nodes;
}

int stack::empty() {
	return top == -1;
}

int stack::full() {
	return top == STACKSIZE - 1;
}
void stack::push(char &data) {
	if (full()) {
		cout << "Stack overflow!" << endl;
		return;
	}
	nodes[++top] = data;
}

char stack::pop(void) {
	if (empty())
		cout << "stack empty!";
	return nodes[top--];
}

char stack::topofstack(void) {
	if (empty())
		cout << "stack empty!";
	return nodes[top];
}
char stack::pop(int &underflow) {
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
			<<endl;
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
			<<endl;
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
			<<endl;
			exit(1);
			break;
		}

		break;
	case '^':
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
			<<endl;
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
			<<endl;
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
	stack operatorstack;

	int outposition = 0;
	int inposition = 0;
	char data;
	int underflow;
	char c;
	while ((c = infix[inposition++]) != '\0') {
		if (isoperand(c)) {
			postfix[outposition++] = c;

		} else {
			while (!operatorstack.empty() && precedence(operatorstack.topofstack(), c)) {

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
	return 0;

}

