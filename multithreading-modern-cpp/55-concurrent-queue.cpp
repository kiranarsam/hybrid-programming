#include <queue>
#include <mutex>
#include <iostream>
#include <future>
#include <thread>

// Simple concurrent queue implementation
// pop() throws an exception when the queue is empty
// push() throws an exception when the queue is full

// Exception types for when queue is empty or full
class ConcurrentQueueEmpty : public std::runtime_error {
  public:
	ConcurrentQueueEmpty() : std::runtime_error("Queue is empty") {}
	ConcurrentQueueEmpty(const char *s) : std::runtime_error(s) {}
};

class ConcurrentQueueFull : public std::runtime_error {
  public:
	ConcurrentQueueFull() : std::runtime_error("Queue is full") {}
	explicit ConcurrentQueueFull(const char *s) : std::runtime_error(s) {}
};

// Concurrent queue class
template <class T>
class ConcurrentQueue
{
private:
	// Data members
	std::mutex mut;
	std::queue<T> que;
	int max{50};
public:
  // Constructors
	ConcurrentQueue() = default;
	ConcurrentQueue(int max) : max(max) {};

	// Deleted special member functions
	ConcurrentQueue(const ConcurrentQueue&) = delete;
	ConcurrentQueue& operator =(const ConcurrentQueue&) = delete;
	ConcurrentQueue(ConcurrentQueue&&) = delete;
	ConcurrentQueue& operator =(ConcurrentQueue&&) = delete;

	// Member functions
	// Push an element onto the queue
	void push(T value) {
		std::lock_guard<std::mutex> lck_guard(mut);

		if (que.size() > max) {
			throw ConcurrentQueueFull();
		}

		que.push(value);
	}

	// Pop an element from the queue
	void pop(T& value) {
		std::unique_lock<std::mutex> uniq_lck(mut);

		if (que.empty()) {
			throw ConcurrentQueueEmpty();
		}

		value = que.front();
		que.pop();
	}
};

// Simple Concurrent Queue
// Shared queue object
ConcurrentQueue<std::string> conc_que(10);

// Waiting thread
void reader() {
	using namespace std::literals;
	std::this_thread::sleep_for(2s);                         // Pretend to be busy...
	std::string sdata;

	// Pop some elements from the queue
	std::cout << "Reader calling pop..." << std::endl;
	for (int i = 0; i < 10; ++i) {
		conc_que.pop(sdata);                                    // Pop the data off the queue
		std::cout << "Reader received data: " << sdata << std::endl;
	}
}

// Modifying thread
void writer() {
	// Push the data onto the queue
	for (int i = 0; i < 10; ++i) {
		std::string sdata = "Item " + std::to_string(i);
		conc_que.push(sdata);
	}

	std::cout << "Writer returned from push..." << std::endl;
}

// Test program for simple concurrent queue with exception handling
// Shared queue object
ConcurrentQueue<std::string> cq(5);

// Waiting thread
void readerException() {
	std::string sdata;

	// Pop an element from the queue
	std::cout << "Reader calling pop..." << std::endl;
	cq.pop(sdata);                                       // Pop the data off the queue
	std::cout << "Reader received data: " << sdata << std::endl;
}

// Modifying thread
void writerException() {
	// Push an element onto the queue
	using namespace std::literals;
	std::this_thread::sleep_for(2s);                         // Pretend to be busy...
	std::cout << "Writer calling push..." << std::endl;
  for(int i = 0; i < 8; i++)
	  cq.push("Populated");                                    // Push the data onto the queue
	std::cout << "Writer returned from push..." << std::endl;
}

int main() {
	// Start the threads
	auto write_fut = std::async(std::launch::async, writer);
	auto read_fut = std::async(std::launch::async, reader);

	// Wait for them to complete
	try {
		read_fut.get();
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	try {
		write_fut.get();
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

  // WITH EXCEPTION

  // Start the threads
	auto write_fut_ex = std::async(std::launch::async, writerException);
	auto read_fut_ex = std::async(std::launch::async, readerException);

	// Wait for them to complete
	try {
		read_fut_ex.get();
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

	try {
		write_fut_ex.get();
	}
	catch (const std::exception& e) {
		std::cout << "Exception caught: " << e.what() << std::endl;
	}

  return 0;
}
