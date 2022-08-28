// atomic <*>
// neither copy assignable nor copy constructible.
// Can assign non atomic Booleans and can be construct using non atomic Booleans

#include <iostream>
#include <thread>
#include <atomic>

void run_code(){

	std::atomic<bool> flag_1;
	std::cout << "flag_1 = " << flag_1 << std::endl;

	////cannot copy construct
	// std::atomic<bool> flag_2 (flag_1);

	////cannot copy assignable
 	// std::atomic<bool> flag_3 = flag_1;
	
	// construct using non atomic boolean value
	bool non_atomic_bool = true;
	std::atomic<bool> flag_4(non_atomic_bool);
	std::cout << "flag_4 = " <<flag_4 <<std::endl;
 
	// assing non atomic boolean boolean value
	std::atomic<bool> flag_5 = non_atomic_bool;
	std::cout<<"flag_5 = " << flag_5 << std::endl;

}

int main() {

	run_code();	
	return 0;
}
