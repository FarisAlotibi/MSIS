
package nonrecursivemergesortDivideAndConquer;
 import java.util.*;
/**
 *
 * @author FRISCA
 */
public class NonRecursiveMergesort {
    public static void merge(int [] A, int first, int last){
        int [] temp = new int[last-first+1];
        if (first<last){
            int i1 = first;
            int mid = (first+last)/2;
            int i2 = mid+1;

            for(int i=0;i< temp.length;i++){
                if (i1>mid){
                    temp[i]= A[i2];
                    i2++;
                }				
                else 
                    if (i2>last){
                        temp[i]= A[i1];
                        i1++;
                    }
                    else
                        if (A[i1]<A[i2]){
                            temp[i]= A[i1];
                            i1++;
                        }
                        else{
                            temp[i]= A[i2];
                            i2++;
                        }
            }
            for(int i=0;i<temp.length;i++)
                A[first+i]=temp[i];
        }
    }
    
//        public static boolean sorted; //Indicates if the first and second half of the array have already been sorted 
//	public static int first;
//	public static int last;
//	

    public static void mergesort(int [] A){
        Stack<MergesortRecord> stack = new Stack();
        MergesortRecord m = new MergesortRecord(false, 0, A.length-1);
        stack.push(m);
        while (!stack.empty()){
            m=stack.pop();
            if (m.getsorted()){//If first and second halves of array have been sorted, merge them
                merge(A,m.getfirst(),m.getlast());
            }
            else{
                if (m.getfirst()<m.getlast()){
                    int mid = (m.getfirst()+m.getlast())/2;
                    stack.push(new MergesortRecord(true,m.getfirst(),m.getlast())); // top
                    stack.push(new MergesortRecord(false,m.getfirst(),mid));// left
                    stack.push(new MergesortRecord(false,mid+1,m.getlast()));// right
                }
            }
//            System.out.print("Current array is: ");
//            printArray(A); //for debugging purposes	
//            System.out.println();
        }
    }
    public static int [] generateRandomArray(int n, int max){
        Random generator = new Random();
        int []randArray = new int[n];
        for(int i=0;i<n;i++)
            randArray[i] = generator.nextInt(max);
        return randArray;
    }

    public static void printArray(int [] A){
        for(int i =0;i<A.length;i++)
            System.out.print(A[i]+" ");
        System.out.println();
    }

    public static void main(String[] args){
        long startRecording = System.nanoTime();
//      int [] A = {3, 4, 8, 2, 9, 7};
//      int [] A = {4, 4, 8, 2, 9, 7};
      int[] A={12,1,10,2,8,3,6,4,9,11,7,5}; //Worst case
//      int[] A={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
//        int[] A={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case
//      int [] A = generateRandomArray(50,100);
        System.out.println("The Array is ");
        printArray(A);
        mergesort(A);
        System.out.println("The Sorted Array is ");
        printArray(A);
        long endRecording = System.nanoTime();
        long time=(endRecording-startRecording)/1000;
        System.out.println("The Worst case takes " + time + " Microseconds");
    }
}