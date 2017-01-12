/**
 *
 * @author FRISCA
 */
public class Mergesort1 {
    public static void mergesort(int n, int[] S){
        if (n > 1)
        {
            int h = (int)Math.floor(n/2), m = n - h;
            int[] U = new int[h], V = new int[m];

            for (int i = 0; i < h; i++)
                U[i] = S[i];
            int k = 0;
            for (int i = h; i < n; i++)
                V[k++] = S[i];

            mergesort(h, U);
            mergesort(m, V);
            merge(h, m, U, V, S);
        }
    }

    public static void merge(int h, int m, int[] U, int[] V, int[] S){
        int i, j, k;
        i = 0; j = 0; k = 0;
        while(i < h && j < m)
        {
            if(U[i] < V[j]) {
                S[k] = U[i];
                i++;
            }
            else{
                S[k] = V[j];
                j++;
            }
            k++;
        }
        while (j < m)
            S[k++] = V[j++];
        while (i < h)
            S[k++] = U[i++];
    }
    public static void printList(int[] List){ // printing function
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

        mergesort(S.length, S);

        System.out.println("The Sorted Array is ");
        printList(S);

        long endRecording = System.nanoTime();
        long time=(endRecording-startRecording)/1000;
        System.out.println("The Worst case takes " + time + " Microseconds");
    }    
}
