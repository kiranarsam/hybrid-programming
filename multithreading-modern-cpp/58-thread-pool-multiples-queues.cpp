#include <thread>
#include <functional>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

using namespace std::literals;

// Simple concurrent queue implementation
// pop() busy waits when the queue is empty
// Concurrent queue class
template <class T>
class ConcurrentQueueCv {
	// Data members
	std::mutex mut;
	std::queue<T> que;
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
		std::unique_lock<std::mutex> uniq_lck(mut);

		// If the queue is full, wait and try again
		while (que.size() > max) {
			uniq_lck.unlock();
			std::this_thread::sleep_for(50ms);
			uniq_lck.lock();
		}

		// Perform the push and notify
		que.push(value);
	}

	// Pop an element from the queue
	void pop(T& value) {
		std::unique_lock<std::mutex> uniq_lck(mut);

		while(que.empty())
		{
			uniq_lck.unlock();
			std::this_thread::sleep_for(50ms);
			uniq_lck.lock();
		}

		// Perform the pop
		value = que.front();
		que.pop();
	}
};

// Thread pool with single queue
// Type alias to simplify the code
// All the task functions will have this type
using Func = std::function<void()>;

// Alias for concurrent queue type
using Queue = ConcurrentQueueCv<Func>;

class ThreadPool {
	// Each thread has its own queue of task functions
	std::unique_ptr<Queue []> work_queues;

	// Vector of thread objects which make up the pool
	std::vector<std::thread> threads;

	// Entry point function for the threads
	void worker(int idx);

	// The number of threads in the pool
	int thread_count;

	// Index into the vector of queues
	int pos{0};

public:
	ThreadPool();
	~ThreadPool();

	// Add a task to the queue
	void submit(Func func);
};

// Thread pool with single queue
// Constructor
ThreadPool::ThreadPool() {
	thread_count = std::thread::hardware_concurrency() - 1;
	std::cout << "Creating a thread pool with " << thread_count << " threads\n";

	// Create a dynamic array of queues
	work_queues = std::make_unique<Queue []> (thread_count);

	// Start the threads
	for (int i = 0; i < thread_count; ++i) {
		threads.push_back(std::thread{&ThreadPool::worker, this, i});
	}
}

// Destructor
ThreadPool::~ThreadPool() {
	// Wait for the threads to finish
	for (auto& thr: threads) {
		thr.join();
	}
}

// Entry point function for the threads
void ThreadPool::worker(int idx) {
	while (true) {
		Func task;

		// Take a task function off the queue
		work_queues[idx].pop(task);

		// Invoke it
		task();
	}
}

// Add a task to the queue
void ThreadPool::submit(Func func) {
	work_queues[pos].push(func);

	// Advance to the next thread's queue
	pos = (pos + 1) % thread_count;
}


// A task function
void task() {
	std::cout << "Thread id: " << std::this_thread::get_id() << " starting a task " << std::endl;
	std::this_thread::sleep_for(100ms);
	std::cout << "Thread id: " << std::this_thread::get_id() << " finishing a task " << std::endl;
}

int main() {
	// Create the thread pool
	ThreadPool pool;

	// Send some tasks to the thread pool
	for (int i = 0; i < 20; ++i)
		pool.submit(task);

	pool.submit([&pool](){
		std::this_thread::sleep_for(1s);
		std::cout << "All tasks completed" << std::endl;
	});

  return 0;
}
