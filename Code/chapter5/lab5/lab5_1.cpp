#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <thread>
#include <atomic>
#include "../include/hpc_helpers.hpp"

// void init(float * data, uint64_t length) {

//     std::mt19937 engine(42);
//     std::uniform_real_distribution<float> density(-1, 1);

//     for (uint64_t i = 0; i < length; i++)
//         data[i] = density(engine);
// }

/*
    N urttai float massiv dahi hamgiin ih elementiig tootsoolog paralllel
    program

*/

// Atomic Parallel-reduction using compare-and-swap
/*
    function cas(p: pointer to int, old: int, new: int) is
    if *p ≠ old
        return false

    *p ← new

    return true
*/

template<typename T>
void max_elem(std::atomic<T>& maximum_value, T const& value) noexcept
{
        T prev_value = maximum_value;
        while(prev_value < value && !maximum_value.compare_exchange_weak(prev_value, value))
        {}    
}

int main() {

	std::vector<std::thread> threads;

	const uint64_t num_thread = 8;
	const uint64_t n =  1 << 10; // 1024

	int *A = (int*)malloc(n*sizeof(int));

    // srand(time(NULL));
    
    for(uint64_t i = 0; i<n; i++){
        // A[i] = float(5+rand() % (150+1-5)) / 100;
        A[i] = rand() % n; 
    }

    for(uint64_t j = 0; j <n; j++){
        std::cout<< A[j]<<std::endl;
    }

    // auto mutex_max =
    //     [&] (volatile std::atomic<uint64_t>* counter,
    //         const auto& id) -> void {

    //         for (uint64_t i = id; i < n; i += num_thread)
    //             if(i > *counter)
    //                 *counter = i;
    //     }

    auto atomic_max =
        [&] (volatile std::atomic<uint64_t>* max,
            const auto& id) -> void {

            for (uint64_t i = id; i < n; i += num_thread) {
                // std::atomic<float> value = A[i-1];
                // auto previous = value->load();
                std::atomic<uint64_t> previous = A[i-1];
                std::atomic<uint64_t> current = A[i];
                while(previous < current && !max->compare_exchange_weak(previous, current)) {}
            }
        };

    //TIMERSTART(incorrect_max)
    // std::atomic<uint64_t> amximum_value(0);
    // threads.clear();
    // for (uint64_t id = 0; id < num_threads; id++)
    //     threads.emplace_back(false_max, &maximum_value, id);
    // for (auto& thread : threads)
    //     thread.join();
    // TIMERSTOP(incorrect_max)

    TIMERSTART(atomic_max)
    std::atomic<int> max(0);
    threads.clear();
    for (uint64_t id = 0; id < num_thread; id++)
        threads.emplace_back(atomic_max, &max, id);
    for (auto& thread : threads)
        thread.join();
    TIMERSTOP(atomic_max)

    // std::cout << false_counter << " " << " atomic_max " << max << std::endl;
}