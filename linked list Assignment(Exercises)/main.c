#include <stdio.h>
#include <stdlib.h>
#define NUMNODES 500

struct nodetype {
	int info, next;
};

struct nodetype node[NUMNODES];
int list1 = -1;
int available;
void initialize() {
	available = 0;
	int i;
	for (i = 0; i < NUMNODES - 1; i++)
		node[i].next = i + 1;
	node[NUMNODES - 1].next = -1;

}

int getnode() {
	int p;
	if (available == -1) {
		printf("overflow\n");
		exit(1);
	}
	p = available;
	available = node[available].next;
	return p;
}

void freenode(int p) {
	node[p].next = available;
	available = p;
}

void insertafterGivenIndex(int p, int x) {
	int q;
	if (p == -1) {
		printf("invalid insertion\n");
		return;
	}
	q = getnode();
	node[q].info = x;
	node[q].next = node[p].next;
	node[p].next = q;
	return;
}

void deleteAfterGivenIndex(int p, int *px) {
	int q;
	if ((p == -1) || (node[p].next == -1)) {
		printf("invalid deletion\n");
		return;
	}

	q = node[p].next;
	*px = node[q].info;
	node[p].next = node[q].next;
	freenode(q);
	return;
}

void printlist(int headindex) {
	if (headindex == -1) {
		printf("list is empty.\n");
	}
	int currentindex = headindex;
	while (currentindex != -1) {
		printf("%d(index:%d , nextindex:%d)\t", node[currentindex].info,
				currentindex, node[currentindex].next);
		currentindex = node[currentindex].next;
	}
	printf("\n");
}

int appendTotheEnd(int list, int value) {

	if (list == -1)
		return -1;
	/* go to the end of list*/
	int currentindex = list;
	while (node[currentindex].next != -1) {
		currentindex = node[currentindex].next;
	}

	/* Now, currentindex points to the end of the list	 */

	/* insert after currentindex */

	insertafterGivenIndex(currentindex, value);
	return 1;
}

int deleteLastElement(int list) {
	if (list == -1)
		return -1;
	/* go to the second last node of list*/
	int currentindex = list;
	int deletedValue;
	while (currentindex != -1 && node[currentindex].next != -1
			&& node[node[currentindex].next].next != -1) {
		currentindex = node[currentindex].next;
	}

	/* Now, currentindex points to the end of the list	 */

	/* delete after currentindex */

	deleteAfterGivenIndex(currentindex, &deletedValue);
	printf("%d deleted(last element)\n", deletedValue);
	return 1;
}

int deleteNth(int *list, int n) {

	/* hop n -2 times which reaches the predecessor of the node we want to delete
	 * and then set the predecessor's next to next's next.
	 * free the nth node
	 * also check if there are actually n elements, otherwise we dont delete anything
	 *
	 *
	 * Also, Handle Special case: of deleting the 1st element in the list;
	 * deleteAfter is not possible while deleting the 1st element( i.e the head of the list)
	 */
	int i = 0;
	int currentindex = *list;
	int deletedValue;

	if(n < 1){
		return -1;
	}
	if(n == 1){
		deletedValue = node[*list].info;
		printf("Deleted Value:%d\n", deletedValue);
		*list = node[*list].next;
		freenode(currentindex);
		return 1;
	}
	while (currentindex != -1 && i < n - 2) {
		currentindex = node[currentindex].next;
		i++;
	}
	deleteAfterGivenIndex(currentindex, &deletedValue);
	printf("Deleted Value:%d\n", deletedValue);

	return 1;	//1 means successful operation
}

//search for first occurrence of "value"
int search(int list, int value) {
	int currentindex = list, distancefromhead = 0;
	while (currentindex != -1) {
		if (node[currentindex].info == value) {
			printf(
					"Found first occurence of value %d at position %d in the list.\n",
					value, distancefromhead + 1);
			return currentindex;
		}
		currentindex = node[currentindex].next;
		distancefromhead++;

	}
	return -1;
}

//for debug purpose
void printStorage(){
	int i;
	printf("%d(Available start index)\n",available);
	for(i = 0; i< NUMNODES; i++){
		printf("(Value:%d Index:%d)\t",node[i].info,node[i].next);
	}

}

