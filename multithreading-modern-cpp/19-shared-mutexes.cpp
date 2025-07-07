// Shared mutex example
// Requires C++17
// (for C++14, use std::shared_timed_mutex)
// The write thread uses an exclusive lock
// The read thread uses a shared lock
#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <chrono>
#include <vector>

std::shared_mutex g_sh_mtx;

// Shared variable
int g_x = 0;

void write()
{
  // Don't use shared_lock for write operations
	std::lock_guard<std::shared_mutex> lock(g_sh_mtx);

	// Start of critical section
	++g_x;
	// End of critical section
}

void read()
{
  // Shared lock, due to read operation
	std::shared_lock<std::shared_mutex> lock(g_sh_mtx);

	// Start of critical section
	using namespace std::literals;
	std::this_thread::sleep_for(100ms);
	// End of critical section
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	threads.push_back(std::thread(write));
	threads.push_back(std::thread(write));

	for (int i = 0; i < 20; ++i)
		threads.push_back(std::thread(read));

	for (auto& thr : threads)
		thr.join();

  std::cout << "g_x: " << g_x << std::endl;

  return 0;
}