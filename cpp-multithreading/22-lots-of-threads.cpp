#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <mutex>

std::mutex g_mtx;

int work(int id)
{
  std::unique_lock<std::mutex> lock(g_mtx);
  std::cout << "Starting: " << id << std::endl;
  lock.unlock();
  std::this_thread::sleep_for(std::chrono::seconds(3));

  return id;
}

int main(int argc, char **argv)
{
  std::vector<std::shared_future<int>> futures;
  auto hw_conc = std::thread::hardware_concurrency();

  for(int i = 0; i < hw_conc; i++)
  {
    std::shared_future<int> f = std::async(std::launch::async, work, i);
    // "future" is not copyable, use "shared_future" while pushing into containers
    futures.push_back(f);
  }

  for (auto f : futures)
  {
    auto result = f.get();
    std::cout << "Returned async future value: " << result << std::endl;
  }

  return 0;
}