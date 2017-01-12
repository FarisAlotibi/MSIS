package e28_algorithms;
import java.util.*;
/**
 *
 * @author FRISCA
 */
public class ProbabilisticSelection {
  static int pivotpoint;
  public static int[] S={12,1,10,2,8,3,6,4,9,11,7,5}; //Worst case
//    public static int[] S={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
//    public static int[] S={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case
  public static int selection3(int low, int high, int k){

    if(low==high){
      return S[low];
    }
    else{
      pivotpoint = partition3(low,high,pivotpoint);
      if(k==pivotpoint){
        return S[pivotpoint];
      }
      else if(k<pivotpoint){
        return selection3(low,pivotpoint-1,k);
      }
      else{
        return selection3(pivotpoint+1,high,k);
      }
    }
  }

  public static int partition3(int low,int high,int pivotpoint){
    int i,j;
    int pivotitem;
    Random rand=new Random();
    int randspot = rand.nextInt((high - low)+1) + low;
    pivotitem=S[randspot];
    int temp=S[low];
    S[low]=S[randspot];
    S[randspot]=temp;
    j=low;
    for(i=low+1;i<=high;i++){
      if(S[i]<pivotitem){
        j++;
        temp=S[i];
        S[i]=S[j];
        S[j]=temp;
      }
    }
    pivotpoint=j;
    temp=S[low];
    S[low]=S[pivotpoint];
    S[pivotpoint]=temp;

    return pivotpoint;
  }
  
  public static void printList(int[] List){ // printing function
      for(int i = 0; i < List.length; i++)
        System.out.print(List[i] + "  ");
      System.out.println();
  }

  public static void main(String[] args) {
      long startRecording = System.nanoTime();
      int k=10;//3

      System.out.println("The Array is ");
      printList(S);
      System.out.print("Which is smallest? From the "+ k + "th\n");
      k = selection3(0, S.length-1, k);  // call the function

      System.out.println("Key is " + k);
      long endRecording = System.nanoTime();
      long time=(endRecording-startRecording)/1000;
      System.out.println("The Worst case takes " + time + " Microseconds");
  }
}
