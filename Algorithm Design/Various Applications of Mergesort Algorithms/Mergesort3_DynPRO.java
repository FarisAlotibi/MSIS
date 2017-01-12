/**
 *
 * @author FRISCA
 */
public class Mergesort3_DynPRO {
    public static void mergesort3(int n, int[] S)
    {
        int m;
        int low, mid, high, size;
        int[] U = new int[n];
        for(size = 1; size < n; size *= 2)
            for(low = 0; low < n-size; low += 2*size)
            {
                mid = low + size - 1;
                high = Math.min(low + 2 * size - 1, n-1);
                merge3(S, U, low, mid, high);
            }
    }

    public static void merge3(int[] a, int[] U, int low, int mid, int high){
        for(int k = low; k <= high; k++)
            U[k] = a[k];

        int i = low, j = mid+1;
        for(int k = low; k <= high; k++)
        {
            if(i > mid) 					
                a[k] = U[j++];
            else if(j > high) 				
                a[k] = U[i++];
            else if(U[j] < U[i])			
                a[k] = U[j++];
            else							
                a[k] = U[i++];
        }
    }

    public static void printList(int[] List){  // printing function
        for(int i = 0; i < List.length; i++)
          System.out.print(List[i] + "  ");
        System.out.println();
    }

    public static void main(String[] args){
        long startRecording = System.nanoTime();
        int[] S={12,1,10,2,8,3,6,4,9,11,7,5}; //Worst case
//        int[] S={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
//        int[] S={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case

        System.out.println("The Array is ");
        printList(S);

        mergesort3(S.length, S); // call the function

        System.out.println("The Sorted Array is ");
        printList(S);

        long endRecording = System.nanoTime();
        long time=(endRecording-startRecording)/1000;
        System.out.println("The Worst case takes " + time + " Microseconds");
    }    
}
