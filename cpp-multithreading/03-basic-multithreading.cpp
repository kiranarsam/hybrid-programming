#include <iostream>
#include <thread>
#include <chrono>

void work()
{
  for(int i = 0; i < 10; i++)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "Loop: " << i << std::endl;
  }
}

int main(int argc, char **argv)
{
  std::thread t1(work);
  std::thread t2(work);

  t1.join();
  t2.join();

  return 0;
}
