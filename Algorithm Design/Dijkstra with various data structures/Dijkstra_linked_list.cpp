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


//// A utility function to find the vertex with minimum distance value, from
//// the set of vertices not yet included in shortest path tree
//int minDistance(int* length, bool* F, int n)
//{
//	int min = INF;
//	int vnear;
//
//	for (int i = 0; i < n; i++)
//		if (F[i] == false && length[i] <= min){
//			min = length[i];
//			vnear = i;
//		}
//
//		return vnear;
//}
//
//
//
//void dijkstra(LinLisGra* W, int src, int n)
//{
//	int vnear, v = n - 1;
//	int* length = new int[n];	// length[i] will hold the shortest distance from src to i
//
//	bool* F = new bool[n]; 		// F[i] will true if vertex i is included in shortest
//                     			// path tree or shortest distance from src to i is finalized
//	int* touch = new int[n];				// keep track path
//
//	// Initializations
//	for (int i = 0; i < n; i++)
//	{
//		touch[i] = -1;
//		length[i] = INF; 		// Unknown distance function from source to v
//		F[i] = false;			// Previous node in optimal path from source
//	}
//
//	length[src] = 0; // Distance from source to source
//
//	// Find shortest path for all vertices
//	while(v >= 0)
//	{
//		// Pick the minimum distance vertex from the set of vertices not
//		// yet processed. vnear is always equal to src in first iteration.
//		vnear = minDistance(length, F, n);
//
//		// Mark the picked vertex as processed
//		F[vnear] = true;
//
//		// Update length value of the adjacent vertices of the picked vertex.
//		for (int i = 0; i < n; i++)
//		{
//			int crrW = W->getAttribute(vnear, i);
//			// Update length[i] only if it is not in F, there is an Link from 
//			// vnear to i, and total weight of path from src to  i through vnear is 
//			// smaller than current value of length[i]
//			if (!F[i] && crrW && 
//				length[vnear] != INF && 
//				length[vnear] + crrW < length[i])
//			{
//				length[i] = length[vnear] + crrW;
//				touch[i] = vnear;
//			}
//		}
//		v--;
//	}
//
//		// print the constructed distance array
//		printSolution(length, touch, src, n);
//}



// Structure to represent a min heap node
struct MinHeapNode
{
        int  v;
        int to;
};

// Structure to represent a min heap
struct MinHeap
{
    int size;      // Number of heap nodes present currently
    int capacity;  // Capacity of min heap
    int *pos;     // This is needed for decreaseKey()
    struct MinHeapNode **array;
};

