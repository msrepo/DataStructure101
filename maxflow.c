/*
 * maxflow.c
 *
 *  Created on: May 28, 2015
 *      Author: linux
 */
#include <stdlib.h>
#include <stdio.h>

#define MAXNODES 4
#define TRUE 1
#define FALSE 0

#define INFINITY RAND_MAX
int anyOneElementIsTrue(int[]);

void maxflow(int capacity[][MAXNODES], int s, int t, int *ptotalflow);

int main() {
	//exmple graph
	int graphcapacity[MAXNODES][MAXNODES] = { { 0, 4, 4, 0 }, { 0, 0, 5, 3 }, {
			0, 0, 0, 4 }, { 0, 0, 0, 0 } };
	int totalflow;
	int s = 0;
	int t = 3;
	maxflow(graphcapacity, s, t, &totalflow);
	printf("Total flow possible: %d\n", totalflow);

	return 0;
}
void maxflow(int capacity[][MAXNODES], int s, int t, int *ptotalflow) {

	int node, i, x, predecessornode, flow[MAXNODES][MAXNODES];
	int precedingnode[MAXNODES], improvedflownumber[MAXNODES];
	int isEdgeEndofPartialPath[MAXNODES], isforwardedge[MAXNODES],
			isEdgeOnPath[MAXNODES];

	//start with empty flow network
	for (node = 0; node < MAXNODES; node++) {
		for (i = 0; i < MAXNODES; i++) {
			flow[node][i] = 0;
		}
	} //end for

	//reset total flow
	*ptotalflow = 0;

	do {
		//attempt to find a semipath from s to t

		//reset flags
		for (node = 0; node < MAXNODES; node++) {
			isEdgeOnPath[node] = FALSE;
			isEdgeEndofPartialPath[node] = FALSE;
		}

		//initial condition
		//starting node is always a part of the partial path
		isEdgeEndofPartialPath[s] = TRUE;
		isEdgeOnPath[s] = TRUE;

		//set improvedflownumber to some large number so any value is better than this INIFINTE NUMBER
		//improvedflownumber[node] saves the value of the smallest possible flow from s to that node along the current semipath
		//we assume s(source) can provide infinite flow
		improvedflownumber[s] = INFINITY;

		//while we have not found a complete path( i.e t(target) is not yet part of the semipath and there is still some way to extend the partial path
		while ((isEdgeOnPath[t] == FALSE)
				&& (anyOneElementIsTrue(isEdgeEndofPartialPath))) {
			//attempt to extend an existing path
			for (node = 0; isEdgeEndofPartialPath[node] == FALSE; node++)
				;
			//at this point node index is end of a partial path
			isEdgeEndofPartialPath[node] = FALSE; //this will no longer be a partial path
			//DEBUG
			fprintf(stderr,"Extended semipath from %d  ",node);
			//but which node extends from this node?
			for (i = 0; i < MAXNODES; i++) {
				if ((flow[node][i] < capacity[node][i])
						&& (isEdgeOnPath[i] == FALSE)) {
					isEdgeOnPath[i] = TRUE;
					isEdgeEndofPartialPath[i] = TRUE;
					precedingnode[i] = node;
					isforwardedge[i] = TRUE;
					x = capacity[node][i] - flow[node][i];
					improvedflownumber[i] =
							(improvedflownumber[node] < x) ?
									improvedflownumber[node] : x;
					//DEBUG
					fprintf(stderr,"to %d(Forward edge)\t precedingnode[%d]=%d\n",i,i,node);
					break;
				} //found a forward edge

				//if we did not find a forward edge from node to i, lets search for backward edge from some i to node
				if ((flow[i][node] > 0) && (isEdgeOnPath[i] == FALSE)) {
					isEdgeEndofPartialPath[i] = TRUE;
					isEdgeOnPath[i] = TRUE;
					precedingnode[i] = node;
					isforwardedge[i] = FALSE;
					improvedflownumber[i] =
							(improvedflownumber[node] < flow[i][node]) ?
									improvedflownumber[node] : flow[i][node];
					//DEBUG
					fprintf(stderr,"to %d(backward edge)\t precedingnode[%d]=%d\n",i,i,node);
					break;
				} //found a backward edge


			} //found a node to extend from the current end
		} //either found a complete path or could not extend the semipath

		//DEBUG
		fprintf(stderr,"flow through the path:%d\n",x);

		//now increase flow on this complete path
		if (isEdgeOnPath[t] == TRUE) {
			//flow on semipath to t can be increased
			x = improvedflownumber[t];
			*ptotalflow += x;
			node = t;
			while (node != s) {
				//travel back the path from t to s
				predecessornode = precedingnode[node];
				isforwardedge[node] ?
						(flow[predecessornode][node] += x) :
						(flow[node][predecessornode] -= x);

				//DEBUG
				isforwardedge[node] ?
						fprintf(stderr,"Foward Edge ") :
						fprintf(stderr,"Backward Edge ");
				fprintf(stderr,"Returning back from %d to %d(Flow from predecessornode(%d) to node(%d):%d\n",node,predecessornode,predecessornode,node,flow[predecessornode][node]);
				node = predecessornode;


			} //reached source node

		} //flow increase done

		//print DEBUG INFO
		fprintf(stderr,"Maxflow:%d\n",*ptotalflow);


	} while (isEdgeOnPath[t] == TRUE); // (could not find a complete path so cannot improve the result
}

int anyOneElementIsTrue(int elementarray[]) {
	int i;
	for (i = 0; i < MAXNODES; i++) {
		if (elementarray[i] == TRUE)
			return TRUE;
	}
	return FALSE;
}
