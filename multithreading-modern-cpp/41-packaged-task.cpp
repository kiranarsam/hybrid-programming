// Packaged task example
// Executes the task in the current thread
#include <future>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std::literals;

void basicPackagedTask()
{
	// Packaged task object
	// The callable object is a lambda expression
	// It takes int and int arguments and returns int, syntax: int(int, int)
	std::packaged_task<int(int, int)> ptask([](int a, int b) {
		std::this_thread::sleep_for(1s);
		return a + b;
		});

	// The promise object is an std::promise<int>
	// Get the future associated with it
	std::future<int> fut = ptask.get_future();

	// Invoke the packaged task in this thread
	ptask(6, 7);

	std::cout << "Waiting for result\n";

	// Call get() to receive the result of the packaged task
	std::cout << "6 + 7 is " << fut.get() << '\n';
}

void threadBasedPackagedTask()
{
  // Packaged task object
	std::packaged_task<int(int, int)> ptask([](int a, int b) {
		std::this_thread::sleep_for(1s);
		return a + b;
		});

	// The promise object is an std::promise<int>
	// Get the future associated with it
	auto fut = ptask.get_future();

	// Start a new thread
	// The packaged task will be its entry point
	std::thread thr(std::move(ptask), 6, 7);

	std::cout << "Waiting for result\n";

	thr.join();
  std::cout << "6 + 7 is " << fut.get() << '\n';
}

int main()
{
  basicPackagedTask();

  threadBasedPackagedTask();

  return 0;
}