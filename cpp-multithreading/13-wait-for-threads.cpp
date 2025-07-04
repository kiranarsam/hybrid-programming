#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

int main(int argc, char **argv)
{
  // thread_local bool is_ready = false; // Here, thread_local doesn't work
  bool is_ready = false;  // Works
  // std::atomic<bool> is_ready = false; // Works

  std::thread t1([&](){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    is_ready = true;
  });

  // Why thread.join() to keep, if already checking for the status of ready in main thread
  //t1.join();

  while(!is_ready) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  std::cout << "Ready = " << is_ready << std::endl;

  t1.join();

  return 0;
}