// Lazy initialization (multi-threaded)
// Uses Meyers singleton
#include <mutex>
#include <thread>
#include <iostream>

class Test {
	// ...
public:
	Test()
	{
		std::cout << "Test constructor called\n";
	}

	void func()
	{
		/*...*/
	}
};

// Using Meyers Singleton
void processMeyers()
{
	static Test ptest;            // Variable which is lazily initialized
	ptest.func();
}


// Using std::call_once()
std::once_flag ptest_flag;         // The flag stores synchronization data
Test* ptest = nullptr;             // Variable to be lazily initialized

void processCallOnce()
{
	// Pass a callable object which performs the initialization
	std::call_once(ptest_flag, []() {
		ptest = new Test;
		});
	ptest->func();
}


int main()
{
	std::thread thr1(processMeyers);
	std::thread thr2(processMeyers);
	thr1.join(); thr2.join();

  std::thread thr3(processCallOnce);
	std::thread thr4(processCallOnce);
	thr3.join(); thr4.join();

  return 0;
}