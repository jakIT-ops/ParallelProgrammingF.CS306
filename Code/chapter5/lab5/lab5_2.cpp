#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <omp.h>

#include "../include/hpc_helpers.hpp"

int main() {

	const uint64_t num_threads = 10;
	const uint64_t n = 100'000'000;
	omp_set_num_threads(num_threads);
	

	TIMERSTART(alloc)
	float *A = (float*)malloc(n*sizeof(float));
	TIMERSTOP(alloc)

	float max_val = 0;

	TIMERSTART(init)
	#pragma omp parallel for
	for(uint64_t i = 0; i < n; i++)
		A[i] = float(5 + rand() % (150 + 1 - 5 )) / 100; 
		// 0 - 1 random float numbers
	TIMERSTOP(init)

	TIMERSTART(max)
	#pragma omp parallel for reduction(max:max_val) 
	for(uint64_t i = 0; i < n; i++)
		max_val = max_val > A[i] ? max_val : A[i];
		// max = operator
		// max_val = reduction variable
	TIMERSTOP(max)
	
	// for(uint64_t j = 0; j <10; j++){
 //        std::cout<< A[j]<<std::endl;
 //    }

    std::cout<<"max val: "<< max_val <<std::endl;
}

