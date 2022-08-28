#include <iostream>
#include <thread>
#include <atomic>

void run_code() {

	std::atomic<bool> x(false);
	std::cout << "atomic boolean is implemented lock free - "
		<< (x.is_lock_free() ? "yes" : "no") << std::endl;

	std::atomic<bool> y(true);

	// store operations 
	x.store(false);
	x.store(y); // true

	// load operations
	std::cout<<"value of the atomic bool y - "<< y.load() << std::endl;

	// exchange operation
	bool z = x.exchange(false); // z = x not x = z

	std::cout << "current value of atomic bool x - " << x.load() << std::endl;
	std::cout << "previous value of atomic bool x - " << z << std::endl;

	std::cout << std::endl;	
}

int main(){
	run_code();
	return 0;
}