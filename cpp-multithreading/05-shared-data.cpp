#include <iostream>
#include <thread>

int main(int argc, char **argv)
{
  int count = 0;
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

  // Here, we can see output, data is not synchronizing.
  std::cout << "Count = " << count << std::endl;
  return 0;
}
