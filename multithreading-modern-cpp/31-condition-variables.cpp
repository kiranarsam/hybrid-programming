// Condition variable example
//
// The reader thread waits for a notification
// The writer thread modifies the shared variable "sdata"
// The writer thread sends a notification
// The reader thread receives the notification and resumes
// The reader thread uses the new value of the shared data
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>
#include <chrono>

using namespace std::literals;

// The shared data
std::string g_sdata;

// Mutex to protect critical sections
std::mutex g_mtx;

// The condition variable
std::condition_variable g_cond_var;

// Waiting thread
void reader()
{
	// Lock the mutex
	std::cout << "Reader thread locking mutex\n";
	std::unique_lock<std::mutex> lock(g_mtx);
	std::cout << "Reader thread has locked the mutex\n";

	// Call wait()
	// This will unlock the mutex and make this thread
	// sleep until the condition variable wakes us up
	std::cout << "Reader thread sleeping...\n";
	g_cond_var.wait(lock);

	// The condition variable has woken this thread up
	// and locked the mutex
	std::cout << "Reader thread wakes up\n";

	// Display the new value of the string
	std::cout << "Data is \"" << g_sdata << "\"\n";
}

// Notifying thread
void writer()
{
	{
		// Lock the mutex
		std::cout << "Writer thread locking mutex\n";

		// Lock the mutex
		// This will not be explicitly unlocked
		// std::lock_guard is sufficient
		std::lock_guard<std::mutex> lock(g_mtx);
		std::cout << "Writer thread has locked the mutex\n";

		// Pretend to be busy...
		std::this_thread::sleep_for(2s);

		// Modify the string
		std::cout << "Writer thread modifying data...\n";
		g_sdata = "Populated";
	}

	// Notify the condition variable
	std::cout << "Writer thread sends notification\n";
	g_cond_var.notify_one();
}

int main()
{
	// Initialize the shared string
	g_sdata = "Empty";

	// Display its initial value
	std::cout << "Data is \"" << g_sdata << "\"\n";

	// Start the threads
	std::thread read(reader);
	std::thread write(writer);
	// std::thread read(reader);

	// read.join();
	write.join();
	read.join();

  return 0;
}