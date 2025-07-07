// Example of passing a std::thread object to a function
#include <thread>
#include <iostream>

// The task function
void hello() {
	using namespace std::literals;
	std::this_thread::sleep_for(1s);
	std::cout << "hello: Hello, Thread!\n";
}

// Function taking a thread object as argument
// The object must be moved into the argument
void func(std::thread thr) {
	std::cout << "Move: Received thread with ID " << thr.get_id() << std::endl;

	// The function argument now "owns" the system thread
	// It is responsible for calling join()
	thr.join();
}

// Function returning a std::thread object
std::thread func() {
	// Start the thread
	std::thread thr(hello);

	// Return a local variable
	return thr;

	// Return a temporary object
	// return std::thread(hello);
}

// Task function
void helloException() {
	try {
		// Throw an exception
		throw std::exception();
	}
	catch (std::exception& e) {
		std::cout << "Exception caught: " << e.what() << '\n';
	}
	std::cout << "helloException: Hello, Thread!\n";
}

// Task function
void helloUncaughtException() {
	throw std::exception();

	std::cout << "helloUncaughtException: Hello, Thread!\n"; // this line ignored
}

// wrapper for uncaught exception
void wrapper() {
  try {
    helloUncaughtException();
  }
  catch(const std::exception& e) {
    std::cout << "Wrapper: Uncaught Exception recovered: " << e.what() << '\n';
  }
}

int main() {
	// std::thread is a move-only object
	std::thread thr1(hello);
	// Display the child thread's ID
	std::cout << "Hello thread 1 has ID " << thr1.get_id() << '\n';

  // Call a function which return an std::thread object
	std::thread thr2 = func();

	// Pass a temporary object
	func(std::thread(hello)); // pass by move (rvalue reference)

  // Create an std::thread object
	std::thread thr4(helloException);

  // Create an std::thread object which throws an uncaught exception
  // the below leads to runtime error, here exception is not handled.
	// try {
	// 	std::thread thr5{helloUncaughtException};
  //   // wait for the thread 5 to complete
	// 	thr5.join();
	// }
	// catch (std::exception& e) {
	// 	std::cout << "Uncaught Exception caught: " << e.what() << '\n';
	// }

  std::thread thr5{wrapper};

 	// Pass a named object using std::move()
	func(std::move(thr1)); // pass by move (rvalue reference)

	std::cout << "Received thread 2 with ID " << thr2.get_id() << '\n';
	// Our thr object now "owns" the system thread
	// It is responsible for calling join()
	thr2.join();
  //wait for a thread 4 to complete
  thr4.join();
  //wait for a thread 4 to complete
  thr5.join();

  return 0;
}