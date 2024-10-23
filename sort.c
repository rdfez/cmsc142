#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

// print array
void output(int a[], int n){
    int i;

    for(i=0;i<n;i++)
        printf("%i ", a[i]);
    printf("\n");
}

// input_case = [asc, desc, random]
// random = [rand1, rand2, rand3] (NULL for asc, desc)
void init(int a[], int n, char *input_case, int random){
    int i;
    
    // ascending
    if (!strcmp(input_case, "asc")) { 
        for(i=0;i<n;i++)
            a[i]=i+1;
    // descending
    } else if (!strcmp(input_case, "desc")) {
        for(i=0;i<n;i++)
            a[i]=n-i;
    // random
    } else if (!strcmp(input_case, "rand")) { 
        // random
        // initialize array a
        for(i=0;i<n;i++)
            a[i]=i+1;
        
        // set seed
        switch(random){
            case 0:
                srand(7);
                break;
            case 1:
                srand(13);
                break;
            case 2:
                srand(17);
                break;
        }
        
        for(i=0;i<n;i++)
            swap(&a[i],&a[rand()%n]);
    }
}

// insertion sort
void isort(int a[], int n){
    int i,j;
    for(i=1;i<n;i++)
        for(j=i;j>0;j--)
            if(a[j-1]>a[j])
                swap(&a[j-1], &a[j]);
            else break;
}

// shell sort
void shsort(int a[], int n){
  int i,j,d;

  for(d=n/2;d>0;d/=2)
    for(i=d;i<n;i++)
        for(j=i;j>d-1;j-=d)
            if(a[j]<a[j-d])
                swap(&a[j],&a[j-d]);
            else break;
}

// merge sort
void merge (int a[], int n) {
    int i,j,k, mid=n/2, temp[n];

    for(i=0,j=mid,k=0;k<n;k++)
        temp[k]=(i<mid&&(j>=n||a[i]<a[j]))?a[i++]:a[j++]; //fill missing expression
    memcpy(a,temp,n*sizeof(int)); //copy a back to temp

}//end of merge

void msort (int a[], int n){
    if(n>1) {
        msort(a, n/2);
        msort(&a[n/2],n-n/2);
        merge(a,n);
    }
}//end of msort

// bubble sort
void bsort(int a[], int n){
    int i;
    int swapped = 1;

    while (swapped != 0) {
        swapped = 0;
        for(i=0;i<n-1;i++)
            if(a[i]>a[i+1]) {
                swap(&a[i], &a[i+1]);
                swapped = 1;
            }
    }
}

// selection sort
void ssort(int a[], int n){
    int i,j;
    int min_index;

    for(i=0;i<n-1;i++) {
        min_index = i;
        for(j=i+1; j<n;j++)
            if(a[j]<a[min_index]) {
                min_index = j;
            }
        if (min_index != i)
            swap(&a[i], &a[min_index]);
    }
}

// for own qsort
int partition(int a[], int low, int high){
    int pivot = a[high];
    int i = (low-1);

    for(int j=low;j<high;j++){
        if(a[j]<=pivot){
            i++;
            swap(&a[i],&a[j]);
        }
    }
    
    swap(&a[i+1],&a[high]);
    return (i+1);
}

// own qsort
void qsort1(int a[], int low, int high){
    if(low<high){
        int pi = partition(a,low,high);
        qsort1(a,low,pi-1);
        qsort1(a,pi+1,high);
    }
}

// for built in qsort
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

// for heap sort
void heapify(int arr[], int n, int i) {
    // indices for root, left child and right child
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // Find largest among root, left child and right child
    // if left is within bounds and greater than root
    if (left < n && arr[left] > arr[largest])
        largest = left;
    // if right is within bounds and greater than root
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // Swap and continue heapifying if root is not largest
    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

// heap sort
void hsort(int arr[], int n) {
    // Build max heap
    // i = non-leaf nodes (from n/2-1)
    for (int i=n/2-1; i>=0; i--)
        heapify(arr, n, i);
  
    // Heap sort
    for (int i=n-1; i>=0; i--) {
        // swap root (largest) with last element
        swap(&arr[0], &arr[i]);
    
        // Heapify root element to get highest element at root again
        heapify(arr, i, 0);
    }
}

int main(int argc,char *argv[]){
    char *type = argv[1];
    int size = atoi(argv[2]);
    char *sort_algo = argv[3];

    // int n=10;
    int n=10000*(size);
    int a[n], i;
    clock_t t1, t2;
    
    // init(a,n,<input_case>,<random>)
    // @ <input_case> = [asc, desc, random]
    // @ <random> = seed no. = [rand1, rand2, rand3]
    // ascending
    if (!strcmp(type, "asc"))
        init(a,n,"asc",NULL);
    // descending
    else if (!strcmp(type, "desc"))
        init(a,n,"desc",NULL);
    // random1
    else if (!strcmp(type, "rand1"))
        init(a,n,"rand",0);
    // random2
    else if (!strcmp(type, "rand2"))
        init(a,n,"rand",1);
    // random3
    else if (!strcmp(type, "rand3")) 
        init(a,n,"rand",2);
    
    // output(a,n);
    t1 = clock();

    // sort
    if (!strcmp(sort_algo,"isort"))
        isort(a,n);
    else if (!strcmp(sort_algo, "shsort"))
        shsort(a,n);
    else if (!strcmp(sort_algo, "msort"))
        msort(a,n);
    else if (!strcmp(sort_algo, "bsort"))
        bsort(a,n);
    else if (!strcmp(sort_algo, "ssort"))
        ssort(a,n);
    else if (!strcmp(sort_algo, "qsort"))
        qsort(a, n, sizeof(int), compare);
    else if (!strcmp(sort_algo, "qsort1"))
        qsort1(a,0,n-1);
    else if (!strcmp(sort_algo, "hsort"))
        hsort(a,n);
    
    t2 = clock();

    // output(a,n);
    printf("%0.6f, ", (double) (t2-t1)/(double)(CLOCKS_PER_SEC));
}
