package breadth.first;
import java.util.*;
/**
*
* @author FRISCA
*/
public class BreadthFirst {   
// int[][] graph = {{0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, //test
//                  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0},
//                  {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, 
//                  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//                  {0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
//                  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, 
//                  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, 
//                  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1}, 
//                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0}};  


// int[][] graph = {{0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1},      //test case 2
//                  {1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
//                  {1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0},
//                  {1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
//                  {1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
//                  {0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0},
//                  {1, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
//                  {1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
//                  {1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1},
//                  {1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0},
//                  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
//                  {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1},
//                  {0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1},
//                  {1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1},
//                  {1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0}};
  int[][] graph = {{0, 0, 0, 1, 0, 1},      // testcase 1
                   {0, 0, 0, 1, 1, 1},
                   {0, 0, 0, 1, 0, 0},
                   {1, 1, 1, 0, 0, 0},
                   {0, 1, 0, 0, 0, 0},
                   {1, 1, 0, 0, 0, 0}};


/* Integer array used to mark each checked vertex.
   If checked[v] = -1 , vertex v has not been checked.
   If v is root of a Breadth First Search, checked[v] = 0;
Other positive values represent for the shortest path length from root to a particular vertex.*/
private int[] checked;

private int[] minCircle;        // Integer array minCircle is used to store minimum length of circle(s) involving the root vertex.

private int[] predecessor;      // Integer array predecessor is used to store predecessor of every vertex for computing minimum length of circles

public int girth(){

    minCircle = new int[graph.length];
    predecessor = new int[graph.length];
    checked = new int[graph.length];

    // Compute the girth for the tree rooted at each vertex
    // girth of a given graph.
    // It takes O(n*(n+m))
    for(int i=0;i<graph.length;i++){
        minCircle[i]=breathFirstSearch(i);
    }

    int minimum = Integer.MAX_VALUE;
    for(int i=0;i<minCircle.length;i++){
        if(minCircle[i] < minimum){
            minimum = minCircle[i];
        }
    }
    return minimum;     // the number of short cycle returns
}



/* The girth of a graph is the length of its shortest cycle. If a graph is acyclic, then its
 girth is infinite.*/
private int breathFirstSearch(int ver){

    
    for(int i=0;i<graph.length;i++){                        // Initialize int[] checked before a Breadth First Search is going to start.
        checked[i] = -1;
    }
    
    Queue<Integer> queue = new LinkedList<Integer>();       // A Breadth First Search starts.
    int girth = Integer.MAX_VALUE;
    checked[ver] = 0;
    queue.add(ver);

    while(!queue.isEmpty()){
        int j = queue.poll();
        for(Integer k: getTheNeighbors(j)){
            if(checked[k] <0){
                
                checked[k] = checked[j] +1;                 // Each level of BFS should increase shortest path length by 1
                predecessor[k] = j;                         // k's parent u was found.
                queue.add(k);
            }
            else{
                // If the checked vertex k is not j's parent, a cycle is here
                if(k != predecessor[j]){
                    // Decide if this length cycle is greater than the smallest one discovered.
                    // If no, this cycle is the smallest
                    if(girth > checked[k] + checked[j] + 1){
                        girth = checked[k] + checked[j] + 1;
                    }
                }
            }
        }
    }
    return girth;
}

public List<Integer> getTheNeighbors(int verteX)
{
    List<Integer> neighbor = new ArrayList<Integer>();
    for (int i = 0; i < graph.length; i++)
    {
        if(graph[verteX][i] == 1)
            neighbor.add(i);
    }
    return neighbor;
}

public static void main(String[] args) {
    long startTime = System.currentTimeMillis();

    BreadthFirst breFirObj = new BreadthFirst();

    if(breFirObj.girth() == Integer.MAX_VALUE){
        System.out.println("Because the graph is acyclic graph, the girth is infinite.");
    }
    else{
        System.out.println("The girth is " + breFirObj.girth());
        System.out.format("%n%-32s: %d ms.%n", "Processing Time of Finding Girth",
                    (System.currentTimeMillis() - startTime));
    }
}

}

    