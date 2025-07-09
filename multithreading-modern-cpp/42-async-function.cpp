// Hello world using std::async()
#include <future>
#include <iostream>
#include <thread>
#include <exception>

using namespace std::literals;

// Task function
void hello()
{
    std::cout << "Hello, Async!\n";
}

// ACTIVITY 2
// Task which returns a value
int produce()
{
	int x = 42;
	std::this_thread::sleep_for(2s);

	// Some code which may throw an exception
	if (1) {
		throw std::out_of_range("Oops");
	}

	std::cout << "Produce returning " << x << '\n';
	return x;
}

// ACTIVITY 3
// Task which returns a value
unsigned long long fibonacci(unsigned long long n)
{
	if (n <= 1)
		return 1;
	return fibonacci(n-1) + fibonacci(n-2);
}

int main()
{
	// Call std::async() to perform the task
  std::future<void> f = std::async(hello);

  // ACTIVITY 2
  // Call async() and store the returned future
	auto result = std::async(produce);

	// Get the result - may throw an exception
	std::cout << "Future calling get()...\n";
	try {
		int x = result.get();				           // Get the result
		std::cout << "Future returns from calling get()\n";
		std::cout << "The answer is " << x << '\n';
	}
	catch(std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}

  // ACTIVITY 3
  std::cout << "Calling fibonacci(44)\n";
	// Call async() and store the returned future
	auto result01 = std::async(fibonacci, 44);

	while (result01.wait_for(1s) != std::future_status::ready) {
		std::cout << "Waiting for the result...\n";
		// Do some other work
		// ...
	}
	// Call get() when we are ready
	std::cout << result01.get() << std::endl;

  return 0;
}