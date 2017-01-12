#include <stdio.h>		/* printf, scanf, puts, NULL */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <iostream>
#include <string>
#include "printers.h"
//#include "graphsFunctions.h"       no need cause matrixIntitization.h was included in graphsFunctions
//#include "LinLisGra.h"	/* utility lib. for representing the graph as linked list */   no need cause already included in matrixIntitization.h header 
//#include "matrixIntilization.h"  no need cause already included in printers.h header 
using namespace std;
using namespace printer;
using namespace Intilization;
using namespace graphsFunctions;
#define BILLION 1000000000L

void floyd( LinLisGra* W, LinLisGra* D, LinLisGra* P, int vertices)
{
	int i, j, k;

	 for (i = vertices-1; i >= 0; i--)
	 	for (j = vertices-1; j >= 0; j--)
	 		P->addUndirectedLink(i, j, 0);

	*D = *W->copy();

	for (k = 0; k < vertices; k++)
		for (i = 0; i < vertices; i++)
			for (j = 0; j < vertices; j++)
			{
				int indexDIK = D->getAttribute(i, k);  // assigned then to variable to avoid calling them several times
				int indexDKJ = D->getAttribute(k, j);
				int indexDIJ = D->getAttribute(i, j);
				if (indexDIK + indexDKJ < indexDIJ)
				{
					P->setAttribute(i, j, k+1);
					D->setAttribute(i, j, indexDIK + indexDKJ);
				}
			}
}


int main()
{
	srand(time(NULL)); /* initialize random seed: */
	int vertices, decision;
	LinLisGra W;
	// int n = 12;			// for test case 2
	printf("Enter the number of vertices: \n");
	scanf("%d", &vertices);				// read the number entered by the user
	struct timespec start, end;
	double diff;
	printf("Enter which function you want to  be executed (1) for complete or (any key) for sparse: \n");
	scanf("%d", &decision);
	if(1 == decision)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);			// start recording time
		W = completeLL(vertices);	//call the complete function to intialize the 1D array randomly
	}
	else{
		clock_gettime(CLOCK_MONOTONIC, &start);
		W = sparseLL(vertices);	//call the sparse function to intialize the 2D matrix randomly
	}
	
	weightLL(&W, vertices);
//	W = initialize_graph2(vertices);  // test case 2

	LinLisGra D(vertices);
	
	LinLisGra P(vertices);
	
	floyd( &W, &D, &P, vertices);
	clock_gettime(CLOCK_MONOTONIC, &end); //get the end time	
	floydPrinterLL(&W, &D, &P, vertices);
//
//
	printf("\nWeight: \n\n");
	// print the linked list representation of the graph
	W.printWeight();

	
	// time functions
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
	printf("elapsed time = %f seconds\n", (double) diff/1000000000);

	return 0;
}

