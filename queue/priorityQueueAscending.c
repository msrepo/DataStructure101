/*
 * queue1.c
 *
 *  Created on: May 28, 2015
 *      Author: linux
 */

//Basic queue implementation
#include <stdio.h>
#include <stdlib.h>
#define MAXQUEUESIZE 5
struct queue {
	int items[MAXQUEUESIZE];
	int front, rear;
};

struct queue q;

//function name: empty
//returns 1 if the given queue is empty otherwise returns 0
int empty() {
	return (q.rear == q.front);
}
//circularly obtain the next index
//Example if MAXQUEUESIZE is 3
/*
 * index= 0,1 returns index + 1
 * index = 2  returns 0
 */
int circularincrement(int index) {
	if (index == MAXQUEUESIZE - 1)
		return 0;
	else if (index < MAXQUEUESIZE - 1)
		return index + 1;
	else {
		printf("invalid index %d\n", index);
		return RAND_MAX; //return garbage, large value
	}
}

int circulardecrement(int index) {
	if (index == 0)
		return MAXQUEUESIZE - 1;
	else if (index > 0 && index <= MAXQUEUESIZE - 1)
		return index - 1;
	else {
		printf("invalid index %d\n", index);
		return RAND_MAX; //return garbage, large value
	}
}
/*
 * returns the number of elements between startindex(exclusive) and endindex(inclusive)
 * assumption: the maxqueuelength in MAXQUEUESIZE
 */
int countelementsinCircularQueue(int startindex, int endindex) {

	if (startindex < endindex)
		return (endindex - startindex);
	else
		return (endindex - startindex + MAXQUEUESIZE);
}

void printQueueDebugmode() {
	int i;
	fprintf(stderr, "Front: %d  Rear:%d  Queue[Items]:", q.front, q.rear);
	for (i = 0; i < MAXQUEUESIZE; i++)
		fprintf(stderr, "\t%d", q.items[i]);
	fprintf(stderr, "\n");
}
//function name: insert
//inserts into queue, the newly inserted element joins the end of queue
void insertintoqueue(int x) {

	if (q.front == circularincrement(q.rear)) {
		printf("could not insert %d into the queue.. Queue Overflow\n", x);
	} else {
		q.rear = circularincrement(q.rear);
		q.items[q.rear] = x;
		printf("%d inserted\n", x);
	}

	printQueueDebugmode();
}

//function name:remove
//remove from the front of the queue
void removefromqueue() {
	int smallestvalueindex, temporaryindex,smallestValue, count, i;
	if (empty()) {
		printf("queue is empty! could not remove!!!\n");

	} else {
		/*
		 * find the node with the smallest priority value(ascending priority queue)
		 */

		temporaryindex = smallestvalueindex = circularincrement(q.front);
		smallestValue = q.items[smallestvalueindex];
		while ((temporaryindex) != q.rear) {
			if (q.items[(temporaryindex)]
					< smallestValue) {
				smallestValue = q.items[(temporaryindex)];
				smallestvalueindex = (temporaryindex);
			}
			temporaryindex= circularincrement(temporaryindex);

		}
		//DEBUG:
		fprintf(stderr,"smallest value:%d smallest value index:%d\n",smallestValue,smallestvalueindex);

		/*
		 * at this point, smallest value index points to the node we need to remove
		 */

		/*
		 * now, move all nodes from smallestvalueindex+1 to q.rear by one position to the left
		 */
		count = countelementsinCircularQueue(smallestvalueindex, q.rear);
		for (i = 0; i < count; i++) {
			q.items[smallestvalueindex] = q.items[circularincrement(
					smallestvalueindex)];
			smallestvalueindex = circularincrement(smallestvalueindex);
		}

		q.rear = circulardecrement(q.rear);

		printf("%d removed\n", smallestValue);

	}
	printQueueDebugmode();
	/*
	 * alternative 1:
	 * return q.items[q.front++];
	 */
}

int main() {
	//initialize the queue
	q.front = MAXQUEUESIZE - 1;
	q.rear = MAXQUEUESIZE - 1;

	printf("Is queue empty?:%d\n", empty());

	insertintoqueue(3);
	insertintoqueue(9);
	insertintoqueue(1);
	insertintoqueue(45);
	insertintoqueue(10);
	insertintoqueue(9);
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();
	removefromqueue();
	insertintoqueue(3);
	insertintoqueue(9);
	insertintoqueue(3);
	insertintoqueue(9);
	insertintoqueue(3);
	insertintoqueue(9);

	return 0;
}

