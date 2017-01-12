#include <iostream>
#include <stdlib.h>		/* srand, rand */
#include "matrixIntilization.h"
//#include "LinLisGra.h"	/* utility lib. for representing the graph as linked list */
#define INF 999999999
using namespace std;
namespace graphsFunctions
{	
	/*
 	* generate random number between 1 and vertices
	*/
	int random(int vertices)
	{
		return rand() % vertices + 1;
	}
	
	
	/*---------------------------------------------2D functions ------------------------------------*/
	
	//Floyd 2D -- Dijkstra 2D
	
	int** complete(int vertices)
	{
		int **adj_matrix;
		adj_matrix = new int*[vertices];
	
		for (int i = 0; i < vertices; i++)
		{
			adj_matrix[i] = new int[vertices];
			for (int j = 0; j < vertices; j++)
			{
	            // fill in some initial values
	            // (filling diagnal elements in zeros)
	            if(i == j)
	            	adj_matrix[i][j] = 0;
	            else
					adj_matrix[i][j] = 1;
			}
		}
	
		return adj_matrix;
	}
	
	int** sparse(int vertices)
	{
		int **adj_matrix;
		adj_matrix = new int*[vertices];
	
		for (int i = 0; i < vertices; i++)
		{
			adj_matrix[i] = new int[vertices];
			for (int j = 0; j < vertices; j++)
	            adj_matrix[i][j] = 0;
		}
		// number of edges must be vertices - 1
		for(int i = 1; i < vertices; i++)
		{
			int j;
			do
			{
				j = random(i) - 1;
				if(j != i)
				{
					adj_matrix[i][j] = 1;
					adj_matrix[j][i] = 1;
				}
	
			} while(i == j);
		}
	
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
			{
				// fill in some initial values
				// (filling diagnal elements in zeros)
				if(i != j && adj_matrix[i][j] == 0)
					adj_matrix[i][j] = INF;
			}
	
		return adj_matrix;
	}

	void weight(int** adj_matrix, int vertices)
	{
		for (int i = 0; i < vertices; i++)
			for(int j = i+1; j < vertices; j++)
				if(adj_matrix[i][j] == 1)
				{
					adj_matrix[i][j] = random(vertices);
					adj_matrix[j][i] = adj_matrix[i][j];
				}
	}
	
	
	/*---------------------------------------------1D functions ------------------------------------*/
	
	// floyd 1D -- Dijkstra 1D
	
	int get1DIndexG(int v, int u) {   // to get the equavelint coordinates for one dimesional array
		if (v < u) {
			int temp = v;
			v = u;
			u = temp;
		}
		return ((v * (v-1)) / 2 + u) ;
	}
	
	int* complete1D(int vertices)
	{
		int matrix_len = ((vertices*vertices)-vertices)/2;
		int* adj_matrix = new int[matrix_len];
	
		for (int i = 0; i < matrix_len; i++)
			adj_matrix[i] = 1;
	
		return adj_matrix;
	}
	
	int* sparse1D(int vertices)
	{
		int matrix_len = ((vertices*vertices)-vertices)/2;
		int *adj_matrix = new int[matrix_len];
	
		for (int i = 0; i < matrix_len; i++)
			adj_matrix[i] = 0;
	
		// number of edges must be vertices - 1
		for(int i = 1; i < vertices; i++)
		{
			int j;
			do
			{
				j = random(i) - 1;
				if(j != i)
				{
					adj_matrix[get1DIndexG(i, j)] = 1;
					adj_matrix[get1DIndexG(i, j)] = 1;
				}
	
			} while(i == j);
		}
	
		for (int i = 0; i < vertices; i++)
			for (int j = 0; j < vertices; j++)
			{
		// fill in some initial values
		// (filling diagnal elements in zeros)
				if(i != j && adj_matrix[get1DIndexG(i, j)] == 0)
					adj_matrix[get1DIndexG(i, j)] = INF;
			}
	
		return adj_matrix;
	}
	
	void weight1D(int* adj_matrix, int vertices)
	{
		int matrix_len = ((vertices*vertices)-vertices)/2;
		for (int i = 0; i < matrix_len; i++)
			if(adj_matrix[i] == 1)
				adj_matrix[i] = random(vertices);
	}
	
	
	/*---------------------------------------------LinkedList functions ------------------------------------*/
	
		
	LinLisGra completeLL(int vertices)
	{
		
		LinLisGra graph(vertices);
	
		for (int i = vertices-1; i >= 0; i--)
			for (int j = vertices-1; j > i; j--)
				graph.addUndirectedLink(i, j);
	
		return graph;
	}
	
	LinLisGra sparseLL(int vertices)
	{
		LinLisGra graph(vertices);
		for(int i = 1; i < vertices; i++)
		{
			int j;
			do
			{
				j = random(i) - 1;
				if(j != i)
				{
					graph.addUndirectedLink(i,j,1);
	
				}
	
			} while(i == j);
		}
	
	
		return graph;
	}
	
	void weightLL(LinLisGra* graph, int vertices)
	{
		for (int i = 0; i < vertices; ++i)
			for (int j = 0; j < vertices; ++j){
				if(graph->getAttribute(i,j) == 1)
						graph->setAttribute(i, j, random(vertices)); // set weight
			}
	}
}
