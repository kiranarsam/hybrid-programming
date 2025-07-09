#include <thread>
#include <iostream>
#include <vector>
#include <atomic>

std::atomic<int> counter = 0;
// A shared variable is modified by multiple threads
// Use an "atomic" variable to prevent a data race
void task()
{
  for (int i = 0; i < 100'000; ++i)
    ++counter;
}

// Using a "volatile" variable does not prevent a data race
volatile int counter01 = 0;

void task01() {
    for (int i = 0; i < 100'000; ++i)
        ++counter01;
}

int main()
{
  // CASE 1: Atomic: Prevents Data Race
  std::vector<std::thread> tasks;

  for (int i = 0; i < 10; ++i)
      tasks.push_back(std::thread(task));

	for (auto& thr: tasks)
		thr.join();

	std::cout << counter << '\n';

  // CASE 2: Volatile: Doesn't prevent a Data Race
  std::vector<std::thread> tasks01;

  for (int i = 0; i < 10; ++i)
      tasks01.push_back(std::thread(task01));

	for (auto& thr: tasks01)
		thr.join();

	std::cout << counter01 << '\n';

  return 0;
}