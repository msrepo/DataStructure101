/*
 * queuejune1.c
 *
 *  Created on: Jun 1, 2015
 *      Author: linux
 */
/*
 * IMPLEMENTATION 2
 * 		Here, we will implement circular array to store elements
 * 		With this, the complication arises that its not possible to check if queue is empty with the earlier condition( q.rear < q.front)
 *
 * 		for that, we will adopt a convention that q.front will point to the location( or index) that is one step in front of the actual first element.
 * 		with this convention, we can use the condition (q.front == q.rear) to check if the queue is empty, but then (q.front == q.rear) also represents
 * 		the condition of the full queue. to differentiate between the two condition (queue is empty or queue is full), we will add one more strategy ( which is
 * 		to add only 4(MAXQUEUESIZE -1) elements although the internal array storage can store 5(MAXQUEUESIZE) elements
 */
#include <stdio.h>
#define MAXQUEUESIZE 5
struct queue {
	int items[MAXQUEUESIZE];
	int front, rear;
};

struct queue q;

void initializequeue() {
	q.rear = MAXQUEUESIZE - 1;
	q.front = MAXQUEUESIZE - 1;

}

int empty() {
	return q.rear == q.front;
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

	int earlierqrear = q.rear;
	if (q.rear == MAXQUEUESIZE - 1)
		q.rear = 0;
	else
		q.rear++;

	/* if full, print "Overflow!" */
	if (q.front == q.rear) {
		printf("Queue full!\n");
		//could not insert, so reset the position of q.rear
		q.rear = earlierqrear;
		return;
	}

	q.items[q.rear] = x;
	printf("%d inserted into queue front:%d rear:%d\n", x, q.front, q.rear);
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


	if (q.front == MAXQUEUESIZE - 1)
		q.front = 0;

	else
		q.front++;
	printf("%d removed from the queue\n", q.items[q.front]);
	return q.items[q.front];
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
