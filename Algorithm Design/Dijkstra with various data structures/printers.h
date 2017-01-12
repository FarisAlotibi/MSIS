#include <iostream>
//#include "matrixIntilization.h" // include the INF value --- it is already included in graphsFunctions
#include "graphsFunctions.h"	// to be then included into the main functions

//#include "graphsFunctions.h"
using namespace std;
//using namespace graphsFunctions;
//#define INF 999999999
namespace printer
{	
	/*---------------------------------------------2D functions ------------------------------------*/
   	void printMatrix(int** matrix, int vertices)
   	{
   		cout << "\t";
   		for (int i = 0; i < vertices; i++)
   			cout << "\t[" << i+1 << "]\t";

   		cout << endl;
   		for (int i = 0; i < vertices; i++)
   		{
   			cout << "[" << i+1 << "]\t";
   			for (int j = 0; j < vertices; j++)
   			{
   				if(matrix[i][j] == INF)
   					cout << "\t" << "INF" << "\t";
   				else
   					cout << "\t" << matrix[i][j] << "\t";
   			}

   			cout << endl;
   		}
   	}
   	
   	void pathway(int** p,int v,int u){ // print the path
		if(p[v][u]!=0){
			pathway(p,v,p[v][u]-1);
			printf("->%6.d", p[v][u]);
			pathway(p,p[v][u]-1,u);
		}
	}
   	
   	// Floyd print 2D
   	void floydPrinter(int** matrix, int** D, int** P, int vertices){
   		for(int i =0; i<vertices; i++)
   		{		

   			printf("\nSource %d\n", i+1);
   			printf("%5.sVertics %8.sDistence %6.sShortest Path \t\n","","","");
   			
   			for(int j=0; j<vertices; j++)
   			{
   				printf("%6.d->%1.d\t", i+1, j+1);


   				if(i == j){				
   					printf("%6.s0\t\t","");
   					printf("%6.d->%6.d\n", i+1, j+1);
   				}
   				else
   				{
   					printf(" %6.d\t\t",D[i][j]);   
   					printf("%6.d",i+1);
   					pathway(P,i,j);
   					printf("->%6.d\n", j+1);
   				}	
   			}
   		}
   	}   	
   	
   	
   	
	// print shortest path
	void printPath(int* touch, int j)
	{
		if (touch[j] == -1) return;
		printPath(touch, touch[j]);
		printf("->%6.d", j + 1);
	}
	
	// Dijkstra print  2D
	void printSolution(int* length, int* touch, int src, int vertices)
	{
   			printf("\nSource %d\n", src+1);
   			printf("%5.sVertics %8.sDistence %6.sShortest Path \t\n","","","");
			
			for(int j=0; j<vertices; j++)
			{
   				printf("%6.d->%1.d\t", src+1, j+1);
	
				// else if(src == j){
				// 	printf("\t %d \t",0);
				// 	//printf("\t 0 \t");
				// 	printf("\t%d\n",src+1);
				// }
				if(src == j){				
					printf("%6.s0\t\t","");
					printf("%6.d->%6.d\n", src+1, j+1);
				}
				else
				{
					printf(" %6.d\t\t",length[j]);   
					printf("%6.d",src+1);
					printPath(touch,j);
					printf("\n");
					// printf("->%3.d\n", j+1);
				}	
			}
	}
	
	
	/*---------------------------------------------1D functions ------------------------------------*/
	
	int get1DIndex(int v, int u) {
		if (v < u) {
			int temp = v;
			v = u;
			u = temp;
		}
		return ((v * (v-1)) / 2 + u) ;
	}	
	
		
	void pathway1D(int* p,int v,int u){ // print the path
		if(v != u && p[get1DIndex(v,u)]!=0){
			pathway1D(p,v,p[get1DIndex(v,u)]-1);
			printf("->%6.d",p[get1DIndex(v,u)]);
			pathway1D(p,p[get1DIndex(v,u)]-1,u);
		}
	}
   	
   	void printMatrix1D(int* matrix, int vertices)
	{
		cout << "\t";
		for (int i = 0; i < vertices; i++)
			cout << "\t[" << i << "]\t";
	
		cout << endl;
		for (int i = 0; i < vertices; i++)
		{
			cout << "[" << i << "]\t";
			for (int j = 0; j < vertices; j++)
			{
				int k = get1DIndex(i, j);
				if(i == j)
					cout << "\t" << 0 << "\t";
				else if(matrix[k] == INF)
					cout << "\t" << "INF" << "\t";
				else
					cout << "\t" << matrix[k] << "\t";
			}
			
			cout << endl;
		}
	}
	
	
   	// Floyd print 1D
   	void floydPrinter1D(int* matrix, int* D, int* P, int vertices)
	{
   		for(int i =0; i<vertices; i++)
   		{		
   			printf("\nSource %d\n", i+1);
   			printf("%5.sVertics %8.sDistence %6.sShortest Path \t\n","","","");
   			
   			for(int j=0; j<vertices; j++)
   			{
   				printf("%6.d->%1.d\t", i+1, j+1);


   				if(i == j){				
   					printf("%6.s0\t\t","");
   					printf("%6.d->%6.d\n", i+1, j+1);
   				}
   				else
   				{
   					printf(" %6.d\t\t",D[get1DIndex(i,j)]);   
   					printf("%6.d",i+1);
   					pathway1D(P,i,j);
	 				//printf("\n");
   					printf("->%6.d\n", j+1);
   				}	
   			}
   		}
   	}
	   
	/*---------------------------------------------LinkedList functions ------------------------------------*/
	   
	   
	void pathwayLL(LinLisGra* p,int v,int u){ // print the path
		int x = p->getAttribute(v,u);
		if(x!=0){
			pathwayLL(p,v,x-1);
			printf("->%6.d", x);
			pathwayLL(p,x-1,u);
		}
	}   	
	
	
	void floydPrinterLL(LinLisGra* W, LinLisGra* D, LinLisGra* P, int vertices){
   		for(int i =0; i<vertices; i++)
   		{		

   			printf("\nSource %d\n", i+1);
   			printf("%5.sVertics %8.sDistence %6.sShortest Path \t\n","","","");
   			
   			for(int j=0; j<vertices; j++)
   			{
   				printf("%6.d->%1.d\t", i+1, j+1);
   				int y = D->getAttribute(i,j);


   				if(i == j){				
   					printf("%6.s0\t\t","");
   					printf("%6.d->%6.d\n", i+1, j+1);
   				}
   				else
   				{
   					printf(" %6.d\t\t",y);   
   					printf("%6.d",i+1);
   					pathwayLL(P,i,j);
 					//printf("\n");
   					printf("->%6.d\n", j+1);
   				}	
   			}
   		}
   	}   	
}

