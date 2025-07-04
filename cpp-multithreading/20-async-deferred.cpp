#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void work(int id)
{
  for(int i = 0; i < 5; i++)
  {
    std::cout << "Running: " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

  }
}

int main(int argc, char **argv)
{
  std::future<void> f1 = std::async(std::launch::deferred, work, 1);
  std::future<void> f2 = std::async(std::launch::deferred, work, 7);

  // deffered will execute when future.get() is called or invoked.
  f1.get();
  f2.get();
  return 0;
}