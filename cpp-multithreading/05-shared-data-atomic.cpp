#include <iostream>
#include <thread>
#include <atomic>

int main(int argc, char **argv)
{
  std::atomic<int> count = 0;
  const int ITERATIONS = 1E6; // 1 million

  // lamda function can be defined as => [](){}

  std::thread t1([&count](){
    for(int i = 0; i < ITERATIONS; i++)
    {
      ++count;
    }
  });
  std::thread t2([&count](){
    for(int i = 0; i < ITERATIONS; i++)
    {
      ++count;
    }
  });

  t1.join();
  t2.join();

  // Here, data is synchronized with atomic shared variable
  std::cout << "Count = " << count << std::endl;
  return 0;
}
