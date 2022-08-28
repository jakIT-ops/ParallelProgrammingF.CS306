#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <vector>
#include <omp.h>

#include "../../include/hpc_helpers.hpp"

void heapify(int * arr, int n, int i){

    int largest = i; 
    int l = 2 * i + 1; 
    int r = 2 * i + 2; 
    
    if (l < n && arr[l] > arr[largest])
        largest = l;
    
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
 
        heapify(arr, n, largest);
    }
}
 
void heapSort(int * arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}
 
int main() {

	const uint64_t M = 1 << 22;

	// Alloc memory
	int *A = (int*)malloc(M * sizeof(int));

	// init
	for(uint64_t i = 0; i < M; i++)
		A[i] = rand() % M;

    omp_set_num_threads(8);
	TIMERSTART(sorting)
	heapSort(A,M);
	TIMERSTOP(sorting)

	for(int i = 0; i < 10; i++)
		printf("%d\n", A[i]);
	
	TIMERSTART(free_memory)
	free(A);
	TIMERSTOP(free_memory)

	return 0;
}



















