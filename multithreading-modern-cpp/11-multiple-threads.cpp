// Example of starting multiple threads
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

void func(int num)
{
	// Add a delay
	std::this_thread::sleep_for(std::chrono::seconds(num));
	std::cout << "Hello from thread " << num << '\n';
}

int main() {
	// Start 3 threads
	std::cout << "Starting 3 threads:\n";
  std::vector<std::thread> vec;
  for(int i = 0; i < 3; i++) {
    vec.push_back(std::thread{func, i});
  }

	// Wait for the threads to finish
  for(auto& thr : vec) {
    thr.join();
  }
  vec.clear();

  return 0;
}