// Example using std::promise and std::future
// to send a result from a producer thread
// to a consumer thread
#include <future>
#include <iostream>
#include <thread>
#include <chrono>

// The producer's task function takes a std::promise as argument
void produce(std::promise<int>& px, int option)
{
  try
  {
    using namespace std::literals;

    // Produce the result
    int x = 42;
    std::this_thread::sleep_for(2s);

    // Code that may throw
    if (option == 1)
    {
      throw std::out_of_range("Oops");
    }

    if(option == 2)
    {
      // Code that may throw std::make_exception_ptr()
      px.set_exception(std::make_exception_ptr(std::out_of_range("Oops")));
      return;
    }

    // Store the result in the shared state
    std::cout << "Promise sets shared state to " << x << '\n';
    px.set_value(x);
  }
  catch(...)
  {
    // Exception thrown - store it in the shared state
		px.set_exception(std::current_exception());
  }
}

// The consumer's task function takes an std::future as argument
void consume(std::future<int>& fx)
{
	// Get the result from the shared state
	std::cout << "Future calling get()...\n";
  try
  {
    int x = fx.get();
    std::cout << "Future returns from calling get()\n";
    std::cout << "The answer is " << x << '\n';
  }
  catch(const std::exception& e)
  {
    // Exception thrown - get it from the shared state
		std::cout << "Exception caught: " << e.what() << '\n';
  }
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
  std::thread thr_producer(produce, std::ref(prom), 0);
  // The consumer task function takes the future as argument
  std::thread thr_consumer(consume, std::ref(fut));

  thr_consumer.join();
  thr_producer.join();

  // CASE2: exception
  // Try to reset the promise (Don't use same promise or future)
  prom = std::promise<int>(); // This creates a new promise object
  fut = prom.get_future();
  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer01(produce, std::ref(prom), 1);
  // The consumer task function takes the future as argument
  std::thread thr_consumer01(consume, std::ref(fut));

  thr_consumer01.join();
  thr_producer01.join();

  // CASE3: exception
  // Try to reset the promise (Don't use same promise or future)
  prom = std::promise<int>(); // This creates a new promise object
  fut = prom.get_future();
  // Start the threads
  // The producer task function takes the promise as argument
  std::thread thr_producer02(produce, std::ref(prom), 2);
  // The consumer task function takes the future as argument
  std::thread thr_consumer02(consume, std::ref(fut));

  thr_consumer02.join();
  thr_producer02.join();


  return 0;
}