//count the number of elements in the list
 int countElementsIntheList(int list){
	 int currentindex = list, numberoflements = 0;
	 while(currentindex != -1){
		 numberoflements++;
		 currentindex = node[currentindex].next;
	 }
	 printf("there are %d elements in the list\n",numberoflements);
	 return numberoflements;
 }

 //return sum of elements in the list

 int sumOfElements(int list){
	 int currentindex = list, sumOfElements = 0;
	 while(currentindex != -1){
		 sumOfElements+= node[currentindex].info;
		 currentindex = node[currentindex].next;
	 }
	 printf("Sum of ELements :%d\n",sumOfElements);
	 return sumOfElements;
 }

 int findthepredecessorForGivenIndex(int list, int nodeindex, int *predecessorindex){
	 int currentindex = list;
	 *predecessorindex = -1;
	 while(currentindex != nodeindex){
		 *predecessorindex = currentindex;
		 currentindex = node[currentindex].next;
	 }
	 return 1;
 }

 //move node(p) forward n positions
 int moveforward(int nodeindex, int n){

	 /*
	  * hop n-2 times to get to the predecessor and then insert after the predecessor
	  */
	 int i = 0, currentindex = nodeindex, earlierindex = -1, info;
	 while(i< n-2){
		 earlierindex = currentindex;
		 currentindex = node[currentindex].next;
	 }
	 if(earlierindex == -1){
		 /*
		  * this means we are trying to move the head node by n positions
		  */
		 return 1;
	 }
	 /*
	  * earlierindex points to the node after which we want to delete
	  */
	 deleteAfterGivenIndex(earlierindex,&info);




	 return 1;
 }


 //delete every 2nd elements from the list
 int deleteEvery2ndElement(int *list){

	 int i = 1, currentindex = *list,deletedValue;
	 while(currentindex != -1){
		 if(i%2 ==1){
			 //we are at the odd element position
			 deleteAfterGivenIndex(currentindex,&deletedValue);
			 printf("%d Deleted\n",deletedValue);
			 printlist(*list);
		 }

		 currentindex = node[currentindex].next;
	 }



	 return 1;
 }

/* free all nodes in the list */
int freeAllnodes(int *list) {
	if (*list == -1) {
		printf("list is empty\n");
		return -1;
	}
	int deletedValue;
	while (*list != -1) {
		printf("Before Deletion.\n");
		printlist(*list);
		deletedValue = node[*list].info;
		printf("%d deleted.\n", deletedValue);
		*list = node[*list].next;
		printf("After deletion.\n");
		printlist(*list);

	}
	return 1;
}
int createnode(int insertindex, int value) {
	if (insertindex != -1) {
		node[insertindex].info = value;
		node[insertindex].next = -1;
		return 1;
	}
	return -1;
}

int main() {
	initialize();
	//insert an element to the head
	int list1 = getnode();
	createnode(list1, 5);

	/* insert some more elements at the head */
	printf("inserted 8 and 2 at the head of the list.\n");
	insertafterGivenIndex(list1, 8);
	insertafterGivenIndex(list1, 2);
	printlist(list1);
	printf("\n\n\n");

	/* Successful search */
	printf("searching for Value 8 in the list.\n");
	search(list1, 8);
	printf("\n\n\n");

	/* find predecessor of given value */
	int nodeindex = search(list1, 8);
	int predecessor;
	findthepredecessorForGivenIndex(list1, nodeindex)

	/* append 11 to the end */
	printf("After appending 11 to the end of the list.\n");
	appendTotheEnd(list1, 11);
	printlist(list1);
	printf("\n\n\n");

	/*delete last element */
	printf("\n\n\n");
	printf("Before deleting last element\n");
	printlist(list1);
	deleteLastElement(list1);
	printf("After deleting last element\n");
	printlist(list1);
	printf("\n\n\n");

	/* delete 3rd element */
	printStorage();
	printf("Deleting the 3rd element\n");
	printlist(list1);
	deleteNth(&list1, 3);
	printf("after deletion of 3rd element.\n");
	printlist(list1);
	printStorage();
	printf("\n\n\n");

	/* Count number of elements */
	countElementsIntheList(list1);
	printf("\n\n\n");

	/* Return sum of integers in the list */
	sumOfElements(list1);
	printf("\n\n\n");

	/* some more insertions */
	insertafterGivenIndex(list1,21);
	insertafterGivenIndex(list1,33);
	insertafterGivenIndex(list1,8);
	insertafterGivenIndex(list1,19);
	insertafterGivenIndex(list1,114);
	printlist(list1);

	/* delete every 2nd element */
	printf("Deleting every 2nd element\n");
	deleteEvery2ndElement(&list1);
	printf("\n\n\n");

	/*free all nodes */
	printf("Freeing all the nodes in the list\n");
	freeAllnodes(&list1);
	printf("\n\n\n");

	return 0;
}
