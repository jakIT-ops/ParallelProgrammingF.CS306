#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include "../../include/hpc_helpers.hpp"

struct Compare { 
	int val;
	int index;
};

void selectionsort(int* arr, int size){
	
	for(int i = size - 1; i > 0; --i){
		
		struct Compare max;
		max.val = arr[i];
		max.index = i;
		#pragma omp parallel for
		for(int j = i - 1; j >= 0; --j){

			if(arr[j] > max.val){
				max.val = arr[j];
				max.index = j;
			}
		}
		int tmp = arr[i];
		arr[i] = max.val;
		arr[max.index] = tmp;
	}
}

int main() {

	const uint64_t M = 1 << 10;

	// alloc memory
	int *A = (int*)malloc(M * sizeof(int));

	// init
	for(uint64_t i = 0; i < M; i++)
		A[i] = rand() % M;

	omp_set_num_threads(4);
	TIMERSTART(SORTING)
	selectionsort(A, M);
	TIMERSTOP(SORTING)

	for(int i = 0; i < 10; i++)
		printf("%d\n", A[i]);

	TIMERSTART(free_memory)
	free(A);
	TIMERSTOP(free_memory)

	return 0;
}