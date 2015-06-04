/*
 * quicksort.c
 *
 *  Created on: Jun 1, 2015
 *      Author: linux
 */
#define ARRAYSIZE 10
#include <stdio.h>
void quicksort(int data[], int lowerindex, int upperindex);
void partition(int data[], int lowerindex, int upperindex, int *partitionindex);

int main() {
	int data[ARRAYSIZE] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	int i;
	//before
	for (i = 0; i < ARRAYSIZE; i++)
		printf("\t%d", data[i]);
	printf("\n");

	quicksort(data, 0, ARRAYSIZE - 1);

	//after
	for (i = 0; i < ARRAYSIZE; i++)
		printf("\t%d", data[i]);
	printf("\n");

	return 0;

}

void partition(int data[], int lowerindex, int upperindex, int *partitionindex) {
	int temp, i;
	int down = lowerindex;
	int up = upperindex;
	int partitionelement = data[lowerindex];
	while (down < up) {
		/*
		 * increment down index until we find an element greater than partition element
		 */
		while (data[down] <= partitionelement && down < upperindex)
			down++;

		/*
		 * decrement up index until we find an element smaller than or equal to partition element
		 */
		while (data[up] > partitionelement)
			up--;

		/*
		 * swap the values at up and down index
		 */
		if (down < up) {
			temp = data[up];
			data[up] = data[down];
			data[down] = temp;
		}

	}
	/*
	 * finally, swap the value at lowerindex with the element at up pointer(index)
	 */
	data[lowerindex] = data[up];
	data[up] = partitionelement;
	*partitionindex = up;
	printf("partition index(%d)\t", up);
	for (i = 0; i < ARRAYSIZE; i++)
		printf("\t%d", data[i]);
	printf("\n");
}
void quicksort(int data[], int lowerindex, int upperindex) {
	printf("quicksorting from index %d to %d\t", lowerindex, upperindex);

	int j;
	if (lowerindex >= upperindex)
		return; //single or empty element does not require sorting
	partition(data, lowerindex, upperindex, &j);
	printf("j = %d\t", j);
	quicksort(data, lowerindex, j - 1);
	quicksort(data, j + 1, upperindex);
}
