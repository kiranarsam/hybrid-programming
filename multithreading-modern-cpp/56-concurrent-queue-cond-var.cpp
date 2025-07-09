// Simple concurrent queue implementation
// with condition variable
// pop() blocks when the queue is empty
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <thread>
#include <future>
#include <iostream>

using namespace std::literals;

// push() polls when the queue is full

// Concurrent queue class with cond variable
template <class T>
class ConcurrentQueueCv
{
  // By default private memebers if not specified any access specifier
	// Data members
	std::mutex mut;
	std::queue<T> que;
	std::condition_variable cond_var;
	int max{50};
public:
    // Constructors
	ConcurrentQueueCv() = default;
	ConcurrentQueueCv(int max) : max(max) {};

	// Deleted special member functions
	ConcurrentQueueCv(const ConcurrentQueueCv&) = delete;
	ConcurrentQueueCv& operator =(const ConcurrentQueueCv&) = delete;
	ConcurrentQueueCv(ConcurrentQueueCv&&) = delete;
	ConcurrentQueueCv& operator =(ConcurrentQueueCv&&) = delete;

	// Member functions
	// Push an element onto the queue
	void push(T value) {
		std::unique_lock<std::mutex> lock(mut);

		// If the queue is full, wait and try again
		while (que.size() > max) {
			lock.unlock();
			std::this_thread::sleep_for(50ms);
			lock.lock();
		}

		// Perform the push and notify
		que.push(value);
		cond_var.notify_one();
	}

	// Pop an element from the queue
	void pop(T& value) {
		std::unique_lock<std::mutex> lock(mut);

		// Block when the queue is empty
		cond_var.wait(lock, [this] {return !que.empty();});

		// Perform the pop
		value = que.front();
		que.pop();
	}
};

// Test program for concurrent blocking queue
ConcurrentQueueCv<std::string> conc_que(10);

// Waiting thread
void reader() {
	std::string data;

	// Pop some elements from the queue
	std::cout << "Reader calling pop..." << std::endl;
	for (int i = 0; i < 15; ++i) {
		conc_que.pop(data);                                    // Pop the data off the queue
		std::cout << "Reader received data: " << data << std::endl;
	}
}

// Modyifing thread
void writer() {
	using namespace std::literals;
	std::this_thread::sleep_for(100ms);                       // Pretend to be busy...
	std::cout << "Writer calling push..." << std::endl;

	// Push the data onto the queue
	for (int i = 0; i < 15; ++i) {
		std::string data = "Item " + std::to_string(i);
		conc_que.push(data);
	}

	std::cout << "Writer returned from push..." << std::endl;
}

int main() {
	// Start the threads
	std::cout << "Starting reader" << std::endl;
	auto read_fut = async(std::launch::async, reader);
	std::cout << "Starting writer" << std::endl;
	auto write_fut = std::async(std::launch::async, writer);

	// Wait for them to complete
	read_fut.wait();
	write_fut.wait();

  return 0;
}
