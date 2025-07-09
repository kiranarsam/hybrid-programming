#include <future>
#include <string>
#include <iostream>
#include <mutex>
#include <vector>
#include <chrono>
#include <thread>

using namespace std::literals;

// Example of a monitor class
// Has a data member which is a mutex
// Each member function locks the mutex when called

// Very simple "Bank" class
class Bank {
public:
  void debit(const std::string& name, int amount)
	{
		std::cout << "Debiting " << amount << " from " << name << '\n';
	}

	void credit(const std::string& name, int amount)
	{
		std::cout << "Crediting " << amount << " to " << name << '\n';
	}
	void print(const std::string& name)
	{
		std::cout << "Displaying account for " << name << '\n';
	}
};

// Monitor class
// Can wrap any type
template <typename T>
class Monitor {
    // The object to be monitored
	T data;

	// Mutex to protect the object
  std::mutex mtx;
public:
	// Default constructor
	Monitor<T>(T data = T{}) : data(data) {}

	// Function call operator
	// Argument is a callable object of type Func
	// which takes an argument of type T
  template <typename Func>
  auto operator() (Func func) {
		std::lock_guard<std::mutex> lock(mtx);

		// Call the function, protected by the lock
		return func(data);
	}
};

void bankMonitor()
{
  // Transfer $1000 from Peter to Paul
	// Must be done as a single transaction

	// Monitor wrapper for Bank class
	Monitor<Bank> mon; // Bank object is created by default through template

	// Invoke its function call operator and
	// pass a callable object which takes a Bank argument
	mon([] (Bank bank) {
		// Call its member functions, all under the same lock
		bank.debit("Peter", 1000);
		bank.credit("Paul", 1000);
		bank.print("Peter");
		bank.print("Paul");
	});

	std::cout << "Done\n";
}

void stringMonitor()
{
  using namespace std::literals;

	// Monitor wrapper for std::string
	Monitor<std::string> str_mon("start: "s);

	for (int i = 0; i < 5; ++i) {
		// Invoke its function call operator and
	  // pass a callable object which takes an std::string argument
		str_mon([i](std::string& arg) {
			arg += std::to_string(i) + ", " + std::to_string(i) + ", ";
		});

		// Invoke the function call operator again
		str_mon([](const std::string& arg) {
			std::cout << arg << '\n';
		});
	}

	std::cout << "Done\n";
}

void stringMonitorThreads()
{
  using namespace std::literals;

	// Monitor wrapper for std::string
	Monitor<std::string> str_mon("start: "s);

	// Vector to store returned futures from std::async()
	std::vector<std::future<void>> futs;

	for (int i = 0; i < 5; ++i) {
		futs.push_back(std::async([&str_mon, i] {
			// Invoke its function call operator and
	    // pass a callable object which takes an std::string argument
			str_mon([i](std::string& arg) {
				std::this_thread::sleep_for(10ms);
				arg += std::to_string(i) + ", " + std::to_string(i) + ", ";
			});

			// Invoke the function call operator again
			str_mon([](const std::string& arg) {
				std::cout << arg << '\n';
			});
		}));
	}

	for (auto& fut: futs)
		fut.wait();

	std::cout << "Done\n";
}

int main()
{

  bankMonitor();

  stringMonitor();

  stringMonitorThreads();

  return 0;
}
