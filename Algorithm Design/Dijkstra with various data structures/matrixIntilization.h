#include <iostream>
#include "LinLisGra.h"	/* utility lib. for representing the graph as linked list */
#define INF 999999999
using namespace std;
namespace Intilization
{	



	/*---------------------------------------------2D functions ------------------------------------*/
	
	
   	void initialize_matrix1(int** matrix2D)
 	{
 		matrix2D[0][0] = 0, 	matrix2D[0][1] = 7, 	matrix2D[0][2] = INF,	matrix2D[0][3] = 18,	matrix2D[0][4] = 15;
 		matrix2D[1][0] = 7, 	matrix2D[1][1] = 0, 	matrix2D[1][2] = 11, 	matrix2D[1][3] = 7,		matrix2D[1][4] = 5;
 		matrix2D[2][0] = INF,	matrix2D[2][1] = 11, 	matrix2D[2][2] = 0, 	matrix2D[2][3] = 29, 	matrix2D[2][4] = INF;
 		matrix2D[3][0] = 18,	matrix2D[3][1] = 7,		matrix2D[3][2] = 29, 	matrix2D[3][3] = 0, 	matrix2D[3][4] = 18;
 		matrix2D[4][0] = 15,	matrix2D[4][1] = 5,		matrix2D[4][2] = INF,	matrix2D[4][3] = 18,	matrix2D[4][4] = 0;	
 	}

