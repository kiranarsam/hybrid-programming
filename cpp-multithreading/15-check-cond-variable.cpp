#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>

int main(int argc, char **argv)
{
  std::condition_variable cond;
  std::mutex mtx;

  bool is_ready = false;

  std::thread t1([&](){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    std::cout << "t1 acquiring lock" << std::endl;

    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "t1 acquired lock" << std::endl;
    is_ready = true;
    lock.unlock();

    std::cout << "t1 released lock; notifying" << std::endl;
    // Release the mutex and notify
    cond.notify_one();
  });


  std::cout << "main thread acquiring lock" << std::endl;

  std::unique_lock<std::mutex> lock(mtx);

  std::cout << "main thread acquired lock; waiting" << std::endl;

  // wait for the lock, until condition is met
  cond.wait(lock, [&](){ return is_ready;});

  std::cout << "main thread finished waiting " << std::endl;

  std::cout << "Ready = " << is_ready << std::endl;

  t1.join();

  return 0;
}