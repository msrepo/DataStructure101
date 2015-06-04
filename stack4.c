/*
 * stack3.c
 *
 *  Created on: May 14, 2015
 *      Author: linux
 */

#define MAXSTACKSIZE 100
#define MAXCOLUMNS 80
#define FALSE 0
#define TRUE 1
#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>//for exit() function
void postfix(char *, char *);

struct Stack {
	char items[MAXSTACKSIZE];
	int top;
};

int empty(struct Stack *);
int full(struct Stack *);
void push(struct Stack *, char data);
char pop(struct Stack *);
void popandtest(struct Stack *, char *, int *);

int empty(struct Stack *s) {
	return s->top == -1;
}
int full(struct Stack *s) {
	return s->top == MAXSTACKSIZE - 1;
}
void push(struct Stack *s, char data) {
	if (full(s)) {
		printf("%s\n", "Stack overflow!");
		exit(1);
	}
	s->items[++s->top] = data;
}

char pop(struct Stack *s) {
	if (empty(s)) {
		printf("%s\n", "Stack underflow!");
		exit(1);
	}
	return s->items[s->top--];
}

void popandtest(struct Stack *s, char *data, int *underflow) {
	if (!empty(s)) {
		*data = s->items[s->top--];
		*underflow = FALSE;
		return;
	} else {
		*underflow = TRUE;
		return;
	}
}
int isoperand(char c) {
	return isdigit(c) || isalpha(c);
}
char stacktop(struct Stack *s) {
	return s->items[s->top];
}
//returns true if topsymbol has higher precedence than usersymbol
int precedence(char topsymbol, char usersymbol) {
	switch (usersymbol) {
	case '-':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
		case '/':
		case '^':
			return TRUE;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
			exit(1);
			break;
		}
		break;
	case '+':
		switch (topsymbol) {
		case '-':
		case '+':
			return FALSE;
			break;
		case '*':
		case '/':
		case '^':
			return TRUE;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
			exit(1);
			break;
		}
		break;
	case '*':
		switch (topsymbol) {
		case '-':
		case '+':
		case '*':
			return FALSE;
			break;
		case '/':
		case '^':
			return TRUE;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
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
			return FALSE;
			break;
		case '^':
			return TRUE;
			break;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
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
			return FALSE;
			break;
		case '(':
			//because we dont want to pop the opening braces until we find its corresponding closing braces
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
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
			return FALSE;
			break;
		case ')':
			//closing brace should never have been placed into the stack
			printf("Found ) in the top of the stack, when inserting ')' ");
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
			return TRUE;
			//because we want to output the operators to the postfix string
			break;
		case '(':
			//false because we do not want to add parenthesis to the postfix string
			//also we wont add closing braces to the stack, instead we will neglect it
			return FALSE;
			break;
		case ')':
			printf("Found ) in the top of the stack, when inserting ')' ");
			exit(1);
			break;
		}
		break;
	default:
		printf("%s%c%s%c\n", "unknown precedence USERSYMBOL=", usersymbol,
				"\tTOPSYMBOL=", topsymbol);
		exit(1);
	}
	return FALSE;
}
void postfix(char *infix, char *postfix) {
	struct Stack operatorstack;
	int outposition = 0;
	int inposition = 0;
	char data;
	int underflow;
	char c;
	while ((c = infix[inposition++]) != '\0') {
		if (isoperand(c)) {
			postfix[outposition++] = c;

		} else {
			while (!empty(&operatorstack)
					&& precedence(stacktop(&operatorstack), c)) {
				popandtest(&operatorstack, &data, &underflow);
				postfix[outposition++] = data;
			}
			if (c != ')')
				push(&operatorstack, c);
			else
				if(!empty(&operatorstack))
					pop(&operatorstack);//pop corresponding opening braces for the closing brace we are dealing with right now

		}
	}
	while (!empty(&operatorstack)) {
		postfix[outposition++] = pop(&operatorstack);
	}
	postfix[outposition] = '\0';
	printf("Postfix Expression:%s\n", postfix);

}
int main() {
	char infixstr[MAXCOLUMNS];
	char postfixstr[MAXCOLUMNS];
	int position = 0;
	while ((infixstr[position++] = getchar()) != '\n')
		;
	infixstr[--position] = '\0';
	printf("Original Expression:%s\n", infixstr);
	postfix(infixstr, postfixstr);
	printf("Postfix Expression:%s\n", postfixstr);
	return 0;

}
