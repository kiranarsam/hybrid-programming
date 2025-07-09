#include <thread>
#include <iostream>
#include <vector>
#include <mutex>

int g_counter = 0;

// A shared variable is modified by multiple threads
// Integer operations take a single instruction
// Is there a data race?
// Yes, There is data race in this thread task: counter operation
void task()
{
    for (int i = 0; i < 100'000; ++i) {
        ++g_counter;
    }
}

int g_counter01 = 0;
std::mutex g_mtx;
void task01()
{
    for (int i = 0; i < 100'000; ++i) {
      std::lock_guard<std::mutex> lock(g_mtx);
        ++g_counter01;
    }
}

int main()
{
  // CASE 1: Data Race
  std::vector<std::thread> tasks;

  for (int i = 0; i < 10; ++i)
      tasks.push_back(std::thread(task));

  for (auto& thr: tasks)
      thr.join();

  std::cout << g_counter << '\n';

  // CASE 2: protected with Mutex: No Data Race
  std::vector<std::thread> tasks01;

  for (int i = 0; i < 10; ++i)
      tasks01.push_back(std::thread(task01));

  for (auto& thr: tasks01)
      thr.join();

  std::cout << g_counter01 << '\n';

  return 0;
}