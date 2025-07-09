// Condition variable with predicate
//
// The reader thread will wait until "condition" becomes true
// This avoids lost and spurious wakeups
#include <iostream>
#include <thread>
#include <condition_variable>
#include <string>

using namespace std::chrono;

// The shared data
std::string g_sdata;

// Mutex to protect critical sections
std::mutex g_mtx;

// The condition variable
std::condition_variable g_cond_var;

// bool flag for predicate
bool g_condition = false;

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

	// Lambda predicate that checks the flag
	g_cond_var.wait(lock, [] {return g_condition;});

	// The condition variable has woken this thread up
	// and locked the mutex
	std::cout << "Reader thread wakes up\n";

	// Display the new value of the string
	std::cout << "Data is \"" << g_sdata << "\"\n";
	std::cout << "Reader thread unlocks the mutex\n";
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

		// Set the flag
		g_condition = true;

		std::cout << "Writer thread unlocks the mutex\n";
	}

	// Notify the condition variable
	std::cout << "Writer thread sends notification\n";
	g_cond_var.notify_one();
}

// Condition variable with predicate
// Example with multiple waiting threads
// Waiting thread
void readerMulti()
{
	// Lock the mutex
	std::cout << "Reader thread locking mutex\n";
	std::unique_lock<std::mutex> lock(g_mtx);
	std::cout << "Reader thread has locked the mutex\n";

	// Call wait()
	// This will unlock the mutex and make this thread
	// sleep until the condition variable wakes us up
	std::cout << "Reader thread sleeping...\n";

	// Lambda predicate that checks the flag
	g_cond_var.wait(lock, [](){return g_condition;});

	// The condition variable has woken this thread up
	// and locked the mutex
	std::cout << "Reader thread " << std::this_thread::get_id() << " wakes up\n";

	// Display the new value of the string
	std::cout << "Data is \"" << g_sdata << "\"\n";
	std::cout << "Reader thread unlocks the mutex\n";
}

// Notifying thread
void writerMulti()
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

		// Set the flag
		g_condition = true;

		std::cout << "Writer thread unlocks the mutex\n";
	}

	// Notify the condition variable
	std::cout << "Writer thread sends notification\n";

	// g_cond_var.notify_all();

	for (int i = 0; i < 2; ++i)
		g_cond_var.notify_one();

}

// CASE 3
// Example of a "lost wakeup"
//
// The writer thread sends its notification before the reader calls wait()
// The reader never receives the notification
// The reader thread blocks indefinitely
// Waiting thread
void reader01()
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
void writer01()
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

	// The notification is not lost,
	// even if the writer thread finishes before the reader thread starts
	// or there is a "spurious wakeup" (wait returns without a notification)
	std::thread write(writer);
	// std::this_thread::sleep_for(500ms);
	std::thread read(reader);

	write.join();
	read.join();

  // CASE2: cond multithreaded
  g_condition = false;
  // Initialize the shared string
	g_sdata = "Empty";
  // Display its initial value
	std::cout << "Data is \"" << g_sdata << "\"\n";
  // The notification is not lost,
	// even if the writer thread finishes before the reader thread starts
	// or there is a "spurious wakeup" (wait returns without a notification)

	std::thread write1(writerMulti);
	std::thread read1(readerMulti);
	std::this_thread::sleep_for(10ms);
	std::thread read2(readerMulti);
	std::this_thread::sleep_for(10ms);
	std::thread read3(readerMulti);
	std::this_thread::sleep_for(10ms);

	write1.join();
	read1.join();
	read2.join();
	read3.join();

  // Initialize the shared string
	g_sdata = "Empty";

	// Display its initial value
	std::cout << "Data is \"" << g_sdata << "\"\n";

	// Start the threads
	// If the writer thread finishes before the reader thread starts, the notification is lost
	std::thread write01(writer01);
	std::this_thread::sleep_for(500ms);
	std::thread read01(reader01); // reader thread is block due to notification is lost

	write01.join();
	read01.join();

  return 0;
}
