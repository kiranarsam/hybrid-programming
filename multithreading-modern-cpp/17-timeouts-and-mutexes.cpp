#include <iostream>
#include <thread>
#include <mutex>

using namespace std::literals;

std::recursive_mutex g_rmtx;

// In recursive functions, nested locking and thread-safe data structures,
int bad_factorial(int n)
{
	if (n <= 1) {
		std::cout << "g_rmtx: Returning " << 1 << '\n';
		return 1;
	}

	std::lock_guard<std::recursive_mutex> lock(g_rmtx);
	// g_rmtx.lock();

	// Start of critical section
	int retval = n*bad_factorial(n-1);
	std::cout << "g_rmtx: Returning " << retval << std::endl;
	// End of critical section

	// g_rmtx.unlock();
	return retval;
}

// Using mtx.try_lock_for()
std::timed_mutex g_tmtx_01;

void task1TimedMtx()
{
	std::cout << "g_tmtx_01: Task1 trying to lock the mutex\n";
	g_tmtx_01.lock();
	std::cout << "g_tmtx_01: Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "g_tmtx_01: Task1 unlocking the mutex\n";
	g_tmtx_01.unlock();
}

void task2TimedMtx()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "g_tmtx_01: Task2 trying to lock the mutex\n";

	// Try for 1 second to lock the mutex
	while (!g_tmtx_01.try_lock_for(1s)) {
		// Returned false
		std::cout << "g_tmtx_01: Task2 could not lock the mutex\n";
		// Try again on the next iteration
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "g_tmtx_01: Task2 has locked the mutex\n";
	// End of critical section

	g_tmtx_01.unlock();
}

// Using mtx.try_lock_until()
std::timed_mutex g_tmtx_02;

void task1TimedMtxUntil()
{
	std::cout << "g_tmtx_02: Task1 trying to get lock\n";
	g_tmtx_02.lock();
	std::cout << "g_tmtx_02: Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "g_tmtx_02: Task1 unlocking the mutex\n";
	g_tmtx_02.unlock();
}

void task2TimedMtxUntil()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "g_tmtx_02: Task2 trying to lock the mutex\n";
	auto deadline = std::chrono::system_clock::now() + 900ms;

	// Try until "deadline" to lock the mutex
	while (!g_tmtx_02.try_lock_until(deadline)) {
		// Returned false
		// Update "deadline" and try again
		deadline = std::chrono::system_clock::now() + 900ms;
		std::cout << "g_tmtx_02: Task2 could not lock the mutex\n";
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "g_tmtx_02: Task2 has locked the mutex\n";
	// End of critical section

	g_tmtx_02.unlock();
}

// Using lock_guard, unique_lock and mtx.try_lock_for()
std::timed_mutex g_tmtx;

void task1()
{
	std::cout << "g_tmtx: Task1 trying to lock the mutex\n";
	std::lock_guard<std::timed_mutex> lock(g_tmtx);
	std::cout << "g_tmtx: Task1 locks the mutex\n";
	std::this_thread::sleep_for(5s);
	std::cout << "g_tmtx: Task1 unlocking the mutex\n";
}

void task2()
{
	std::this_thread::sleep_for(500ms);
	std::cout << "g_tmtx: Task2 trying to lock the mutex\n";

	std::unique_lock<std::timed_mutex> lock(g_tmtx, std::defer_lock);

	// Try for 1 second to lock the mutex
	while (!lock.try_lock_for(1s)) {
		// Returned false
		std::cout << "g_tmtx: Task2 could not lock the mutex\n";
		// Try again on the next iteration
	}

	// Returned true - the mutex is now locked

	// Start of critical section
	std::cout << "g_tmtx: Task2 has locked the mutex\n";
	// End of critical section
}

int main()
{
	std::thread thr1(bad_factorial, 10);
	std::thread thr2(bad_factorial, 11);

	thr1.join(); thr2.join();

  std::thread thr3(task1TimedMtx);
	std::thread thr4(task2TimedMtx);

  thr3.join(); thr4.join();

  std::thread thr5(task1TimedMtxUntil);
	std::thread thr6(task2TimedMtxUntil);

  thr5.join(); thr6.join();

  std::thread thr7(task1);
	std::thread thr8(task2);

  thr7.join(); thr8.join();

  return 0;
}