// A utility function to create a new Min Heap Node
struct MinHeapNode* newMinHeapNode(int v, int dist)
{
        struct MinHeapNode* minHeapNode = (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
        minHeapNode->v = v;
        minHeapNode->to = dist;
        return minHeapNode;
}

// A utility function to create a Min Heap
struct MinHeap* createMinHeap(int capacity)
{
        struct MinHeap* minHeap = (struct MinHeap*) malloc(sizeof(struct MinHeap));
        minHeap->pos = (int *)malloc(capacity * sizeof(int));
        minHeap->size = 0;
        minHeap->capacity = capacity;
        minHeap->array = (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
        return minHeap;
}

// A utility function to swap two nodes of min heap. Needed for min heapify
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b)
{
        struct MinHeapNode* t = *a;
        *a = *b;
        *b = t;
}

// A standard function to heapify at given idx
// This function also updates position of nodes when they are swapped.
// Position is needed for decreaseKey()
void minHeapify(struct MinHeap* minHeap, int idx)
{
        int smallest, left, right;
        smallest = idx;
        left = 2 * idx + 1;
        right = 2 * idx + 2;

        if (left < minHeap->size && minHeap->array[left]->to < minHeap->array[smallest]->to)
                smallest = left;

        if (right < minHeap->size && minHeap->array[right]->to < minHeap->array[smallest]->to )
                smallest = right;

        if (smallest != idx)
        {
        // The nodes to be swapped in min heap
                MinHeapNode *smallestNode = minHeap->array[smallest];
                MinHeapNode *idxNode = minHeap->array[idx];

        // Swap positions
                minHeap->pos[smallestNode->v] = idx;
                minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
                swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

                minHeapify(minHeap, smallest);
        }
}

// A utility function to check if the given minHeap is ampty or not
int isEmpty(struct MinHeap* minHeap)
{
        return minHeap->size == 0;
}

// Standard function to extract minimum node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)
{
        if (isEmpty(minHeap))
                return NULL;

    // Store the root node
        struct MinHeapNode* root = minHeap->array[0];

    // Replace root node with last node
        struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
        minHeap->array[0] = lastNode;

    // Update position of last node
        minHeap->pos[root->v] = minHeap->size-1;
        minHeap->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
        --minHeap->size;
        minHeapify(minHeap, 0);

        return root;
}

// Function to decreasy dist value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(struct MinHeap* minHeap, int v, int dist)
{
    // Get the index of v in  heap array
        int i = minHeap->pos[v];

    // Get the node and update its dist value
        minHeap->array[i]->to = dist;

    // Travel up while the complete tree is not hepified.
    // This is a O(Logn) loop
        while (i && minHeap->array[i]->to < minHeap->array[(i - 1) / 2]->to)
        {
        // Swap this node with its parent
                minHeap->pos[minHeap->array[i]->v] = (i-1)/2;
                minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
                swapMinHeapNode(&minHeap->array[i],  &minHeap->array[(i - 1) / 2]);

        // move to parent index
                i = (i - 1) / 2;
        }
}

// A utility function to check if a given vertex
// 'v' is in min heap or not
bool isInMinHeap(struct MinHeap *minHeap, int v)
{
        if (minHeap->pos[v] < minHeap->size)
                return true;
        return false;
}

// The main function that calulates distances of shortest paths from src to all
// vertices. It is a O(ELogV) function
void dijkstra(LinLisGra* graph, int src, int vertices)
{
    int vnear, n = vertices;            // Get the number of vertices in graph
    int length[n];                              // length values used to pick minimum weight edge in cut
    int* touch = new int[n];            // keep track path

    // minHeap represents set E
    struct MinHeap* minHeap = createMinHeap(n);

    // Initializations
    for (int v = 0; v < n; ++v)
    {
        touch[v] = -1;
        length[v] = INF;                // Unknown distance function from source to v
        minHeap->array[v] = newMinHeapNode(v, length[v]);
        minHeap->pos[v] = v;
    }

    // Make length value of src vertex as 0 so that it is extracted first
    length[src] = 0;
    decreaseKey(minHeap, src, length[src]);

    // Initially size of min heap is equal to n
    minHeap->size = n;

    // In the following loop, min heap contains all nodes
    // whose shortest distance is not yet finalized.
    while (!isEmpty(minHeap))
    {
        // Extract the vertex with minimum distance value
        struct MinHeapNode* minHeapNode = extractMin(minHeap);
        vnear = minHeapNode->v; // Store the extracted vertex number

        // Traverse through all adjacent vertices of vnear (the extracted
        // vertex) and update their distance values
        for(struct Link* e = graph->getLastLinks()[vnear].head; e != NULL; e = e->nextLink)
        {
                int v = e->to;

            // If shortest distance to v is not finalized yet, and distance to v
            // through vnear is less than its previously calculated distance
                if (isInMinHeap(minHeap, v) && length[vnear] != INF &&
                        e->attribute + length[vnear] < length[v])
                {
                        length[v] = length[vnear] + e->attribute;

                        decreaseKey(minHeap, v, length[v]); // update distance value in min heap
                        touch[v] = vnear;
                }
        }
    }

    // print the calculated shortest distances
    printSolution(length, touch, src, n);
}


int main()
{
	srand(time(NULL)); /* initialize random seed: */

	int vertices, decision;
	LinLisGra W;
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
		W = completeLL(vertices);	//call the complete function to intialize the 2D matrix randomly
	}
	else{
		clock_gettime(CLOCK_MONOTONIC, &start);
		W = sparseLL(vertices);	//call the sparse function to intialize the 2D matrix randomly
	}
//	clock_gettime(CLOCK_MONOTONIC, &start);
//	LinLisGra W = sparseLL(vertices);	
	weightLL(&W, vertices);				//call the weight function to assign wieghts randomly into the 2D matrix
//	W = initialize_graph2(vertices);   // test case 2
	
//	dijkstra(&W, 0, vertices); // 0 is the first node
	for(int i = 0; i < vertices; i++)
	{
	 	dijkstra(&W, i, vertices);
	}
	clock_gettime(CLOCK_MONOTONIC, &end); //get the end time
	
	printf("Weight: \n");
	// print the linked list representation of the graph
	W.printWeight();

	printf("\n");

	
	// time functions
	diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
	printf("\nelapsed time = %f seconds\n", (double) diff/1000000000);

	return 0;
}


