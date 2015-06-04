/*
 * linkedlist.h
 *
 *  Created on: Jun 4, 2015
 *      Author: linux
 */

#ifndef LINKEDLLISTASADATASTRUCTURE_
#define LINKEDLLISTASADATASTRUCTURE_

#include <stdlib.h>
#include <stdio.h>

struct node {
	int info;
	struct node *next;
};
typedef struct node *NODEPOINTER;
typedef NODEPOINTER *PTRTONODEPOINTER;
int isempty(struct node * list);
struct node * getnode();
void freenode(struct node * p);
void insertIntoHeadLinkedList(struct node ** list, int data);
int removeFromHeadLinkedList(struct node ** list);
void printLinkedList(struct node *list);
int deleteAfter(struct node **givenNode);
int insertAfter(struct node **givenNode, int data);
int deleteAllOccurenceOf(struct node** list, int data);

int isempty(struct node * list) {
	return (list == NULL);
}
void freenode(struct node *p) {
	free(p);
}
void printLinkedList(struct node * givenlist) {
	struct node * list = givenlist;
	for (; list != NULL; list = list->next) {
		printf("%d-->", list->info);
	}
	printf("NULL\n");
}
struct node * getnode() {
	return (struct node *) malloc((unsigned) sizeof(struct node));
}
void insertIntoHeadLinkedList(struct node **list, int data) {

	struct node *newnode = getnode();
	newnode->info = data;

	newnode->next = *list;
	*list = newnode;
	printf("%d inserted into linked list\n", data);
	printLinkedList(*list);
}

int removeFromHeadLinkedList(struct node ** list) {
	if (isempty(*list)) {
		printf("list is empty.Cannot remove an element\n");
		return -1;
	}
	int x;
	struct node * returnnode = *list;
	x = returnnode->info;
	(*list) = (*list)->next;
	freenode(returnnode);

	printf("%d removed from the linked list\n", x);
	printLinkedList(*list);
	return x;
}

int insertAfter(struct node **givenNode, int data) {
	if (givenNode == NULL) {
		printf("insertion after NULL node is not possible.\n");
		return 0;
	}
	struct node *newnode = getnode();
	newnode->info = data;
	newnode->next = (*givenNode)->next;
	(*givenNode)->next = newnode;
	return 1;
}
int deleteAfter(struct node **givenNode) {
	if ((*givenNode) == NULL) {
		printf("deletion after a NULL node is not possible.\n");
		return 0;
	}
	struct node *deletenode = (*givenNode)->next;
	int x = deletenode->info;
	(*givenNode)->next = deletenode->next;
	freenode(deletenode);
	printf("Deleted %d\n", x);
	return 1;
}

int deleteAllOccurenceOf(struct node** listptr, int data) {
	/* search for occurences of data and keep track of its predecessors too */
	int count = 0;
	struct node *tempNode = *listptr;
	struct node *predecessorNode = NULL;
	for (; (tempNode) != NULL; predecessorNode = tempNode, (tempNode) =
			(tempNode)->next) {
		/*
		 * case 1:remove from the head
		 */
		if (tempNode->info == data && (predecessorNode == NULL)) {

			tempNode = tempNode->next;
			freenode(*listptr);
			*listptr = tempNode;
			printf("Deleted %d\n",data);
			count++;

		}
		else if ((tempNode)->info == data) {
			/*
			 * case 2: remove from the middle
			 */
			deleteAfter(&predecessorNode);
			count++;

		}

		printLinkedList(*listptr);
	}

	printf("Found %d occurrences of %d\n", count, data);
	return count;
}

#endif /* LINKEDLLISTASADATASTRUCTURE_ */
