/*
 * main.c
 *
 *  Created on: Jun 4, 2015
 *      Author: linux
 */
#include "linkedllistAsADataStructure.h"

int main(){

	struct node * listA = NULL;

	insertIntoHeadLinkedList(&listA,4);
	insertIntoHeadLinkedList(&listA,89);
	insertIntoHeadLinkedList(&listA,7);
	insertIntoHeadLinkedList(&listA,4);
	insertIntoHeadLinkedList(&listA,89);
	insertIntoHeadLinkedList(&listA,7);
	insertIntoHeadLinkedList(&listA,4);
	insertIntoHeadLinkedList(&listA,89);
	insertIntoHeadLinkedList(&listA,7);
	insertIntoHeadLinkedList(&listA,4);
	insertIntoHeadLinkedList(&listA,89);
	insertIntoHeadLinkedList(&listA,7);
	removeFromHeadLinkedList(&listA);
	removeFromHeadLinkedList(&listA);
	removeFromHeadLinkedList(&listA);
	removeFromHeadLinkedList(&listA);
	insertIntoHeadLinkedList(&listA,4);
	insertIntoHeadLinkedList(&listA,89);
	insertIntoHeadLinkedList(&listA,7);
	deleteAllOccurenceOf(&listA,7);

}

