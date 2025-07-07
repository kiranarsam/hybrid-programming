#include <mutex>
#include <iostream>

// Lazy Initialization (single threaded)
class TestSingle {
	// ...
public:
	void func() { /*...*/ }
};

TestSingle *pstest = nullptr;          // Variable to be lazily initialized

void processSingle() {
    if (!pstest)                // First time variable has been used
        pstest = new TestSingle;      // Initialize it
    pstest->func();             // Use it
}

// Lazy initialization (multi-threaded)
// Inefficient (always locks the mutex)
class TestMulti {
	// ...
public:
	void func() { /*...*/ }
};

TestMulti *pmtest = nullptr;         // Variable to be lazily initialized
std::mutex g_mtx;

void processMulti() {
    std::unique_lock<std::mutex> lock(g_mtx);       // Protect ptest

    if (!pmtest)
        pmtest = new TestMulti;
    lock.unlock();
    pmtest->func();
}

// Lazy initialization (multi-threaded)
// Uses the Double-checked Locking algorithm
class TestDoubleCheck {
	// ...
public:
	void func() { /*...*/ }
};

TestDoubleCheck *ptest = nullptr;            // Variable to be lazily initialized
std::mutex g_mtx_02;

void processDoubleCheck() {
    if (!ptest) {                     // First check of ptest
        std::lock_guard<std::mutex> lck_guard(g_mtx_02);

        if (!ptest)                  // Second check of ptest
            ptest = new TestDoubleCheck;   // Initialize ptest
    }
    ptest->func();
}

int main()
{

  processSingle();
  processMulti();

  // Prefer double-checking algorithm over initilization in multi-threaded program
  processDoubleCheck();

  return 0;

}