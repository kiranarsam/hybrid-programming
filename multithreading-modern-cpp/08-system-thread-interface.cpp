// Example of pausing a thread
#include <thread>
#include <iostream>

using namespace std::literals;

void hello() {
	//std::this_thread::sleep_for(std::chrono::seconds(2)); // this, requires chrono header
	std::this_thread::sleep_for(1s); // doesn't chrono header
	std::cout << "Hello, Thread!\n";
  std::cout << "Hello from thread with ID: " << std::this_thread::get_id() << '\n';
}

int main() {
  // Display the main thread's ID
	std::cout << "Main thread has ID: " << std::this_thread::get_id() << '\n';
	// Create an std::thread object
	std::thread thr1(hello);
	// Display the child thread's ID
	std::cout << "Hello thread has ID: " << thr1.get_id() << '\n';
  // Display the child thread's native handle
	std::cout << "Hello thread has native handle " << thr1.native_handle() << '\n';


	// Wait for the thread 1 to complete
	thr1.join();
	// Display the child thread's ID again
	std::cout << "Hello thread again after .join() now has ID: " << thr1.get_id() << '\n';
	// Display the child thread's native handle again
	std::cout << "Hello thread now has native handle " << thr1.native_handle() << '\n';

  return 0;
}