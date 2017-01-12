/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package n.queen.backtracking;

/**
 *
 * @author FRISCA
 */
public class NQueenBacktracking {
//    int count = 0;
//    int [][]x;
    int n;
    int[] x;  // 2 dimensional

    public NQueenBacktracking(int N) {
        x = new int[N];
//        x = new int[N][N];// 2 dimensional
        n = N;
    }

    public boolean canPlaceQueen(int r, int c) { // promissng
        /**
         * Returns TRUE if a queen can be placed in row r and column c.
         * Otherwise it returns FALSE. x[] is a global array whose first (r-1)
         * values have been set.
         */
        for (int i = 0; i < r; i++) { // k in promising
//                System.out.println("i "+ i);
            if (x[i] == c || (i - r) == (x[i] - c) ||(i - r) == (c - x[i])) 
            {
//                System.out.println("i+ "+ i);
                return false;
            }
        }
        return true;
    }
    
//    public boolean canPlaceQueen(int i, int j, int z) // z is the depth .. j is the column .. i is the row
//    {   
//        for (int k = 0; k < n; k++){            // k is the row representing the (depth) in this 2 dimensional array
//            for (int xx = 0; xx<n; xx++){       // xx is column representing the (rows) in this 2D
////                  if(xx - i == z - k || xx - i == k -z || x[k][xx] - j ==  z - k || x[k][xx] - j ==  k - z )  // the value represents the columns in the 2D
//                                                                                                                // between row and col                                                        
//                  if((xx - i == z - k) || (xx - i == k -z) || (x[k][xx] - j ==  z - k) ||
//                          (x[k][xx] - j ==  k - z) || (xx == i && x[k][xx] == j) ||(x[k][xx] == j && k == z) || (xx == i && k ==z))  // the value represents the columns in the 2D
//                  {
//                      return false;
//                  }    
////                if (x[i][k] == j || (k - i) == (x[i][k] - j) ||(k - i) == (j - x[i][k])) 
////                {
////                    return false;
////                }
//            }
//        }
//        return true;
//    }

    public void printQueens(int[] x) {
        int N = x.length;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
//                System.out.print("i "+ i);
//                System.out.print("j "+ j);
//                System.out.println("");

                if (x[i] == j) {
                    System.out.print("Q ");
                } else {
                    System.out.print("* ");
                }
            }
            System.out.println();
        }
        System.out.println();
    }
    
//    public void printQueens(int[][] x)
//    {
//        int N = x.length;
//        for (int k = 0; k < N; k++)
//        {
//            for (int i = 0; i < N; i++) 
//            {
//                for (int j = 0; j < N; j++) 
//                {
//                    if (x[k][i] == j)
//                        System.out.print("Q ");
//                    else
//                        System.out.print("* ");
//                }
//                System.out.println();
//            }
//            System.out.println("------------------------------------------------------\n");
//        }
//        System.out.println();
//    }

    public void placeNqueens(int i, int n) { // queen
        /**
         * Using backtracking this method prints all possible placements of n
         * queens on an n x n chessboard so that they are non-attacking.
         */
        
//        for (int k = 0; k<n; k++){ // for the depth                       ++
            for (int j = 0; j < n; j++) {// j in our algorithm
    //                if (canPlaceQueen(j, i)) {  // watch the switch between j and i
                  if(canPlaceQueen( i, j)) {  // row was not sent (k) .. j is the column .. i is the depth
                    x[i] = j;
//                      x[i][k]=j;  // i for the depth and k for the row  in 2 dimensional       ++
//                      count++;    // assign queens                       ++
                    if (i == n - 1) {
//                    if(i == count) { 
                        printQueens(x);
                    }
                    else{
                        
                        placeNqueens(i + 1, n);
//                        System.out.print(i);
                    }
                }
            }
//            i = 0;
//            count = 0;
        }

    public void callplaceNqueens() {
        placeNqueens(0, x.length);
    }
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        NQueenBacktracking Q = new NQueenBacktracking(4);
        Q.callplaceNqueens();
    }
    
}
