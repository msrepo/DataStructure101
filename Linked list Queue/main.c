/*
 * main.c
 *
 *  Created on: Jun 4, 2015
 *      Author: linux
 */

#include "linkedlistQueueImpl.h"
int main(){

	struct queue *q = malloc(sizeof(struct queue));
	q->front = NULL;
	q->rear = NULL;

	printf("Queue is empty?%d\n",isQueueEmpty(q));
	insert(&q,3);
	insert(&q,5);
	insert(&q,3);
	insert(&q,5);
	insert(&q,3);
	insert(&q,5);
	removefromQueue(&q);




	return 0;
}
