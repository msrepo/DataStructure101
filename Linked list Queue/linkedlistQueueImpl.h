/*
 * linkedlistQueueImpl.h
 *
 *  Created on: Jun 4, 2015
 *      Author: linux
 */

#ifndef LINKEDLISTQUEUEIMPL_H_
#define LINKEDLISTQUEUEIMPL_H_

#include <stdlib.h>
#include <stdio.h>

struct node {
	int info;
	struct node *next;
};

struct queue {
	struct node* front, *rear;
};

int isQueueEmpty();
struct node * getnode();
void insert(struct queue ** q, int data);
int removefromQueue(struct queue **q);
void printqueue(struct queue *q);
void freenode(struct node * n);

struct node* getnode() {
	return (struct node*) malloc(sizeof(struct node));
}

void freenode(struct node *n) {
	free(n);
}
void printqueue(struct queue *q) {
	struct node *tempnode = q->front;
	for (; tempnode != NULL; tempnode = tempnode->next)
		printf("%d-->", tempnode->info);
	printf("NULL\n");
}

int isQueueEmpty(struct queue * q) {
	return (q->front == q->rear) && (q->front == NULL);
}

void insert(struct queue **q, int data) {
	struct node * newnode = getnode();
	newnode->info = data;
	if ((*q)->rear == NULL) {

		(*q)->front = (*q)->rear = newnode;

	} else {
		(*q)->rear->next = newnode;

		(*q)->rear = newnode;
	}
	printf("%d inserted\n", data);
	printqueue(*q);

}

int removefromQueue(struct queue **q) {
	if (isQueueEmpty(*q)) {
		printf("Queue is empty\n");
		return -1;
	}

	int x;
	x = (*q)->front->info;

	struct node *deletenode = (*q)->front;

	(*q)->front = (*q)->front->next;
	if ((*q)->front == NULL)
		(*q)->rear = NULL;

	freenode(deletenode);

	printf("%d removed\n", x);
	printqueue(*q);
	return x;

}

#endif /* LINKEDLISTQUEUEIMPL_H_ */
