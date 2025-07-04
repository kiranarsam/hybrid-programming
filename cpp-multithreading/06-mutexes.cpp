#include <iostream>
#include <thread>
#include <mutex>

// Synchronizing shared data with mutex

int main(int argc, char **argv)
{
  int count = 0;
  const int ITERATIONS = 1E6; // 1 million

  std::mutex mtx;

  // lamda function
  auto func = [&](){
    for(int i = 0; i < ITERATIONS; i++)
    {
      mtx.lock();
      ++count;
      mtx.unlock();
    }
  };

  std::thread t1(func);
  std::thread t2(func);

  t1.join();
  t2.join();

  std::cout << "Count = " << count << std::endl;
  return 0;
}
