/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package tsp_bruteforce;


import java.util.*;
import java.lang.*;
/**
 *
 * @author FRISCA
 */
public class TSP_BruteForce {
//
//    /**
//     * @param args the command line arguments
//     */
    public static void main(String[] args)
    {
        TSP_BruteForce obj = new TSP_BruteForce();

        int[][]x = {{0,1,0,1,0},  //Represent the graphs in the adjacent matrix forms
                   {1,0,0,0,1},
                   {0,0,0,1,0},
                   {1,0,1,0,1},
                   {0,1,0,1,0}};

        int[][]y = {{0,1,0,0,0,1},
                   {1,0,1,0,0,1},
                   {0,1,0,1,1,0},
                   {0,0,1,0,0,0},
            
                   {1,1,0,0,1,0}};

        int[][]z = {{0,1,1,0,0,1},
                   {1,0,1,0,0,0},
                   {1,1,0,1,0,1},
                   {0,0,1,0,1,0},
                   {0,0,0,1,0,1},
                   {1,0,1,0,1,0}};

        int[][] r = {{0,1,1,1,1,1},
                    {1,0,1,1,1,1},
                    {1,1,0,1,1,1},
                    {1,1,1,0,1,1},
                    {1,1,1,1,0,1},
                    {1,1,1,1,1,0}};

        int[][] d = {{ 0, 36, 32, 54, 20, 40}, 
                    {36,  0, 22, 58, 54, 67}, 
                    {32, 22,  0, 36, 42, 71}, 
                    {54, 58, 36,  0, 50, 92}, 
                    {20, 54, 42, 50,  0, 45}, 
                    {40, 67, 71, 92, 45,  0}};

//         obj.locate_all_Hamilton_path(d);   //list all Hamiltonian paths of graph
        obj.findTheShortestHamiltonPathAtThisStartingPoint(d, 1);  //list all Hamiltonian paths start at point 1


    }

    static int length;
    static int[] paths;
    int[][] all_paths_Av;
    static int counter = 0;   

    //List all possible Hamilton path in the graph
    public void locate_all_Hamilton_path(int[][] x)
    {
        length = x.length;
        int[][] original_x_Value = new int[length][length];
        for(int i = 0; i < length; i++)
            for(int j = 0; j < length; j++)
                original_x_Value[i][j] = x[i][j];

        int row_length = 1; // = N!
        for (int i = 1; i <= length; i++ ) row_length *= i;
        System.out.println(" "+row_length);
        all_paths_Av = new int[row_length][length+1]; 
        paths = new int[length+1];
        
        //Go through column(of matrix)
        for(int i = 0; i < length; i++)
        {
            paths[0] = paths[length] = i + 1;
            locate_Hamilton_path(x, 0, i, 0);
        }

         int[] weight = new int[row_length];
        // weight
        for(int i = 0; i < row_length; i++)
        {
            weight[i] = 0;
            for(int j = 0; j < length; j++)
            {
                if(j == length-1)
                    weight[i] += original_x_Value[all_paths_Av[i][j]-1][all_paths_Av[i][0]-1];
                else
                    weight[i] += original_x_Value[all_paths_Av[i][j]-1][all_paths_Av[i][j+1]-1];


            }
        }

        int minimum = weight[0];
        for(int i = 1; i < row_length; i++)
            if(weight[i] <= minimum)
                minimum = weight[i];

        for(int i = 0; i < row_length; i++)
            if(weight[i] == minimum)
            {
                for(int j = 0; j <= length; j++)
                    System.out.print(all_paths_Av[i][j] + " ");
                
                System.out.println(" = " + weight[i]);
            }
    }
    //List all possible Hamilton path with fixed starting point
    public void findTheShortestHamiltonPathAtThisStartingPoint(int[][] x, int startingVertex)
    {
        length = x.length;
        int[][] original_x_Value = new int[length][length];
        for(int i = 0; i < length; i++)
            for(int j = 0; j < length; j++)
                original_x_Value[i][j] = x[i][j];

        int row_length = 1; // = (N-1)!
        for (int i = 1; i < length; i++ ) row_length *= i;
        all_paths_Av = new int[row_length][length+1]; 
        paths = new int[length+1];

        //Go through row(with given column)
        for(int i = startingVertex - 1; i < startingVertex; i++)
        {
            paths[0] = paths[length] = i + 1;
            locate_Hamilton_path(x, 0, i, 0);
        }

        int[] weight = new int[row_length];
        // weight
        for(int i = 0; i < row_length; i++)
        {
            weight[i] = 0;
            for(int j = 0; j < length; j++)
            {
                if(j == length-1)
                    weight[i] += original_x_Value[all_paths_Av[i][j]-1][all_paths_Av[i][0]-1];
                else
                    weight[i] += original_x_Value[all_paths_Av[i][j]-1][all_paths_Av[i][j+1]-1];


            }
        }

        int minimum = weight[0];
        for(int i = 1; i < row_length; i++)
            if(weight[i] <= minimum)
                minimum = weight[i];

        for(int i = 0; i < row_length; i++)
            if(weight[i] == minimum)
            {
                for(int j = 0; j <= length; j++)
                    System.out.print(all_paths_Av[i][j] + " ");
                
                System.out.println(" = " + weight[i]);
            }
    }

