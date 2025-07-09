// Demonstrate member functions of atomic types
#include <iostream>
#include <atomic>
#include <thread>
#include <mutex>
#include <vector>

// SAMPLE1
void basicAtomicOperations()
{
  std::atomic<int> x = 0;
	std::cout << "After initialization: x = " << x << '\n';

	// Atomic assignment to x
	x = 2;

	// Atomic assignment from x. y can be non-atomic
	int y = x;

	std::cout << "After assignment: x = " << x << ", y = " << y << '\n';

	x.store(3);
	std::cout << "After store: x = " << x.load() << '\n';

	std::cout << "Exchange returns " << x.exchange(y) << '\n';
	std::cout << "After exchange: x = " << x << ", y = " << y << '\n';

}

// SAMPLE2
std::mutex g_mtx;

void task(int n) {
	std::lock_guard<std::mutex> lock(g_mtx);
	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section
}

// SAMPLE3
// Use std::atomic_flag to implement a spin lock which protects a critical section
// The atomic_flag must be initialized as false
std::atomic_flag lock_cout = ATOMIC_FLAG_INIT;

void task3(int n)
{
	// test_and_set()
	// Returns true if another thread set the flag
	// Returns false if this thread set the flag
	while (lock_cout.test_and_set()) {}

	// Start of critical section
	// do some work
	using namespace std::literals;
	std::this_thread::sleep_for(50ms);
	std::cout << "I'm a task with argument " << n << '\n';
	// End of critical section

	// Clear the flag, so another thread can set it
	lock_cout.clear();
}

int main()
{

  // SAMPLE1
  basicAtomicOperations();

  // SAMPLE2
  std::vector<std::thread> threads2;

	for (int i = 1; i <= 10; ++i)
	    threads2.push_back(std::thread(task, i));

	for (auto& thr : threads2)
		thr.join();

  // SAMPLE3
  std::vector<std::thread> threads3;

	for (int i = 1; i <= 10; ++i)
	    threads3.push_back(std::thread(task3, i));

	for (auto& thr : threads3)
		thr.join();

  return 0;
}
