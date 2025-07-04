#include <iostream>
#include <future>
#include <chrono>
#include <thread>

// void work(int id)
int work(int id)
{
  for(int i = 0; i < 5; i++)
  {
    std::cout << "Running: " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

  }
  return id * 6;
}

int main(int argc, char **argv)
{
  // If you assign async object then below async function will behave correctly.
  // std::future<void> f1 = std::async(std::launch::async, work, 1);
  // std::future<void> f2 = std::async(std::launch::async, work, 7);
  std::future<int> f1 = std::async(std::launch::async, work, 1);
  std::future<int> f2 = std::async(std::launch::async, work, 2);

  // For launch::async, the future.get() is optional, unless it has return type.
  f1.get();
  f2.get();
  return 0;
}