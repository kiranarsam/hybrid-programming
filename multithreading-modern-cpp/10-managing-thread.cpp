#include <thread>
#include <iostream>
#include <chrono>

// Callable object - thread entry point
void helloDetach() {
	std::cout << "helloDetach: Hello, Thread!\n";
}

// Uses a wrapper class for std::thread
// Ensures safe destruction when an exception is throw
class ThreadGaurd
{
private:
	std::thread thr;
public:
	// Constructor takes rvalue reference argument (std::thread is move-only)
	explicit ThreadGaurd(std::thread&& thr): thr(std::move(thr))
  {
	}

	// Destructor - join the thread if necessary
	~ThreadGaurd()
	{
		if (thr.joinable()) {
			thr.join();
    }
	}

  // Deleted copy operators prevent copying
	ThreadGaurd(const ThreadGaurd&) = delete;
  // The move assignment operator is not synthesized
	ThreadGaurd& operator=(const ThreadGaurd&) = delete;
};

void func()
{
  std::cout << "func: thread id: " << std::this_thread::get_id() << std::endl;
}

int main(int argc, char **argv) {
	// Create an std::thread object
	std::thread thr1(helloDetach);
	// Detach the child thread (thread 1)
	thr1.detach();
	// Continue executing without waiting for the child thread
  std::this_thread::sleep_for(std::chrono::seconds(2)); // check detached thread is executed or not.

  try {
		std::thread thr2(func);
		ThreadGaurd tguard1{std::move(thr2)}; // move thread object

		ThreadGaurd tguard2{std::thread(func)}; // thread temporary object

		// Code which might throw an exception
		throw std::exception();

	} // Calls ~thread_guard followed by ~thread
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}

  // Safely destroying an thread object when exception occured
  std::thread thr3(func);
  try {
		// Code that might throw an exception
		throw std::exception();
		// No exception if we got here - call join() as usual
		thr3.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
		thr3.join(); // Call join() before thr's destructor is called
	}

  // Unsafe for the thread object.
  // below thread is not safely distructing.
  try {
		// Create an std::thread object
		// std::thread thr4(func);
		// Code that might throw an exception
		throw std::exception();
    // No exception if we got here - call join() as usual
		// thr4.join();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught th4: " << e.what() << '\n';
    // Here, thr4 gives, runtime error
    // terminate called without an active exception
    // Aborted (core dumped)
	}

  // Below code executes C++20
  // Safely handles, destroying thread if any exeception occured
  try {
		// Create an std::jthread object
		std::jthread jthr(func);
		// Code that might throw an exception
		throw std::exception();
		// std::jthread's destructor will call join() if necessary
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}

  return 0;
}

/**
 * For C++20
 * g++ -std=c++20 program.cpp -o prog
 */
