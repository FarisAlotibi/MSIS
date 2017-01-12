#include <stdio.h>		/* printf, scanf, puts, NULL */
#include <stdlib.h>		/* srand, rand */
#include <time.h>		/* time */
#include <iostream>
#include <string>
#include "printers.h"
//#include "graphsFunctions.h"
//#include "matrixIntilization.h"  no need cause already included in printers.h header 
using namespace std;
using namespace printer;
using namespace Intilization;
using namespace graphsFunctions;
#define BILLION 1000000000L

// A  function to find the vertex with minimum distance value, from
// the set of nodes not yet included in shortest path tree
int minDistance(int* length, bool* F, int n)
{
	int minimum = INF;
	int vnear;

	for (int i = 0; i < n; i++)
		if (F[i] == false && length[i] <= minimum){
			minimum = length[i];
			vnear = i;
		}

		return vnear;
}

void dijkstra(int* W, int src, int n)
{
	int vnear, v = n - 1;
	int* length = new int[n];	// length[i] will hold the shortest distance from src to i

	bool* F = new bool[n]; 		// F[i] will true if vertex i is included in shortest
                     			// path tree or shortest distance from src to i is finalized
	int* touch = new int[n];				// keep track path

	// Initializations
	for (int i = 0; i < n; i++)
	{
		touch[i] = -1;
		length[i] = INF; 		// Unknown distance function from source to v
		F[i] = false;			// Previous node in optimal path from source
	}

	length[src] = 0; // Distance from source to another

	// Find shortest path for all nodes
	while(v >= 0)
	{
		// Pick the least distance node from the set of vertices not
		// yet processed. vnear is always equal to src in first loop
		vnear = minDistance(length, F, n);

		// Mark the picked vertex as processed
		F[vnear] = true;

		// Update length value of the adjacent vertices of the picked vertex.
		for (int i = 0; i < n; i++)
			// Update length[i] only if it is not in F, there is an edge from 
			// vnear to i, and total weight of path from src to  i through vnear is 
			// less than current value of length[i]
			if (!F[i] && W[get1DIndex(vnear, i)] && 
				length[vnear] != INF && 
				length[vnear] + W[get1DIndex(vnear, i)] < length[i])
			{
				length[i] = length[vnear] + W[get1DIndex(vnear, i)];
				touch[i] = vnear;
			}
		v--;
	}

		// print the constructed distance array
		printSolution(length, touch, src, n);
}

int main()
{
	srand(time(NULL)); /* initialize random seed: */
	int vertices, decision;
	int* W;
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
		W = complete1D(vertices);	//call the complete function to intialize the 1D array randomly
	}
	else{
		clock_gettime(CLOCK_MONOTONIC, &start);
		W = sparse1D(vertices);	//call the sparse function to intialize the 2D matrix randomly
	}
	weight1D(W, vertices);
//	initialize_matrix1D1(W);  // for test case 1
//	initialize_matrix1D2(W);   // for test case 2

//	dijkstra(W, 0, vertices);
	for(int i = 0; i < vertices; i++)
	{
	 	dijkstra(W, i, vertices);
	}
	clock_gettime(CLOCK_MONOTONIC, &end); //get the end time
	
	printf("Weight Matrix: \n");
	printMatrix1D(W, vertices);
	printf("\n");	
	
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
	printf("elapsed time = %f seconds\n", (double) diff/1000000000); 
	puts("");
	return 0;
}


