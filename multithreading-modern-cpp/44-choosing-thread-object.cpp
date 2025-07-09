// The destructor for std::async() will block
// if launched with std::launch::async
#include <future>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>

using namespace std::literals;

void task()
{
	std::this_thread::sleep_for(2s);
	std::cout << "Task result: " << 42 << '\n';
}

void func()
{
	std::cout << "func: Calling async\n";
	auto result = std::async(std::launch::async, task);
  // auto result = std::async(task);
  std::cout << "func: returned\n";
}

int main()
{
	func();
	std::cout << "Task started\n";

  return 0;
}