#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

int main() {
	//std::mutex m;
	//std::condition_variable c;
	 std::vector<std::thread> thread;
  
	//bool done = false;
	auto child = [&]() -> void { // lambda function
    	// unlock
		//std::unique_lock<std::mutex> unique_lock(m);
        //do {
        //    c.wait(unique_lock);
        //} while(!done);

		std::cout << "child1D" << std::endl;
	};

	std::thread thread(child);
	thread.detach();
	std::cout << "parent" << std::endl;
	// lock 
	//std::lock_guard<std::mutex> lock_guard(m); 
	//done = true;
	//c.notify_one();
	//thread.join();
}