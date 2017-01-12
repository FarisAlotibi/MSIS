#include<stdio.h>
#include<stdlib.h>
void merge(int array[], int low, int mid, int high)
{
    int i, j, k;
    int n1 = mid - low + 1;
    int n2 = high - mid;
    // now we will c create temp arrays 
    int Left[n1], Right[n2];
    // firstly we will copy data to temp arrays Left[] and Right[]
    for (i = 0; i < n1; i++)
        Left[i] = array[l + i];

    for (j = 0; j < n2; j++)
        Right[j] = array[m + 1+ j];
    // The next step is to merge the temp arrays back into array[l..high]
    i = 0; 	//This is the initial index of first subarray
    j = 0; 	//This is the Initial index of second subarray
    k = l; 	// This is the Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (Left[i] <= Right[j])
        {
            array[k] = Left[i];
            i++;
        }
        else{
            array[k] = Right[j];
            j++;
        }
        k++;
    }
    // Now we will copy the remaining elements of Left[], if there are any 
    while (i < n1)
    {
        array[k] = Left[i];
        i++;
        k++;
    }
    // Next we will copy the remaining elements of Right[], if there are any
    while (j < n2)
    {
        array[k] = Right[j];
        j++;
        k++;
    }
}
                                                                                                        
// now we have, low is for left index and high is right index of the sub-array of array to be sorted 
void mergeSort(int array[], int low, int high)
{
    if (low < high)
    {
        
        int mid = l+(high-l)/2;
        // Now we will sort the first and second halves
        mergeSort(array, low, mid);
        mergeSort(array, mid+1, high);
        merge(array, low, mid, high);
    }
}
// This is the Function to print an array
void printArray(int B[], int size)
{
    int i;
    for (i=0; i < size; i++)
        cout<< B[i];
    cout<< "\n";
}
/* Now we have the driver program to test above functions */
int main()
{
    int array[] = {12, 13, 11, 3, 4, 5};
    int array_size = sizeof(array)/sizeof(array[0]);
    printf("The given array is \n");
    printArray(array, array_size);
    mergeSort(array, 0, array_size - 1);
    printf("\nThe Sorted array is \n");
    printArray(arry, arry_size);
    return 0;
}