	void initialize_matrix2(int** matrix2D)
	{
		matrix2D[0][0] = 0, 	matrix2D[0][1] = INF, 	matrix2D[0][2] = INF,		matrix2D[0][3] = INF,		matrix2D[0][4] = INF,    matrix2D[0][5] = INF,  	matrix2D[0][6] = INF, 	matrix2D[0][7] = INF,	matrix2D[0][8] = INF,	matrix2D[0][9] = 8, 	matrix2D[0][10] = INF,	matrix2D[0][11] = INF;                             
		matrix2D[1][0] = INF, 	matrix2D[1][1] = 0, 	matrix2D[1][2] = 17,		matrix2D[1][3] = 13,		matrix2D[1][4] = INF,    matrix2D[1][5] = INF,  	matrix2D[1][6] = INF, 	matrix2D[1][7] = 17,	matrix2D[1][8] = 12,	matrix2D[1][9] = INF, 	matrix2D[1][10] = INF,	matrix2D[1][11] = INF;
		matrix2D[2][0] = INF, 	matrix2D[2][1] = 17, 	matrix2D[2][2] = 0,			matrix2D[2][3] = INF,		matrix2D[2][4] = INF,    matrix2D[2][5] = INF, 		matrix2D[2][6] =INF , 	matrix2D[2][7] = INF,	matrix2D[2][8] = INF,	matrix2D[2][9] = 7, 	matrix2D[2][10] = INF,	matrix2D[2][11] = 9;
		matrix2D[3][0] = INF, 	matrix2D[3][1] = 13, 	matrix2D[3][2] = INF,		matrix2D[3][3] = 0,			matrix2D[3][4] = INF,    matrix2D[3][5] = INF, 		matrix2D[3][6] = 15, 	matrix2D[3][7] = INF,	matrix2D[3][8] = INF,	matrix2D[3][9] = 13, 	matrix2D[3][10] = 5,	matrix2D[3][11] = 13;
		matrix2D[4][0] = INF, 	matrix2D[4][1] = INF, 	matrix2D[4][2] = INF,		matrix2D[4][3] = INF,		matrix2D[4][4] = 0,      matrix2D[4][5] = 18, 		matrix2D[4][6] = INF, 	matrix2D[4][7] = INF,	matrix2D[4][8] = 5,		matrix2D[4][9] = INF, 	matrix2D[4][10] = INF,	matrix2D[4][11] = INF;
		matrix2D[5][0] = INF, 	matrix2D[5][1] = INF, 	matrix2D[5][2] = INF,		matrix2D[5][3] = INF,		matrix2D[5][4] = 18,     matrix2D[5][5] = 0, 		matrix2D[5][6] = INF, 	matrix2D[5][7] = 17,	matrix2D[5][8] = INF,	matrix2D[5][9] = INF, 	matrix2D[5][10] = INF,	matrix2D[5][11] = INF;
		matrix2D[6][0] = INF, 	matrix2D[6][1] = INF, 	matrix2D[6][2] = INF,		matrix2D[6][3] = 15,		matrix2D[6][4] = INF,    matrix2D[6][5] = INF, 		matrix2D[6][6] = 0, 	matrix2D[6][7] = 17,	matrix2D[6][8] = INF,	matrix2D[6][9] = INF, 	matrix2D[6][10] = 8,	matrix2D[6][11] = 11;
		matrix2D[7][0] = INF, 	matrix2D[7][1] = 17, 	matrix2D[7][2] = INF,		matrix2D[7][3] = INF,		matrix2D[7][4] = INF,	 matrix2D[7][5] = 17, 		matrix2D[7][6] = 17, 	matrix2D[7][7] = 0,		matrix2D[7][8] = INF,	matrix2D[7][9] = INF, 	matrix2D[7][10] = INF,	matrix2D[7][11] = INF;
		matrix2D[8][0] = INF, 	matrix2D[8][1] = 12, 	matrix2D[8][2] = INF,		matrix2D[8][3] = INF,		matrix2D[8][4] = 5,	  	 matrix2D[8][5] = INF, 		matrix2D[8][6] = INF, 	matrix2D[8][7] = INF,	matrix2D[8][8] = 0,		matrix2D[8][9] = INF, 	matrix2D[8][10] = 15,	matrix2D[8][11] = INF;
		matrix2D[9][0] = 8, 	matrix2D[9][1] = INF,	matrix2D[9][2] = 7,			matrix2D[9][3] = 13,		matrix2D[9][4] = INF,    matrix2D[9][5] = INF,	 	matrix2D[9][6] = INF, 	matrix2D[9][7] = INF,	matrix2D[9][8] = INF,	matrix2D[9][9] = 0, 	matrix2D[9][10] = INF,	matrix2D[9][11] = 14;
		matrix2D[10][0] = INF, 	matrix2D[10][1] = INF, 	matrix2D[10][2] = INF,		matrix2D[10][3] = 5,		matrix2D[10][4] = INF,   matrix2D[10][5] = INF, 	matrix2D[10][6] = 8, 	matrix2D[10][7] = INF,	matrix2D[10][8] = 15,	matrix2D[10][9] = INF,	matrix2D[10][10] = 0,	matrix2D[10][11] = INF;
		matrix2D[11][0] = INF, 	matrix2D[11][1] = INF, 	matrix2D[11][2] = 9,		matrix2D[11][3] = 13,		matrix2D[11][4] = INF,   matrix2D[11][5] = INF, 	matrix2D[11][6] = 11, 	matrix2D[11][7] = INF,	matrix2D[11][8] = INF,	matrix2D[11][9] = 14, 	matrix2D[11][10] = INF,	matrix2D[11][11] = 0;
	}
	
	
	/*---------------------------------------------1D functions ------------------------------------*/
	
	void initialize_matrix1D1(int* matrix1D)
	{
	 	matrix1D[0] = 7, 	matrix1D[1] = INF,	matrix1D[3] = 18,		matrix1D[6] = 15;
	 						matrix1D[2] = 11,	matrix1D[4] = 7,		matrix1D[7] = 5;
	 											matrix1D[5] = 29,	 	matrix1D[8] = INF;
	 																	matrix1D[9] = 18;	
	}
	
