// Singleton class definition
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

std::mutex g_mtx;

class ClassicalSingleton {
	// Pointer to unique instance
	static ClassicalSingleton *single;

	// The constructor is private
	ClassicalSingleton() { std::cout << "Initializing ClassicalSingleton" << std::endl;}
public:
	// The copy and move operators are deleted
	ClassicalSingleton(const ClassicalSingleton&) = delete;
	ClassicalSingleton& operator=(const ClassicalSingleton&) = delete;
	ClassicalSingleton(ClassicalSingleton&&) = delete;
	ClassicalSingleton& operator=(ClassicalSingleton&&) = delete;

	// Static member function to obtain the Singleton object
	static ClassicalSingleton* get_ClassicalSingleton();
};

ClassicalSingleton* ClassicalSingleton::single = nullptr;

// Static member function to obtain the Singleton object
ClassicalSingleton* ClassicalSingleton::get_ClassicalSingleton()
{
    // Thread safety lock. (Double-Checked locking)
    if(single == nullptr) {
      g_mtx.lock();
      if (single == nullptr) {
          single = new ClassicalSingleton;
      }
      g_mtx.unlock();
    }
    return single;
}

class Cpp11Singleton {
  public:
	// The copy and move operators are deleted
	Cpp11Singleton(const Cpp11Singleton&) = delete;
	Cpp11Singleton& operator=(const Cpp11Singleton&) = delete;
	Cpp11Singleton(Cpp11Singleton&&) = delete;
	Cpp11Singleton& operator=(Cpp11Singleton&&) = delete;

	Cpp11Singleton() { std::cout << "Initializing Cpp11Singleton\n";}
};

// Function to obtain the Singleton object
Cpp11Singleton& get_Cpp11Singleton();

// Function to obtain the Singleton object
Cpp11Singleton& get_Cpp11Singleton()
{
  // Initialized by the first thread that executes this code
	static Cpp11Singleton single;
	return single;
}

// ClassicalSignleton
void taskClassical()
{
	ClassicalSingleton* single = ClassicalSingleton::get_ClassicalSingleton();
	std::cout << single << std::endl;
}

// Cpp11Singleton
void taskCpp11()
{
	Cpp11Singleton& single = get_Cpp11Singleton();
	std::cout << &single << std::endl;
}

int main()
{
  // classical singleton
	std::vector<std::thread> threadsClassical;

	for (int i = 0; i < 10; ++i)
		threadsClassical.push_back(std::thread(taskClassical));

	for (auto& thr : threadsClassical)
		thr.join();


  // cpp 11 singleton
  std::vector<std::thread> threadsCpp11;

	for (int i = 0; i < 10; ++i)
		threadsCpp11.push_back(std::thread(taskCpp11));

	for (auto& thr : threadsCpp11)
		thr.join();


  return 0;
}