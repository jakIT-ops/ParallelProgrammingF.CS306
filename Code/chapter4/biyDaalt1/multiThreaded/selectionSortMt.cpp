#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>

#include "../../include/hpc_helpers.hpp"

const uint64_t M = 1 << 18;

void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int * arr, uint64_t id)
{
	int i, j, min_idx;
	//std::cout << "Hello from thread: " << id << std::endl;
	for(i = 0; i < M-1; i++){
		min_idx = i;
		for(j = i+1; j < M; j++)
			if(arr[j] < arr[min_idx])
				min_idx = j;

		swap(&arr[min_idx], &arr[i]);
	}
}

void printArray(int arr[])
{
	int i;
	std::cout<<std::endl;
	for(i = 0; i < M; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
}

int main(){

	const uint64_t num_threads = 4;

    std::vector<std::thread> threads;
    
	printf("selectionSort Multi Thread\n");

    TIMERSTART(alloc_memory)
    int *A = (int*)malloc(M * sizeof(int));
    TIMERSTOP(alloc_memory)

    TIMERSTART(init)
   	for (uint64_t i = 0; i < M; i++)
        A[i] = rand() % M;   // 0 - 99 numbers
    TIMERSTOP(init)

    //printArray(A);

    TIMERSTART(sorting)
    for(uint64_t id = 0; id < num_threads; id++)
    	threads.emplace_back(
    		std::thread(selectionSort, A, id));
    TIMERSTOP(sorting)

    TIMERSTART(join)
  	for(auto& thread: threads)
    	thread.join();
    TIMERSTOP(join)

    //printArray(A);

    TIMERSTART(free_memory)
	free(A);    
    TIMERSTOP(free_memory)
   
}