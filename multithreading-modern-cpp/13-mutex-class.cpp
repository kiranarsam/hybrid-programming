// Use a mutex to avoid scrambled output
#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std::literals; // 20ms, 2s, 500ms, etc..

// Global mutex object
std::mutex g_mtx;
std::mutex g_mtx_task;

void task(const std::string& str)
{
	for (int i = 0; i < 5; ++i) {
		// Lock the mutex before the critical section
		g_mtx.lock();
		// Start of critical section
		std::cout << str[0] << str[1] << str[2] << std::endl;
		// End of critical section
		// Unlock the mutex after the critical section
		g_mtx.unlock();
	}
}

void task1()
{
	std::cout << "Task1 trying to lock the mutex" << std::endl;
	g_mtx_task.lock();
	std::cout << "Task1 has locked the mutex" << std::endl;
	std::this_thread::sleep_for(500ms);
	std::cout << "Task1 unlocking the mutex" << std::endl;
	g_mtx_task.unlock();
}

void task2()
{
	std::this_thread::sleep_for(100ms);
	std::cout << "Task2 trying to lock the mutex" << std::endl;
	while (!g_mtx_task.try_lock()) {
		std::cout << "Task2 could not lock the mutex" << std::endl;
		std::this_thread::sleep_for(100ms);
	}
	std::cout << "Task2 has locked the mutex" << std::endl;
	g_mtx_task.unlock();
}

int main()
{
	std::thread thr1(task, "abc");
	std::thread thr2(task, "def");
	std::thread thr3(task, "xyz");

  std::thread thr4(task1);
	std::thread thr5(task2);

	thr1.join();
	thr2.join();
	thr3.join();
  thr4.join();
	thr5.join();

  return 0;
}