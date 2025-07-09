// Example using std::promise and std::future
// to send a result from a producer thread
// to a consumer thread
#include <future>
#include <iostream>
#include <thread>
#include <chrono>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int>& px)
{
	using namespace std::literals;

	// Produce the result
	int x = 42;
	std::this_thread::sleep_for(2s);

	// Store the result in the shared state
	std::cout << "Promise sets shared state to " << x << '\n';
	px.set_value(x);
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int>& fx)
{
	// Get the result from the shared state
	std::cout << "Future calling get()...\n";
	int x = fx.get();
	std::cout << "Future returns from calling get()\n";
	std::cout << "The answer is " << x << '\n';
}

// The consumer's task function takes an std::shared_future as argument
void consume01(std::shared_future<int>& fx)
{
	// Get the result from the shared state
	std::cout << "Thread " << std::this_thread::get_id() << " calling get()...\n";
  int x = fx.get();

  std::cout << "Thread " << std::this_thread::get_id() << " returns from calling get()\n";
	std::cout << "Thread " << std::this_thread::get_id() << " has answer " << x << '\n';
}

int main()
{
	// Create an std::promise object
	// This creates an associated std::future object
	// and sets up a shared state between them
	std::promise<int> prom;

	// Get the future associated with the promise
	std::future<int> fut = prom.get_future();

	// Start the threads
	// The producer task function takes the promise as argument
	std::thread thr_producer1(produce, std::ref(prom));

	// The consumer task function takes the future as argument
	std::thread thr_consumer1(consume, std::ref(fut));
	std::thread thr_consumer2(consume, std::ref(fut));

	thr_consumer1.join();
	thr_consumer2.join();
	thr_producer1.join();

  // CASE2
  prom = std::promise<int>();
  // Get an std::shared_future associated with the promise
	// This will move the promise's future into a shared future
  std::shared_future<int> shared_fut1 = prom.get_future();

	// Copy the shared future object
  std::shared_future<int> shared_fut2 = shared_fut1;

  // Start the threads
	// The producer task function takes the promise as argument
	std::thread thr_producer2(produce, std::ref(prom));

  // Start two consumer threads
	// The consumer task function takes a shared future as argument
	// Each thread uses a different shared future object
	std::thread thr_consumer3(consume01, std::ref(shared_fut1));
	std::thread thr_consumer4(consume01, std::ref(shared_fut2));

  thr_consumer3.join();
	thr_consumer4.join();
  thr_producer2.join();

  return 0;
}