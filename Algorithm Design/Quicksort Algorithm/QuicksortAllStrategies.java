import java.util.*;
/**
 *
 * @author FRISCA
 */
public class QuicksortAllStrategies{
	static int[] array;
	static int pivot_Method;
	private static void quicksort(int low, int high){
		if (low < high){

			int pivotpoint = partition(low, high);
			quicksort(low, pivotpoint - 1);
			quicksort(pivotpoint + 1, high);

		}
	}

	public static int partition(int low, int high){
		int i;
		int pivotitem = array[low]; // first element
		int j = low;

		// Choose pivot item strategy
		if(pivot_Method == 11) // last element pivot
		{
			pivotitem = array[high];
			swapping(low, high);
		}
		else if(pivot_Method == 22) // median-of-three element pivot
		{
			int med = medianOfThree(low, high);
			pivotitem = array[med];
			swapping(low, med);
		}
		else if(pivot_Method == 33) // random element pivot
		{
			int rnd = (int) (low + (Math.random()*((high-low)+1)));
			pivotitem = array[rnd];
			swapping(low, rnd);
		}
		else if(pivot_Method == 44) // median element pivot							 
		{
			int med = (low + high) / 2;
			pivotitem = array[med];
			swapping(low, med);
		}
		

		for(i = low + 1; i <= high; i++)
			if(array[i] < pivotitem){
				j++;
				swapping(i, j);
			}

			int pivotpoint = j;
			swapping(low, pivotpoint);

			return pivotpoint;
	}

	public static void swapping(int x, int y){ //swapping function
		int temp = array[x];
		array[x] = array[y];
		array[y] = temp;
	}

	public static int medianOfThree(int left, int right){  //to find the median of three process
		int mid = (left + right) / 2;

		if (array[left] > array[mid])
			swapping(left, mid);

		if (array[left] > array[right])
			swapping(left, right);

		if (array[mid] > array[right])
			swapping(mid, right);

		swapping(mid, right-1);

		return right-1;
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
        array = S;
        pivot_Method = 33; // choose strategy from 0, 11, 22, 33, 44
        System.out.println("The Array is ");
        printList(S);

        quicksort(0, S.length-1);

        System.out.println("The Sorted Array is ");
        printList(S);

        long endRecording = System.nanoTime();
        long time=(endRecording-startRecording)/1000;
//		 System.out.println("The Best case takes " + time + " Microseconds");
//       System.out.println("The Average case takes " + time + " Microseconds");
        System.out.println("The Worst case takes " + time + " Microseconds");
    }	
}
