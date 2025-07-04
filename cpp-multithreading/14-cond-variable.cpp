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
    std::unique_lock<std::mutex> lock(mtx);
    is_ready = true;
    lock.unlock();
    // Release the mutex and notify
    cond.notify_one();
  });


  std::unique_lock<std::mutex> lock(mtx);

  while(!is_ready) {
    // wait for the lock to be notified
    cond.wait(lock);
  }

  std::cout << "Ready = " << is_ready << std::endl;

  t1.join();

  return 0;
}