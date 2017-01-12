package nonrecursivemergesortDivideAndConquer;

/**
 *
 * @author FRISCA
 */
public class MergesortRecord {
    private boolean sorted; //Indicates if the first and second half of the array have already been sorted 
    private int first;
    private int last;

    public MergesortRecord(boolean s, int f, int l){
        sorted = s;
        first = f;
        last = l;
    }

    public  int getfirst()   {
        return first;
    }

    public boolean getsorted()   {
        return sorted;
    }

    public  int getlast()   {
        return last;
    }

    public void print(){
        System.out.println(sorted+" "+first+" "+last);
    }
}
