#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>

std::mutex g_mtx;

// Shared variable
int g_x = 0;

void write()
{
	std::lock_guard<std::mutex> lock(g_mtx);

	// Start of critical section
	++g_x;
	// End of critical section
}

void read()
{
	std::lock_guard<std::mutex> lock(g_mtx);

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

  // 42 threads: 40 reads and 2 write operations on global shared data bw threads
	for (auto& thr : threads)
		thr.join();

  std::cout << "g_x: " << g_x << std::endl;

  return 0;
}