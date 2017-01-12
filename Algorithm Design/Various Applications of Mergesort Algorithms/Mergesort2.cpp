  #include <iostream>
  #include <time.h>
  using namespace std;
  #define BILLION 1000000000L

  void printList(int a[], int sz){
    for (int i = 0; i < sz; i++) cout << a[i] << " ";
      cout << endl;
  }

  void merge2(int a[], const int low, const int mid, const int high){

    int i, j, k;
    int *temp = new int[high-low+1];

    i = low; j = mid+1; k = 0;
    
    while(i <= mid && j <= high){
      if(a[i] <= a[j]) {
        temp[k] = a[i];
        i++;
      }
      else { 
        temp[k] = a[j];  
        j++;
      }
      k++;
    }

    if(i > mid){ 
      for(int x=j; x <= high; x++){
        temp[k] = a[x];
        k++;
      }
    }
    else {  
      for(int x=i; x <= mid; x++){
        temp[k] = a[x];
        k++;
      }
    }
    
    for(int x=0; x<=high-low; x++){
      a[x+low] = temp[x];
    }
    delete[] temp;
  }

  void mergesort2(int a[], const int low, const int high){
    if(low < high)
    {
      int mid = (low + high)/2;
      mergesort2(a, low, mid);
      mergesort2(a, mid+1, high);
      merge2(a, low, mid, high);
    }
  }

  int main(){   

  	struct timespec start, end;
  	double diff;
  	clock_gettime(CLOCK_MONOTONIC, &start);			// start recording time
  //  int a[] ={12,11,10,9,8,7,6,5,4,3,2,1}; //Worst case
    int a[] ={1,2,3,4,5,6,7,12,10,8,11,9};   //Average case
  //  int a[] ={1,2,3,4,5,6,7,8,9,10,11,12};   //Best case
    int arraySize = sizeof(a)/sizeof(int);
    printf("The Array is:\n");
    printList(a, arraySize);
    
    mergesort2(a, 0, (arraySize-1) );   
    printf("\nThe Sorted Array is:\n");
    printList(a, arraySize);  
    clock_gettime(CLOCK_MONOTONIC, &end); //get the end time
    diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec; 
    printf("\nThe Average case takes  %d Microseconds\n", (int) diff/1000);

    return 0;
  }