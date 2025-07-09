#include <mutex>
#include <thread>
#include <vector>
#include <atomic>
#include <iostream>

class Test {
	// ...
public:
	void func() {
    std::cout << "Test.func called\n";
  }
};

// Another way to solve double-checked locking
// Make the lazily-initialized variable atomic
std::atomic<Test*> ptest = nullptr;  // Variable to be lazily initialized
std::mutex g_mtx;

void process()
{
	// First check of ptest
	if (!ptest) {
		std::lock_guard<std::mutex> lck_guard(g_mtx);

		// Second check of ptest
		if (!ptest) {
			// Initialize ptest
			ptest = new Test;
		}
	}

	// Atomic pointers cannot be dereferenced
	// Copy it to a non-atomic pointer first
	Test *ptr_test = ptest;
	ptr_test->func();
}

int main()
{
	std::vector<std::thread> threads;

	for (int i = 0; i < 10; ++i)
		threads.push_back(std::thread(process));

	for (auto& thr : threads)
		thr.join();

  return 0;
}