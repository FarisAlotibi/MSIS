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
//const int INF1 = 999999999;


void floyd(int** W, int** D, int** P, int n)
{
	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			P[i][j] = 0;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			D[i][j] = W[i][j];

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
			if(D[k][i]!=INF)											// optimization for sparse graphs
				for (j = 0; j < i; j++)
					if (D[i][k] + D[k][j] < D[i][j])
					{	
						/*P[i][j] = k+1; 
						D[i][j] = D[i][k] + D[k][j]; j to n old one */
						
						P[i][j] = k+1; 									// optimizing the algorithm
						P[j][i] = k+1; 
						D[i][j] = D[i][k] + D[k][j];
						D[j][i] = D[i][k] + D[k][j];
					}
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
	
	int** P = new int*[vertices];
	int** D = new int*[vertices];
	for (int i = 0; i < vertices; i++) 	// initilizing the empty matrices to be used 
	{
		P[i] = new int[vertices];
		D[i] = new int[vertices];
	}
	
	floyd(W, D, P, vertices);
	clock_gettime(CLOCK_MONOTONIC, &end); //get the end time
	floydPrinter(W, D, P, vertices);
//
//	//printers printer;		// creating an object for a class
	printf("Weight Matrix: \n");
	printMatrix(W, vertices);

	
	// time functions
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
	printf("elapsed time = %f seconds\n", (float) diff/1000000000);
	return 0;
}
