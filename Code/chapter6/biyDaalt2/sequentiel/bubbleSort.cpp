#include <bits/stdc++.h>
#include <cstdint>
#include <cstdlib>
#include "../../include/hpc_helpers.hpp"

using namespace std;
 
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}
 
void bubbleSort(int * arr, int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)    
        for (j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}
 
void printArray(int * arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{

    const uint64_t M = 1 << 10;
    printf("bubbleSort Single Thread\n");

    TIMERSTART(alloc_memory)
    int *A = (int*)malloc(M * sizeof(int));
    TIMERSTOP(alloc_memory)

    TIMERSTART(init)
    for (uint64_t i = 0; i < M; i++)
        A[i] = rand() % M;  
    TIMERSTOP(init)

    //int n = sizeof(A)/sizeof(A);
    
    TIMERSTART(sorting)
    bubbleSort(A, M);
    TIMERSTOP(sorting)


    printf("%ld", sizeof(A));

    TIMERSTART(free_memory)
    free(A);    
    TIMERSTOP(free_memory)

    return 0;
}
