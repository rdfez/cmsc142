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

// input_case = [asc, desc, random]
// random = [rand1, rand2, rand3] (NULL for asc, desc)
void init(int a[], int n, int input_case, int random){
    int i;

    switch(input_case) {
        case 0:
            // ascending
            for(i=0;i<n;i++)
                a[i]=i+1;
            break;
        case 1:
             // descending
            for(i=0;i<n;i++)
                a[i]=n-i;
            break;
        case 2:
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

// print array
void output(int a[], int n){
    int i;
    
    for(i=0;i<n;i++)
        printf("%i\n", a[i]);
    printf("\n");
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
            } else break;
    }
}

// selection sort
void ssort(int a[], int n){
    int i,j;
    int min_index;

    for(i=0;i<n-1;i++) {
        min_index = a[i];
        for(j=i; j<n-1;j++)
            if(a[j]>a[j+1]) {
                min_index = j+1;
            } else break;
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

// heap sort

int main(int argc,char *argv[]){
    char *type = argv[1];
    int size = atoi(argv[2]);
    char *sort_algo = argv[2]; 
    // int n=10;
    int n=10000*(size);
    int a[n], i;
    clock_t t1, t2;
    
    // init(a,n,<input_case>,<random>)
    // @ <input_case> = [asc, desc, random]
    // @ <random> = seed no. = [rand1, rand2, rand3]
    
    // ascending
    if (type == "0")
        init(a,n,0,0);
    // descending
    else if (type == "1") 
        init(a,n,1,0);
    // random1
    else if (type == "2") 
        init(a,n,2,0);
    // random2
    else if (type == "3") 
        init(a,n,2,1);
    // random3
    else if (type == "4") 
        init(a,n,2,2);

    // output(a,n);

    t1 = clock();
    // sorting algorithms

    if (sort_algo == "isort")
        isort(a,n);
    else if (sort_algo == "shsort")
        shsort(a,n);
    else if (sort_algo == "msort")
        msort(a,n);
    else if (sort_algo == "bsort")
        bsort(a,n);
    else if (sort_algo == "ssort")
        ssort(a,n);
    else if (sort_algo == "qsort")
        qsort(a, n, sizeof(int), compare);
    else if (sort_algo == "qsort1")
        qsort1(a,0,n-1);
    else if (sort_algo == "hsort")
        qsort1(a,0,n-1);
    t2 = clock();

    // output(a,n);
    printf("%0.6f, ", (double) (t2-t1)/(double)(CLOCKS_PER_SEC));
}
