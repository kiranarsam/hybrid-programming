#include <iostream>
#include <thread>
#include <mutex>

// Synchronizing shared data with mutex and thread function with arguments
void work(int &count, std::mutex &mtx)
{
  for(int i = 0; i < 1E6; i++)
  {
    mtx.lock();
    ++count;
    mtx.unlock();
  }
}

int main(int argc, char **argv)
{
  int count = 0;

  std::mutex mtx;

  std::thread t1(work, std::ref(count), std::ref(mtx));
  std::thread t2(work, std::ref(count), std::ref(mtx));

  t1.join();
  t2.join();

  std::cout << "Count = " << count << std::endl;
  return 0;
}
