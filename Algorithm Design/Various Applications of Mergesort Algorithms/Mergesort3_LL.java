/**
 *
 * @author FRISCA
 */
public class Mergesort3_LL {
    private static class Node {
        int key;
        int link;
    }
    static Node S[];

    public static int mergesort4(int low, int high, int mergedlist){
        int mid, list1 = low, list2 = high;
        if(low == high){
            mergedlist = low;
            S[mergedlist].link = -1;
        }
        else{
            mid = (low+high)/2;
            list1 = mergesort4(low, mid, list1);
            list2 = mergesort4(mid + 1, high, list2);
            mergedlist = merge4(list1, list2, mergedlist);
        }
        return mergedlist;
    }

    public static int merge4(int list1, int list2, int mergedlist){
        int lastsorted;
        if(S[list1].key < S[list2].key){
            mergedlist = list1;
            list1 = S[list1].link;
        }
        else{
            mergedlist = list2;
            list2 = S[list2].link;
        }
        lastsorted = mergedlist;
        while(list1 != -1 && list2 != -1){
            if(S[list1].key < S[list2].key){
                S[lastsorted].link = list1;
                lastsorted = list1;
                list1 = S[list1].link;
            }
            else{
                S[lastsorted].link = list2;
                lastsorted = list2;
                list2 = S[list2].link;
            }
        }

        if(list1 == -1)
            S[lastsorted].link = list2;
        else
            S[lastsorted].link = list1;

        return mergedlist;
    }

    public static void printList(Node[] S, int list_Front){  // printing function
        while(true){
            System.out.print(S[list_Front].key + " ");
            if(S[list_Front].link == -1)
                break;
            list_Front = S[list_Front].link;
        }
        System.out.println();
    }

    public static void main(String[] args)
    {
        long startRecording = System.nanoTime();
        S = new Node[12];

        for(int i = 0; i < S.length; i++)
            S[i] = new Node();
//worst case
        S[0].key = 12; S[0].link = 1;
        S[1].key = 1;  S[1].link = 2;
        S[2].key = 10; S[2].link = 3;
        S[3].key = 2;  S[3].link = 4;
        S[4].key = 8;  S[4].link = 5;
        S[5].key = 3;  S[5].link = 6;
        S[6].key = 6;  S[6].link = 7;
        S[7].key = 4;  S[7].link = 8;
        S[8].key = 9;  S[8].link = 9;
        S[9].key = 11; S[9].link = 10;
        S[10].key = 7; S[10].link = 11;
        S[11].key = 5; S[11].link = -1;
        
//average case
//        S[0].key = 1;  S[0].link = 1;
//        S[1].key = 2;  S[1].link = 2;
//        S[2].key = 3;  S[2].link = 3;
//        S[3].key = 4;  S[3].link = 4;
//        S[4].key = 5;  S[4].link = 5;
//        S[5].key = 6;  S[5].link = 6;
//        S[6].key = 7;  S[6].link = 7;
//        S[7].key = 12; S[7].link = 8;
//        S[8].key = 10; S[8].link = 9;
//        S[9].key = 8;  S[9].link = 10;
//        S[10].key = 11;S[10].link = 11;
//        S[11].key = 9; S[11].link = -1;

//best case
//        S[0].key = 1;  S[0].link = 1;
//        S[1].key = 2;  S[1].link = 2;
//        S[2].key = 3;  S[2].link = 3;
//        S[3].key = 4;  S[3].link = 4;
//        S[4].key = 5;  S[4].link = 5;
//        S[5].key = 6;  S[5].link = 6;
//        S[6].key = 7;  S[6].link = 7;
//        S[7].key = 8;  S[7].link = 8;
//        S[8].key = 9;  S[8].link = 9;
//        S[9].key = 10; S[9].link = 10;
//        S[10].key = 11;S[10].link = 11;
//        S[11].key = 12;S[11].link = -1;

        int list_Front = 0;
        System.out.println("The Array is ");
        printList(S, list_Front);

        list_Front = mergesort4(0, S.length-1, list_Front); // calling function
        
        System.out.println("The Sorted Array is ");
        printList(S, list_Front);

        long endRecording = System.nanoTime();
        long time=(endRecording-startRecording)/1000;
        System.out.println("The Worst case takes " + time + " Microseconds");
    }
}
