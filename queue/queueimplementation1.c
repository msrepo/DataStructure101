/*
 * queuejune1.c
 *
 *  Created on: Jun 1, 2015
 *      Author: linux
 */
#include <stdio.h>
#define MAXQUEUESIZE 5
struct queue {
	int items[MAXQUEUESIZE];
	int front, rear;
};

struct queue q;

void initializequeue() {
	q.rear = -1;
	q.front = 0;
}

int empty() {
	return q.rear < q.front;
}
/*
 * FUNCTION
 * 		insert
 *
 * DESCRIPTION
 * 		inserts into a queue if there is room
 * 		q.rear points to the last element in the queue
 * 		so, first q.rear is incremented, to empty valid place
 * 		where x is inserted
 *
 * 		the full condition is checked by q.rear == last valid array position
 */
void insert(int x) {
	/* if full, print "Overflow!" */
	if (q.rear == MAXQUEUESIZE - 1) {
		printf("Queue full!\n");
		return;
	}

	q.items[++q.rear] = x;
	printf("%d inserted into queue front:%d rear:%d\n", x,q.front,q.rear);
}

/*
 * FUNCTION
 * 		remove
 * 	DESCRIPTION
 * 		if queue is empty, returns -1
 * 		else returns value pointed to by current front pointer
 * 		and then increments front pointer to indicate the new front of the queue
 */
int removefromqueue() {
	/* if empty, print "Underflow!" */
	if (empty()) {
		printf("Queue is empty, cannot remove!\n");
		return -1;
	}

	printf("%d removed from the queue\n",q.items[q.front]);
	return q.items[q.front++];
}

int main() {

	initializequeue();
	insert(2);
	insert(9);
	insert(87);
	insert(3);
	insert(12);
	insert(0);
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();

	insert(2);
	insert(9);
	insert(87);
	insert(3);

	return 0;
}