    private void locate_Hamilton_path(int[][] matrix, int x, int y, int l)
    {
        for(int i = x; i < length; i++){         //Go through row

            if(matrix[i][y] != 0){      //2 point connect

                if(detect(paths, i + 1))// if detect a point that already in the path => duplicate 
                    continue;

                l++;                //Increase path length due to 1 new point is connected 
                paths[l] = i + 1;    //correspond to the array that start at 0, graph that start at point 1
                if(l == length - 1){  //Except initial point already counter =>success connect all point
                    counter++;   
                    if (counter == 1)
                        System.out.println("Hamilton path of graph: ");

                    //savePath(paths);
                    for(int j = 0; j < paths.length; j++)
                        all_paths_Av[counter-1][j] = paths[j];
                    display(paths);
                    l--;
                    continue;
                }

                matrix[i][y] = matrix[y][i] = 0;  //remove the path that has been get and
                locate_Hamilton_path(matrix, 0, i, l); //recursively start to find new path at new end point
                l--;                // reduce path length due to the failure to find new path         
                matrix[i][y] = matrix[y][i] = 1; //and tranform back to the inital form of adjacent matrix(graph)
            }
        }
        paths[l+1]=0;    //disconnect two point correspond the failure to find the..   
    }                     //possible hamilton path at new point(ignore newest point try another one)         

    public void display(int[] x)
    {
        System.out.print(counter + " : ");
        for(int i:x)
        {
            System.out.print(i + " ");
        }
        System.out.println();   
    }

//    private void savePath(int[] x)
//    {
//        for(int i = 0; i < x.length; i++)
//            all_paths_Av[counter-1][i] = x[i];
//    }

    //Detect duplicate point in Halmilton path
    private boolean detect(int[]x,int target)
    { 
        boolean t=false;                        
        for(int i:x){
            if(i==target){
                t = true;
                break;
            }
        }
        return t;
    }    
}    