	void initialize_matrix1D2(int* matrix1D)
	{
		matrix1D[0] = INF;
		matrix1D[1] = INF; 	matrix1D[2] = 17; 
		matrix1D[3] = INF; 	matrix1D[4] = 13; 	matrix1D[5] = INF;
		matrix1D[6] = INF; 	matrix1D[7] = INF;	matrix1D[8] = INF; 	matrix1D[9] = INF;
		matrix1D[10] = INF; matrix1D[11] = INF; matrix1D[12] = INF; matrix1D[13] = INF; matrix1D[14] = 18;
		matrix1D[15] = INF; matrix1D[16] = INF; matrix1D[17] = INF; matrix1D[18] = 15; 	matrix1D[19] = INF; matrix1D[20] = INF;
		matrix1D[21] = INF; matrix1D[22] = 17; 	matrix1D[23] = INF; matrix1D[24] = INF; matrix1D[25] = INF; matrix1D[26] = 17; 	matrix1D[27] = 17;
		matrix1D[28] = INF; matrix1D[29] = 12; 	matrix1D[30] = INF; matrix1D[31] = INF; matrix1D[32] = 5; 	matrix1D[33] = INF; matrix1D[34] = INF; matrix1D[35] = INF;
		matrix1D[36] = 8; 	matrix1D[37] = INF; matrix1D[38] = 7; 	matrix1D[39] = 13; 	matrix1D[40] = INF; matrix1D[41] = INF; matrix1D[42] = INF; matrix1D[43] = INF; matrix1D[44] = INF;
		matrix1D[45] = INF; matrix1D[46] = INF; matrix1D[47] = INF; matrix1D[48] = 5; 	matrix1D[49] = INF; matrix1D[50] = INF; matrix1D[51] = 8; 	matrix1D[52] = INF; matrix1D[53] = 15; 	matrix1D[54] = INF;
		matrix1D[55] = INF; matrix1D[56] = INF; matrix1D[57] = 9; 	matrix1D[58] = 13; 	matrix1D[59] = INF; matrix1D[60] = INF; matrix1D[61] = 11; 	matrix1D[62] = INF; matrix1D[63] = INF; matrix1D[64] = 14; matrix1D[65] = INF;
	}
	
	
	/*---------------------------------------------1D functions ------------------------------------*/
	
	LinLisGra initialize_graph1(int n)
	{
		LinLisGra graph(n);	
	
		graph.addUndirectedLink(0, 1, 7);		graph.addUndirectedLink(0, 3, 18);		graph.addUndirectedLink(0, 4, 15);
	
									graph.addUndirectedLink(1, 2, 11);		graph.addUndirectedLink(1, 3, 7);		
	
																	graph.addUndirectedLink(2, 3, 29);	
	
																									graph.addUndirectedLink(3, 4, 18);
	
	
		return graph;	
	}
	LinLisGra initialize_graph2(int n)
	{
		LinLisGra graph(n);
	
		graph.addUndirectedLink(0, 9,  8);		graph.addUndirectedLink(1, 2,  17);
	
		graph.addUndirectedLink(1, 3,  13);	graph.addUndirectedLink(1, 7,  17);
	
		graph.addUndirectedLink(1, 8,  12);	graph.addUndirectedLink(2, 9,  7);
	
		graph.addUndirectedLink(2, 11, 9);		graph.addUndirectedLink(3, 6,  15);
	
		graph.addUndirectedLink(3, 9,  13);	graph.addUndirectedLink(3, 10, 5);
	
		graph.addUndirectedLink(3, 11, 13);	graph.addUndirectedLink(4, 5,  18);
	
		graph.addUndirectedLink(4, 8,  5);		graph.addUndirectedLink(5, 7,  17);
	
		graph.addUndirectedLink(6, 7,  17);	graph.addUndirectedLink(6, 10, 8);
	
		graph.addUndirectedLink(6, 11, 11);	graph.addUndirectedLink(8, 10, 15);	graph.addUndirectedLink(9, 11, 14);
		
		return graph;
	}
}
