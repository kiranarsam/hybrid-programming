#include <iostream>
#include <mutex>
#include <thread>

using namespace std::literals;

// A naive internally synchronized class
// Has a data member which is a mutex
// Each member function locks the mutex when called
class BankNaive {
	// Mutex to protect the data
	std::mutex mtx;

	// Shared data
	// ...
public:
	void debit(const std::string& name, int amount)
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "Debiting " << amount << " from " << name << '\n';
	}

	void credit(const std::string& name, int amount)
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "Crediting " << amount << " to " << name << '\n';
	}
	void print(const std::string& name)
	{
		std::lock_guard<std::mutex> lock(mtx);
		std::cout << "Displaying account for " << name << '\n';
	}
};

// Monitor class
// It wraps the protected object
// Each member function locks the mutex when called
// then forwards the call to the wrapped object

// Very simple "Bank" class
class Bank {
	// Shared data
	// ...
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

class BankMonitor {
	std::mutex mtx;
	Bank bank;

public:
	void debit(const std::string& name, int amount) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lock(mtx);
		bank.debit(name, amount);
	}
	void credit(const std::string& name, int amount) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lock(mtx);
		bank.credit(name, amount);
	}
	void print(const std::string& name) {
		// Lock the mutex and forward the call
		std::lock_guard<std::mutex> lock(mtx);
		bank.print(name);
	}
};

int main()
{
  // NAIVE- CLASS
  // Transfer $1000 from Peter to Paul
	BankNaive bank;

	// Call its member functions
	// Each member function locks separately
	std::thread thr1([&bank] {
		bank.debit("Peter", 1000);
		bank.credit("Paul", 1000);
		bank.print("Peter");
		bank.print("Paul");
		});

	thr1.join();

	std::cout << "Done\n";

  // MONITOR CLASS
	// Transfer $1000 from Peter to Paul
	BankMonitor bank_mon;

	// Call its member functions; Each member function locks separately
	std::thread thr2([&bank_mon] {
		bank_mon.debit("Peter", 1000);
		bank_mon.credit("Paul", 1000);
		bank_mon.print("Peter");
		bank_mon.print("Paul");
		});

	thr2.join();

	std::cout << "Done\n";

  return 0;
}