//    static int len;
//    static int[] path;
//    int[][] allPaths;
//    static int count = 0;   
//
//    //List all possible Hamilton path in the graph
//    public void allHamiltonPath(int[][] x)
//    {
//        
//        len = x.length;
//        int[][] orgX = new int[len][len];
//        for(int i = 0; i < len; i++)
//            for(int j = 0; j < len; j++)
//            {
//                orgX[i][j] = x[i][j];
//            }
//
//        int row_len = 1; // = N!
//        for (int i = 1; i <= len; i++ ) row_len *= i;
//        
//        allPaths = new int[row_len][len+1]; 
//        path = new int[len+1];
//        
//        //Go through column(of matrix)
//        for(int i = 0; i < len; i++)
//        {
//            path[0] = path[len] = i + 1;
//            findHamiltonpath(x, 0, i, 0);
//        }
//
//        int[] w = new int[row_len];
//        // weight
//        for(int i = 0; i < row_len; i++)
//        {
//            w[i] = 0;
//            for(int j = 0; j < len; j++)
//            {
//                if(j == len-1)
//                    w[i] += orgX[allPaths[i][j]-1][allPaths[i][0]-1];
//                else
//                    w[i] += orgX[allPaths[i][j]-1][allPaths[i][j+1]-1];
//
//
//            }
//        }
//        // System.out.println(orgX[0][1] + orgX[1][2] + orgX[2][3]);
//        int min = w[0];
//        ArrayList<Integer> list = new ArrayList<Integer>();
//        int idx_min = -1;
//        for(int i = 1; i < row_len; i++)
//        {
//            if(w[i] <= min)
//            {
//                idx_min = i;
//                list.add(i);
//                min = w[i];
//                for(int j = 0; j <= len; j++)
//                {
//                    System.out.print(allPaths[i][j] + " ");
//                }
//                System.out.println(" = " + w[i]);
//            }
//        }
//        for(int i = 0; i < list.size(); i++)
//        {
//            for(int j = 0; j <= len; j++)
//            {
//                // System.out.print(allPaths[list.get(i)][j] + " ");
//            }
//            // System.out.println(" = " + min);
//        }
//    }
//
//    //List all possible Hamilton path with fixed starting point
//    public void HamiltonPath(int[][] x, int start)
//    {
//        len = x.length;
//        int row_len = 1; // = N!
//        for (int i = 1; i < len ; i++ ) row_len *= i;
//        path = new int[len];
//        int i;
//        //Go through row(with given column)
//        for(i = start - 1; i < start; i++)
//        {
//            path[0] = i + 1;
////            findHamiltonpath(x, 0, i, 0, path);
//            findHamiltonpath(x, 0, i, 0);
//        }
//    }
//
//    private void findHamiltonpath(int[][] M, int x, int y, int l)
//    {
//        
//        int[][] M1 = M.clone();
////        len = M1.length;
////        int[][] M1 = M;
////        System.out.println(M1[0][1] + M1[1][2] + M1[2][3]);
//
//
////
////        for(int i = 0; i < len; i++)
////            for(int j = 0; j < len; j++)
////            {
////                M1[i][j] = M[i][j];
////            }
//        for(int i = x; i < len; i++){         //Go through row
//            if(M1[i][y] != 0){      //2 point connect
//                if(detect(path, i + 1))// if detect a point that already in the path => duplicate 
//                    continue;
//                l++;                //Increase path length due to 1 new point is connected 
//                path[l] = i + 1;    //correspond to the array that start at 0, graph that start at point 1
//                if(l == len - 1){   //Except initial point already count =>success connect all point
//                    count++;   
//                    if (count == 1)
//                        System.out.println("Hamilton path of graph: ");
//
//                    savePath(path);
//                    display(path);
//                    l--;
//                    continue;
//                }
//
//                M1[i][y] = M1[y][i] = 0;  //remove the path that has been get and
//                findHamiltonpath(M1, 0, i, l); //recursively start to find new path at new end point
//                l--;                // reduce path length due to the failure to find new path         
//                M1[i][y] = M1[y][i] = 1; //and tranform back to the inital form of adjacent matrix(graph)
//            }
//        }
//         path[l+1]=0;    //disconnect two point correspond the failure to find the..   
//    }                     //possible hamilton path at new point(ignore newest point try another one)         
//
//    public void display(int[] x)
//    {
//        System.out.print(count + " : ");
//        for(int i:x)
//        {
//            System.out.print(i + " ");
//        }
//        System.out.println();   
//    }
//
//    private void savePath(int[] x)
//    {
//        for(int i = 0; i < x.length; i++)
//            allPaths[count-1][i] = x[i];
//    }
//
//    //Detect duplicate point in Halmilton path
//    private boolean detect(int[]x,int target)
//    { 
//        boolean t=false;                        
//        for(int i:x){
//            if(i==target){
//                t = true;
//                break;
//            }
//        }
//        return t;
//    }
//    public static void main(String[] args) {
//        // TODO code application logic here
//        
//        
//        TSP_BruteForce obj = new TSP_BruteForce();
//
//        int[][]x = {{0,1,0,1,0},  //Represent the graphs in the adjacent matrix forms
//                    {1,0,0,0,1},
//                    {0,0,0,1,0},
//                    {1,0,1,0,1},
//                    {0,1,0,1,0}};
//
//        int[][]y = {{0,1,0,0,0,1},
//                    {1,0,1,0,0,1},
//                    {0,1,0,1,1,0},
//                    {0,0,1,0,0,0},
//                    {0,0,1,0,0,1},
//                    {1,1,0,0,1,0}};
//
//        int[][]z = {{0,1,1,0,0,1},
//                    {1,0,1,0,0,0},
//                    {1,1,0,1,0,1},
//                    {0,0,1,0,1,0},
//                    {0,0,0,1,0,1},
//                    {1,0,1,0,1,0}};
//
//        int[][] r = {{0,1,1,1,1,1},
//                     {1,0,1,1,1,1},
//                     {1,1,0,1,1,1},
//                     {1,1,1,0,1,1},
//                     {1,1,1,1,0,1},
//                     {1,1,1,1,1,0}};
//
//        int[][] d = {{0, 36, 32, 54, 20, 40}, 
//                     {36, 0, 22, 58, 54, 67}, 
//                     {32, 22, 0, 36, 42, 71}, 
//                     {54, 58, 36, 0, 50, 92}, 
//                     {20, 54, 42, 50, 0, 45}, 
//                     {40, 67, 71, 92, 45, 0}};
//
//          obj.allHamiltonPath(d);   //list all Hamiltonian paths of graph
////        obj.HamiltonPath(d,1);  //list all Hamiltonian paths start at point 1
//    }

