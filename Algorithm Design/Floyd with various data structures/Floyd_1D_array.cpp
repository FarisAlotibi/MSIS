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

void floyd(int* W, int* D, int* P, int n)
{
	int matrix_len = ((n*n)-n)/2;

	int i, j, k;

	for (i = 0; i < matrix_len; i++)
	{
		P[i] = 0;
		D[i] = 0;
	}

//	for (i = 0; i < matrix_len; i++)
//		D[i] = W[i];
//
//	for (k = 0; k < n; k++)
//		for (i = 0; i < n; i++)
//			for (j = 0; j < n; j++)
//				if(i != j && i != k && j != k)
//				{
//					if (D[get1DIndexG(i, k)] + D[get1DIndexG(k, j)] < D[get1DIndexG(i, j)])
//					{
//						P[get1DIndexG(i, j)] = k+1;
//						D[get1DIndexG(i, j)] = D[get1DIndexG(i, k)] + D[get1DIndexG(k, j)];
//					}
//				}


	int temp1;
	int temp2;
	int temp3;
	for (i = 0; i < matrix_len; i++)
		D[i] = W[i];

	for (k = 0; k < n; k++)
		for (i = 0; i < n; i++)
		{
			temp2 = get1DIndexG(i, k);
			if(D[temp2]!=INF)
				for (j = 0; j < i; j++)
					if(i != j && i != k && j != k)
					{	temp1 = get1DIndexG(i, j);

						temp3 =	get1DIndexG(k, j);
						if (D[temp2] + D[temp3] < D[temp1])
						{
							P[temp1] = k+1;
							D[temp1] = D[temp2] + D[temp3];
						}
					}
		}

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

	int matrix_len = ((vertices*vertices)-vertices)/2;
	int* P = new int[matrix_len];
	int* D = new int[matrix_len];

	floyd(W, D, P, vertices);
	clock_gettime(CLOCK_MONOTONIC, &end); 		// get the end time
	floydPrinter1D(W, D, P, vertices); // printer
//		
	printf("Weight Matrix: \n");
	printMatrix1D(W, vertices);
	

		
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
//	diff = diff /1000000000;  // seconds -- miliseconds 1000000 -- microseconds 1000 -- nanoseconds nothing
	printf("elapsed time = %lf seconds\n", (double) diff/1000000000);	
	return 0;
}


