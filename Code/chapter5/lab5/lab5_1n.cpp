#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <atomic>
#include <mutex>
#include "../include/hpc_helpers.hpp"

// Atomic Parallel-reduction using compare-and-swap
/*
    function cas(p: pointer to int, old: int, new: int) is
    if *p ≠ old
        return false

    *p ← new

    return true
*/

int CAS(int *ptr,int oldvalue,int newvalue)
{
   int temp = *ptr;
   if(*ptr == oldvalue)
       *ptr = newvalue;
   return temp;
}

int main( ) {

    std::mutex mutex;
    std::vector<std::thread> threads;
    const uint64_t num_threads = 10;
    const uint64_t num_iters = 100'000'000; 
    // 1 thread = 10,000,000

    // WARNING: this closure produces incorrect results
    auto mutex_max =
        [&] (volatile uint64_t* max,
            const auto& id) -> void {

            for (uint64_t i = id; i < num_iters; i += num_threads){
                std::lock_guard<std::mutex> lock_guard(mutex);
                if(i > *max){
                    *max = i;
                }
            }
                    
        };

    auto atomic_max =
        [&] (volatile std::atomic<uint64_t>* max_value,
            const auto& id) -> void {

            for (uint64_t i = id; i < num_iters; i += num_threads) {
                auto previous = max_value->load();
                while (previous < i && !max_value->compare_exchange_weak(previous, i)) {}
            }
        };

    // mutex
    TIMERSTART(mutex_max)
    uint64_t m_max = 0;
    threads.clear();
    for (uint64_t id = 0; id < num_threads; id++) // 10
        threads.emplace_back(mutex_max, &m_max, id);
    for (auto& thread : threads)
        thread.join();
    TIMERSTOP(mutex_max)

    // ATOMIC
    TIMERSTART(atomic_max)
    std::atomic<uint64_t> a_max(0);
    threads.clear();
    for (uint64_t id = 0; id < num_threads; id++)
        threads.emplace_back(atomic_max, &a_max, id);
    for (auto& thread : threads)
        thread.join();
    TIMERSTOP(atomic_max)

    std::cout << m_max << " " << a_max << std::endl;
}   