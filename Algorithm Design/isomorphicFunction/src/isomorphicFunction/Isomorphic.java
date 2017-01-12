package isomorphicFunction;
/**
*
* @author FRISCA
*/
public class Isomorphic {

//int[][]graph1= {{0,0,1,1,1,1,0}, // Test case 3
//                {0,0,0,0,1,0,0},
//                {1,0,0,0,1,1,0},
//                {1,0,0,0,1,1,0},
//                {1,1,1,1,0,0,1},
//                {1,0,1,1,0,0,1},
//                {0,0,0,0,1,1,0}};
//
//int[][]graph2= {{0,0,0,0,0,0,1},
//                {0,0,1,1,0,1,1},
//                {0,1,0,0,0,1,1},
//                {0,1,0,0,0,1,1},
//                {0,0,0,0,0,1,1},
//                {0,1,1,1,1,0,0},
//                {1,1,1,1,1,0,0}};
int [][]graph1= {{0,1,0,0,1,1,0},  // Test case 1
                 {1,0,1,0,0,0,1},
                 {0,1,0,1,0,0,0},
                 {0,0,1,0,0,1,1},
                 {1,0,0,0,0,0,1},
                 {1,0,0,1,0,0,1},
                 {0,1,0,1,1,1,0}};
int[][] graph2= {{0,1,0,1,1,0,0},
                 {1,0,0,0,0,1,1},
                 {0,0,0,1,1,1,0},
                 {1,0,1,0,0,0,0},
                 {1,0,1,0,0,1,1},
                 {0,1,1,0,1,0,0},
                 {0,1,0,0,1,0,0}};
//int[][]graph1= {{0,1,1,1,1,0}, // Test case 2
//                  {1,0,0,0,1,1},
//                  {1,0,0,0,1,1},
//                  {1,0,0,0,0,1},
//                  {1,1,1,0,0,1},
//                  {0,1,1,1,1,0}};
//
//int[][]graph2= {{0,0,0,0,0,1},
//                  {0,0,0,1,1,0},
//                  {0,0,0,1,1,0},
//                  {0,1,1,0,1,1},
//                  {0,1,1,1,0,0},
//                  {1,0,0,1,0,0}};

static int n;
int counter = 0;
static int[] x;  // 1 dimensional, the ordering
public boolean promissing(int r, int c) { // promissng function
    boolean check;
    for(int i=0; i<r; i++)
        if(x[i] == c){
            check = false;
            return check;
        }
    for(int k=0; k<r; k++)
        if(graph1[k][r] != graph2[x[k]][c]){
            check = false;
            return check;
        }
    check = true;
    return check;
}
public void isoMorph(int i) { // isomorphic function
     //Using backtracking
    if(i == 0)
    {
        if(graph1.length == graph2.length) //ensure that both graphs have same length
        {   
            n = graph1.length;
            x = new int[n];
            for(int a = 0; a < n; a++)
                x[a] = -1;      // initilization
        }
        else{
            System.out.println("Not isomorphic.");
            return;
        }
    }
    for(int j = 0; j < n; j++) {
        if(promissing( i, j)){
            x[i] = j;
            if (i == n - 1){
                counter++;
                if(counter != 0)
                    System.out.println("Isomorphic");
                printOrdering(x);
            }
            else
                isoMorph(i + 1); 
        }
    }
}
public void printOrdering(int [] ordering){     //printing function
    for(int j=0;j<n;j++){
        System.out.print(ordering[j]+1);
        if(j != n-1)
            System.out.print(", ");
    }
    System.out.println();
}
public static void main(String[] args) {       
    Isomorphic Q = new Isomorphic();        // create an object
    Q.isoMorph(0);                          // start i with 0
    if(Q.counter == 0)                      // if counter did increase means n solution
        System.out.println("Not isomorphic");   
}
}
