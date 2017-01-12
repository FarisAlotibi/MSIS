package e28_algorithms;
import java.util.Arrays;
/**
 *
 * @author FRISCA
 */
public class SelectionUsingMedian {

  static int pivotpoint;
  public static int[] S={12,1,10,2,8,3,6,4,9,11,7,5}; //Worst case
//  public static int[] S={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
//  public static int[] S={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case

  public static int select2(int n, int [] T, int k){
    return selection2(T,0,n-1,k);
  }

  public static int selection2(int []S,int low,int high,int k){
    if(low==high){
      return S[low];
    }
    else{
      pivotpoint = partition2(low,high,pivotpoint);
      if(k==pivotpoint){
        return S[pivotpoint];
      }
      else if(k<pivotpoint){
        return selection2(S,low,pivotpoint-1,k);
      }
      else{
        return selection2(S,pivotpoint+1,high,k);
      }
    }
  }

  public static int partition2(int low,int high,int pivotpoint){
    int arraysize = high-low+1;
    int r=(int)Math.ceil((double)arraysize/5);
    int i,j,mark,first,last;
    int pivotitem;

    mark=0;
    int [] T=new int[r];

    for(i=0;i<r;i++){
      first = low+5*(i+1)-5;
      last = Math.min(low+5*(i+1)-1,arraysize);
      T[i]=findMedian(first,last);
    }

    pivotitem=select2(r,T,(r+1)/2);
    j=low;

    for(i=low;i<=high;i++){
      if(S[i]==pivotitem){
        int temp=S[i];
        S[i]=S[j];
        S[j]=temp;
        mark=j;
        j++;
      }
      else if(S[i]<pivotitem){
        int temp=S[i];
        S[i]=S[j];
        S[j]=temp;
        j++;
      }
    }

    pivotpoint=j-1;
    int temp=S[mark];
    S[mark]=S[pivotpoint];
    S[pivotpoint]=temp;

    return pivotpoint;
  }

  public static int findMedian(int first,int last){ // used to find the median
    Arrays.sort(S); // used to sort before finding the median
    int length = last-first+1;
    int middle = length/2+first;
    int medianValue;
    if (length%2 == 1)
      medianValue = S[middle];
    else
      medianValue = (S[middle-1] + S[middle]) / 2;
    
    return medianValue;
  }

  public static void printList(int[] List){ // printing process
    for(int i = 0; i < List.length; i++)
      System.out.print(List[i] + "  ");
    System.out.println();
  }

  static int key1;

  public static void main(String[] args){
    System.out.println("The Array is ");
    printList(S);
    int key = 10; //choose the k th
    key1=key;
    System.out.print("Which is smallest? From the "+ key + "th\n");

    long startRecording = System.nanoTime();
    key = select2(S.length-1,S,key);
    long endRecording = System.nanoTime();
    System.out.print("Key is "+ key + "\n");

    long time=(endRecording-startRecording)/1000;
    System.out.println("The Worst case takes " + time + " Microseconds");
  }
}
