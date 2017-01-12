package e28_algorithms;

/**
 *
 * @author FRISCA
 */
public class Selection {

    public static int pivot =0;
    public static int[] S={12,1,10,2,8,3,6,4,9,11,7,5}; //Worst case
//    public static int[] S={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
//    public static int[] S={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case
    static int selection (int low, int high, int k){
        int pivotpoint = low;
        if(low == high)
            return S[low];
        else{
            partition(S, low, high, pivotpoint);
            if(k == pivotpoint)
                return S[pivotpoint];
            else if(k<pivotpoint)
                return selection(low, pivotpoint-1, k);
            else 
                return selection(pivotpoint + 1, high, k);
        }
    }

    static void partition(int S[], int low, int high, int pivotpoint){
        pivot = S[low];
        int temp = 0;
        int j = low;
        for (int i = low; i < high; i++){
            if (S[i] < pivot){
             j = j + 1;
             swapping(i,j);
            }
        }
        pivotpoint = j;
        swapping(low,pivotpoint);
    }

    static void swapping(int x,int y){ // swapping function
       int temp = S[x];
       S[x] = S[y];
       S[y] = temp;
    }

    public static void printList(int[] List){
        for(int i = 0; i < List.length; i++)
          System.out.print(List[i] + "  ");
        System.out.println();
    }
    
    public static void main(String[] args) {
        int value = 10;
        System.out.println("The Array is ");
        printList(S);
        System.out.print("Which is smallest? From the "+ value + "th\n");
        int key;

        long startRecording = System.nanoTime();  // recording the time

        key = selection(0,S.length,value);
        long endRecording = System.nanoTime();
        
        System.out.print("Key is "+ key + "\n");
        long time=(endRecording-startRecording)/1000;
        System.out.println("The Worst case takes " + time + " Microseconds");
    }
}
