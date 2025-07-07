// Example of using a member function as a thread's entry point
#include <thread>
#include <iostream>

// Class whose member function
// will be used as the thread's entry point
class Greeter {
public:
	void hello() {
		std::cout << "Hello, Member Function Thread!\n";
	}
};

// Callable object - thread entry point
void helloThread(std::string str) {
    std::cout << str << '\n';
}

// Passing argument to a thread function by reference
void helloRef(std::string& s) {
	s = "xyz";
}

// Requires an rvalue argument
void funcMove(std::string&& str) {
	std::cout << "Ownership of \"" << str << "\" transferred to thread" << '\n';
}

int main() {
	// Create an object of the class
	Greeter greet;

	// Create an std::thread object
	// Pass a pointer to the member function
	// and a pointer to the object to call it on
	std::thread thr1(&Greeter::hello, &greet);

  // Use a lambda expression as the thread's entry point
	std::thread thr2(
		// The first argument is the lambda expression
		[] (int i1, int i2) {
			std::cout << "The sum of " << i1 << " and " << i2 << " is " << i1 + i2 << '\n';
		},

		// The remaining arguments are passed to the lambda expression
		2, 3
	);

  // hello() takes a string argument
	std::thread thr3(helloThread, "Hello, Thread!");

  int i = 3;
	// Use a lambda expression as the thread's entry point
	std::thread thr4(
		// The first argument is the lambda expression
		[&i] {
		i *= 2;
	});

  std::string str5 = "abc" ;
	// Wrap argument in a call to std::ref()
	std::thread thr5(helloRef, std::ref(str5));

  std::string str6 = "moveable";
	// Wrap str in a call to std::move()
	std::thread thr6(funcMove, std::move(str6));

  // Wait for the thread 1 to complete
	thr1.join();

  // Wait for the thread 2 to complete
	thr2.join();

  // Wait for the thread 3 to complete
	thr3.join();

  // Wait for the thread 4 to complete
  thr4.join();
	std::cout << "Value of i is now " << i << '\n';

  // Wait for the thread 5 to complete
  thr5.join();
	// Verify that it has been modified
	std::cout << "str is now " << str5 << '\n';

  // Wait for the thread 6 to complete
  thr6.join();
	// Verify that str6 has been modified
	std::cout << (str6.empty() ? "No" : "Yes") << ".\n";

  return 0;
}