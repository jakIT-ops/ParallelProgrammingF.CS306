#include <cstdlib>
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <thread>

#include "../../include/hpc_helpers.hpp"
 
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
        std::cout << arr[i] << " ";
    std::cout << endl;
}

int main()
{
    const uint64_t num_threads = 4;
    const uint64_t M = 1 << 18;
    std::vector<std::thread> threads;

    printf("bubbleSort Multi Thread\n");

    TIMERSTART(alloc_memory)
    int *A = (int*)malloc(M * sizeof(int));
    TIMERSTOP(alloc_memory)

    TIMERSTART(init)
    for (uint64_t i = 0; i < M; i++)
        A[i] = rand() % M;  
    TIMERSTOP(init)

    //int n = sizeof(A)/sizeof(A);
    
    TIMERSTART(sorting)
    for(uint64_t id = 0; id < num_threads; id++)
        threads.emplace_back(
            std::thread(bubbleSort, A, M));
    TIMERSTOP(sorting)

    TIMERSTART(join)
    for(auto& thread: threads)
        thread.join();
    TIMERSTOP(join)

    TIMERSTART(free_memory)
    free(A);    
    TIMERSTOP(free_memory)

    return 0;
}