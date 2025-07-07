// First program with std::thread
#include <thread>
#include <iostream>

// Callable object - thread entry point
void helloThread() {
	std::cout << "Hello, Thread!\n";
}

// Functor class with overloaded () operator
class Hello {
	public:
	void operator()() { std::cout << "Hello, Functor Thread!\n"; }
};

int main() {
	// Create an std::thread object
	// Pass the entry point function to the constructor
	std::thread thr1(helloThread);

  // Use a lambda expression as the thread's entry point
	std::thread thr2([]() {
		std::cout << "Hello, Lambda Thread!\n";
	});


  // Create an object of the functor class
	Hello hello;

	// Pass the functor object to std::thread's constructor
	std::thread thr3(hello);

	// Wait for the thread 1 to complete
	thr1.join();

  // Wait for the thread 2 to complete
 	thr2.join();

	// Wait for the thread 3 to complete
	thr3.join();

  return 0;
}