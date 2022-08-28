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

void selectionSort(int * arr, uint64_t n)
{
	int i, j, min_idx;

	for(i = 0; i < n-1; i++){
		min_idx = i;
		for(j = i+1; j < n; j++)
			if(arr[j] < arr[min_idx])
				min_idx = j;

		swap(&arr[min_idx], &arr[i]);
	}
}

void printArray(int arr[], int size)
{
	int i;
	for(i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

int main(){
	const uint64_t M = 1 << 18;

	printf("selectionSort Single thread\n");

    TIMERSTART(alloc_memory)
    int *A = (int*)malloc(M * sizeof(int));
    TIMERSTOP(alloc_memory)
    
    TIMERSTART(init)
   	for (uint64_t i = 0; i < M; i++)
        A[i] = rand() % 100;   // 0 - 99 numbers
    TIMERSTOP(init)
/*
    for(uint64_t i = 0; i<10; i++){
    	printf("%d", A[i]);
    }
*/
    TIMERSTART(sorting)
    selectionSort(A, M);
    TIMERSTOP(sorting)
/*
    for(uint64_t i = 0; i<10; i++){
    	printf("%d", A[i]);
    }
*/
    TIMERSTART(free_memory)
	free(A);    
    TIMERSTOP(free_memory)
}