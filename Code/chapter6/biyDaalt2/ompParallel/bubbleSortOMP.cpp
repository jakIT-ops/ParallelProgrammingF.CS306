#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <omp.h>

#include "../../include/hpc_helpers.hpp"

void swap(int *xp, int *yp) {

	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void bubbleSort(int* arr, int size){

	int i, j;
	#pragma omp parallel for
	for(i = 0; i < size - 1; i++)
		for(j = 0; j < size - i - 1; j++)
			if(arr[j] > arr[j+1])
				swap(&arr[j], &arr[j+1]);
}

int main(){

	const uint64_t M = 1 << 10;

	// Alloc memory
	int *A = (int*)malloc(M * sizeof(int));

	// init
	for(uint64_t i = 0; i < M; i++)
		A[i] = rand() % M;
	
	omp_set_num_threads(4);
	TIMERSTART(sorting)
	bubbleSort(A, M);
	TIMERSTOP(sorting)

	for(int i = 0; i < 10; i++)
		printf("%d\n", A[i]);
	
	TIMERSTART(free_memory)
	free(A);
	TIMERSTOP(free_memory)

	return 0;
}