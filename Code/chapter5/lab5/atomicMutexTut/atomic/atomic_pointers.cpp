/*
	Atomic<T*> is a atomic from of pointer.
	 * Does not means object pointed to is atomic
	 * But pointer it self is atomic
	* neither copy constructible nor copy assignable
	* But can be construct and assign usin non atomic value
*/

#include <iostream>
#include <thread>
#include <atomic>

void run_code() {
	int values[20];

	for(int i = 0; i< 20; i++)
		values[i] = i + 1;

	std::atomic<int*> x_pointer = values;
	std::cout <<"atomic integer pointer lock free ? " 
		<< (x_pointer.is_lock_free() ? "yes" : "no") << std::endl;

	int * y_pointer = values + 3;

	x_pointer.store(y_pointer);
	std::cout << "value referening to by pointer : " << *(x_pointer.load()) << std::endl;

	bool ret_val = x_pointer.compare_exchange_weak(y_pointer, values + 10);
	std::cout << "store operation successful : " <<(ret_val ? "yes" : "no")<< std::endl;
	std::cout << "new value pointer by atomic pointer : " << *x_pointer << std::endl;	
}

int main() {
	run_code();

	return 0;
}