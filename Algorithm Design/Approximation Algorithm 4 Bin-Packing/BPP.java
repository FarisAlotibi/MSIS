import java.util.*;

public class BPP {

    public static void binPacking(int[] a)
    {
        int size = 6;
        ArrayList<Integer> binValues = new ArrayList<Integer>();
        binValues.add(size);

        for (int i = 0; i < a.length; i++)
        {
            boolean packed = false;
            for (int j = 0; j < binValues.size(); j++)
            {
                if (binValues.get(j) - a[i] >= 0)
                {
                    binValues.set(j, binValues.get(j) - a[i]);
                    packed = true;
                    break;
                }
            }
            if(!packed)
            {
                binValues.add(size);
                int last = binValues.size()-1;
                binValues.set(last, binValues.get(last) - a[i]);
            }
        }

        System.out.println("Number of bins required using first fit decreasing algorithm is:" + binValues.size());
    }

    public static int[] sort(int[] sequence, int n)
    {
        // Bubble Sort descending order
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n - 1; j++){
                if (sequence[j] < sequence[j + 1])
                {
                    sequence[j] = sequence[j] + sequence[j + 1];
                    sequence[j + 1] = sequence[j] - sequence[j + 1];
                    sequence[j] = sequence[j] - sequence[j + 1];
                }
            }
        } 
        return sequence;
    }

    public static void main(String[] args)
    {
        System.out.println("BIN - PACKING Algorithm 1D Objects(First Fit Decreasing)");

        int n = 9;
        int[] a = {4, 1, 2, 5, 3, 2, 3, 6, 3};
        int size = 6;
        int[] sequence = sort(a, n);
        binPacking(sequence);
    }
}