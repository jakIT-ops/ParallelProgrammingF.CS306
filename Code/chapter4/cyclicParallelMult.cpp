#include <iostream>
#include <cstdint> // std::cout
// uint64_t
#include <vector> // std::vector
#include <thread> // std::thread (not used yet)
#include "../include/hpc_helpers.hpp" // custom timers
// initialize A as lower triangular matrix
// simulating prefix summation and vector x
// with consecutive values (0, 1, 2, 3, ...)

template <
typename value_t, 
typename index_t>
void init(
    std::vector<value_t>& A,
    std::vector<value_t>& x,
    index_t m,
    index_t n) {
    for (index_t row = 0; row < m; row++)
        for (index_t col = 0; col < n; col++)
            A[row*n+col] = row >= col ? 1 : 0;
    
    for (index_t col = 0; col < n; col++)
        x[col] = col;
}

template <
    typename value_t,
    typename index_t>
void cyclic_parallel_mult(
    std::vector<value_t>& A, // linear memory for A
    std::vector<value_t>& x, // to be mapped vector
    std::vector<value_t>& b, // result vector
    index_t m,               // number of rows
    index_t n,               // number of cols
    index_t num_threads=8) { // number of threads p

    // this  function  is  called  by the  threads
    auto cyclic = [&] (const index_t& id) -> void {

        // indices are incremented with a stride of p
        for (index_t row = id; row < m; row += num_threads) {
            value_t accum = value_t(0);
	    for (index_t col = 0; col < n; col++)
                accum += A[row*n+col]*x[col];
            b[row] = accum;
        }
    };

    // business as usual
    std::vector<std::thread> threads;

    for (index_t id = 0; id < num_threads; id++)
        threads.emplace_back(cyclic, id);

    for (auto& thread : threads)
        thread.join();
}



int main(int argc, char* argv[]) {

    const uint64_t n = 1UL << 8;
    const uint64_t m = 1UL << 8;
    
    TIMERSTART(overall)
    
    TIMERSTART(alloc)
    std::vector<uint64_t> A(m*n);
    std::vector<uint64_t> x(n);
    std::vector<uint64_t> b(m);
    TIMERSTOP(alloc)
    
    TIMERSTART(init)
    init(A, x, m, n);
    TIMERSTOP(init)
    
    TIMERSTART(mult)
    cyclic_parallel_mult(A, x, b, m, n);
    TIMERSTOP(mult)
    
    TIMERSTOP(overall)
    // check if summation is correct
    for (uint64_t index = 0; index < m; index++)
        if (b[index] != index*(index+1)/2)
            std::cout << "error at position "<< index << std::endl;
}