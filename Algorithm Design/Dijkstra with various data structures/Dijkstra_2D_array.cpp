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


// A utility function to find the vertex with minimum distance value, from
// the set of vertices not yet included in shortest path tree
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

void dijkstra(int** W, int src, int n)
{
	int vnear, v = n - 1;
	int* length = new int[n];	// length will keep the shortest distance from source to i

	bool* F = new bool[n]; 		// F will be true if vertex i is added into shortest path tree or shortest distance from source to i is finalized
	int* touch = new int[n];				// keep track of the path

	// Initializations process
	for (int i = 0; i < n; i++)
	{
		touch[i] = -1;
		length[i] = INF; 		// Unknown distance from source to v
		F[i] = false;			// From source, previous node is in optimal path
	}

	length[src] = 0; 			// Distance from the same node

	
	while(v >= 0)  	// Find shortest path for all vertices
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. vnear is always equal to src in first iteration.
		vnear = minDistance(length, F, n);

		// Mark the picked vertex as processed
		F[vnear] = true;

		// Update length value of the adjacent vertices of the picked vertex.
		for (int i = 0; i < n; i++)
			// Update length[i] only if it is not in F, there is an edge from 
			// vnear to i, and total weight of path from src to  i through vnear is 
			// smaller than current value of length[i]
			if (!F[i] && W[vnear][i] && 
				length[vnear] != INF && 
				length[vnear] + W[vnear][i] < length[i])
			{
				length[i] = length[vnear] + W[vnear][i];
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
	int** W;
	// int n = 12;
	printf("Enter the number of vertices: \n");
	//cin >> vertices;
	scanf("%d", &vertices);				// read the number entered by the user
	// printf("%d\n", random(n));
	struct timespec start, end;
	double diff;
	printf("Enter which function you want to  be executed (1) for complete or (any key) for sparse: \n");
	scanf("%d", &decision);
	if(1 == decision)
	{
		clock_gettime(CLOCK_MONOTONIC, &start);
		W = complete(vertices);	//call the complete function to intialize the 2D matrix randomly
	}
	else{
		clock_gettime(CLOCK_MONOTONIC, &start);
		W = sparse(vertices);	//call the sparse function to intialize the 2D matrix randomly
	}
//	clock_gettime(CLOCK_MONOTONIC, &start);
//	W = sparse(vertices);	
	weight(W, vertices);				//call the weight function to assign wieghts randomly into the 2D matrix
	
//	initialize_matrix1(W); // for test case 1
//	initialize_matrix2(W); // for test case 2
	
//	dijkstra(W, 0, vertices);
	for(int i = 0; i < vertices; i++)
	{
		dijkstra(W, i, vertices);
	}
	clock_gettime(CLOCK_MONOTONIC, &end); // get the end time
	
	printf("Weight Matrix: \n");
	printMatrix(W, vertices);
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
	diff = diff /1000000000;
	printf("elapsed time = %f seconds\n", (double) diff);
	
//	puts("");

	return 0;
}


