// Use std::unique_lock to avoid scrambled output
// Find out what happens when an exception is thrown
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
#include <string>

using namespace std::literals;

std::mutex g_mtx;

void task1(std::string str)
{
    for (int i = 0; i < 5; ++i) {
      // Create an std::unique_lock object
      // This calls print_mutex.lock()
      std::unique_lock<std::mutex> lock(g_mtx);
      // Start of critical section
      std::cout << str[0] << str[1] << str[2] << std::endl;
      // End of critical section
      // Unlock the mutex
      lock.unlock();

      std::this_thread::sleep_for(50ms);
    } // Calls ~std::unique_lock
}

void task2(const std::string& str)
{
	for (int i = 0; i < 5; ++i) {
		try {
      // Create an std::unique_lock object
      // This calls g_mtx.lock()
      std::unique_lock<std::mutex> lock(g_mtx);

			// Start of critical section
			std::cout << str[0] << str[1] << str[2] << std::endl;

			// Throw an exception
				throw std::exception();
			// End of critical section

			// Unlock the mutex
			lock.unlock();

			std::this_thread::sleep_for(50ms);
		} // Calls ~std::unique_lock
		catch (std::exception& e) {
			std::cout << "Exception caught: " << e.what() << '\n';
		}
	}
}

int main()
{
	std::thread thr1(task1, "abc");
	std::thread thr2(task1, "def");
	std::thread thr3(task1, "xyz");

  std::thread thr4(task2, "lmn");
	std::thread thr5(task2, "opq");
	std::thread thr6(task2, "rst");

	thr1.join(); thr2.join(); thr3.join();
  thr4.join(); thr5.join(); thr6.join();

  return 0;
}