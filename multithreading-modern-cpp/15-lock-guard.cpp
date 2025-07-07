// Use std::lock_guard to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex g_mtx;

// using std::lock_guard, to release mtx lock, automatically.
void task1(const std::string& str, int id)
{
	for (int i = 0; i < 5; ++i) {
		try {
			// Create an std::lock_guard object
			// This calls print_mutex.lock()
			std::lock_guard<std::mutex> lck_guard(g_mtx);

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;
			// Critical section throws an exception
			throw std::exception();
			// End of critical section
			std::this_thread::sleep_for(50ms);
		}  // Calls ~std::lock_guard
		catch (std::exception& e) {
			std::cout << "Thread ID: " << id << " Exception caught: " << e.what() << '\n';
		}
	}
}

// Using std::mutex, to lock and unlock explicitly.
void task2(const std::string& str, int id)
{
	for (int i = 0; i < 5; ++i) {
		try {
			// Lock the mutex before the critical section
			g_mtx.lock();

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;
			// Critical section throws an exception
			throw std::exception();
			// End of critical section

      // never gets called
      g_mtx.unlock();
			std::this_thread::sleep_for(50ms);
		}  // Calls ~std::lock_guard
		catch (std::exception& e) {
			std::cout << "Thread ID: " << id << " Exception caught: " << e.what() << '\n';
      g_mtx.unlock(); // this will properly, unlock the mtx safely from the exception in the thread
		}
	}
}

int main()
{
  // Using lock_guard to lock and unlock the mutex
	std::thread thr1(task1, "abc", 1);
	std::thread thr2(task1, "def", 2);
	std::thread thr3(task1, "xyz", 3);

	thr1.join(); thr2.join(); thr3.join();

  std::this_thread::sleep_for(50ms);

  // Using g_mtx to lock and unlock
  std::thread thr4(task2, "abc", 4);
	std::thread thr5(task2, "def", 5);
	std::thread thr6(task2, "xyz", 6);

  // Threads are unable to join(), due to g_mtx is not releasing from first acquired thread
  // in task2().
  // Use g_mtx.unlock() in the exception handler

	thr4.join(); thr5.join(); thr6.join();

  return 0;
}