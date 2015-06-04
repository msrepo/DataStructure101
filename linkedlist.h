/*
 * linkedlist.h
 *
 *  Created on: Jun 4, 2015
 *      Author: linux
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>
#include <stdio.h>

struct node {
	int info;
	struct node *next;
};



int isempty(struct node * list);
struct node * getnode();
void freenode(struct node * p);
void insertIntoHeadLinkedList(struct node ** list, int data);
int removeFromHeadLinkedList(struct node ** list);
void printLinkedList(struct node *list);
int isempty(struct node * list){
	return (list == NULL);
}
void freenode(struct node *p){
	free(p);
}
void printLinkedList(struct node * givenlist){
	struct node * list = givenlist;
	for(;list != NULL;list = list->next){
		printf("%d-->",list->info);
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

#endif /* LINKEDLIST_H_ */
