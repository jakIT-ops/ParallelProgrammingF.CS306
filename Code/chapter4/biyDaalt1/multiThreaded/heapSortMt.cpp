#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <thread>

#include "../../include/hpc_helpers.hpp"

void heapify(int * arr, int n, int i)
{
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
 
void printArray(int * arr, int n)
{
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";
    std::cout << "\n";
}
 
int main()
{
    const uint64_t num_threads = 4;
	const uint64_t M = 1 << 18;

    std::vector<std::thread> threads;
    printf("heapSort Multi Thread\n");

	TIMERSTART(alloc_memory)
    int *A = (int*)malloc(M * sizeof(int));
    TIMERSTOP(alloc_memory)

    TIMERSTART(init)
   	for (uint64_t i = 0; i < M; i++)
        A[i] = rand() % M;  
    TIMERSTOP(init)
 
    //int n = sizeof(A) / sizeof(A[0]);
 
    TIMERSTART(sorting)
    for(uint64_t id = 0; id < num_threads; id++)
        threads.emplace_back(
            std::thread(heapSort, A, M));
 	TIMERSTOP(sorting)

    TIMERSTART(join)
    for(auto& thread: threads)
        thread.join();
    TIMERSTOP(join)

 	TIMERSTART(free_memory)
	free(A);    
    TIMERSTOP(free_memory)
}