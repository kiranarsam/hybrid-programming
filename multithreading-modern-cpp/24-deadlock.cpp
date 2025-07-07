#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

// Mutual deadlock
// Two threads wait for the other to unlock a mutex
std::mutex mut1;
std::mutex mut2;

void funcA()
{
	std::cout << "funcA: Thread A trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard(mut1);		// Acquire lock on mut1
	std::cout << "funcA: Thread A has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "funcA: Thread A trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(mut2);		// Wait for lock on mut2
	std::cout << "funcA: Thread A has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "funcA: Thread A releases all its locks\n";
}

void funcB()
{
	std::cout << "funcB: Thread B trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard1(mut2);	    // Acquire lock on mut2
	std::cout << "funcB: Thread B has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "funcB: Thread B trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard2(mut1);	    // Wait for lock on mut1
	std::cout << "funcB: Thread B has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "funcB: Thread B releases all its locks\n";
}

// Avoid deadlock by writing the threads
// so that they lock the mutexes in the same order
std::mutex g_mut1;
std::mutex g_mut2;

void funcAA()
{
	std::cout << "Thread A trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard(g_mut1);        // Acquire lock on mut1
	std::cout << "Thread A has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread A trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(g_mut2);       // Wait for lock on mut2
	std::cout << "Thread A has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread A releases all its locks\n";
}

void funcBB()
{
	std::cout << "Thread B trying to lock mutex 1...\n";
	std::lock_guard<std::mutex> lck_guard1(g_mut1);       // Acquire lock on mut1
	std::cout << "Thread B has locked mutex 1\n";
	std::this_thread::sleep_for(50ms);                  // Do some work
	std::cout << "Thread B trying to lock mutex 2...\n";
	std::lock_guard<std::mutex> lck_guard2(g_mut2);	    // Wait for lock on mut2
	std::cout << "Thread B has locked mutex 2\n";
	std::this_thread::sleep_for(50ms);	                // Do some work
	std::cout << "Thread B releases all its locks\n";
}

int main()
{
  // With Mutual Deadlock, if mutex is locked in different order
	std::thread thrA(funcA);
	std::thread thrB(funcB);

  // No Mutual Deadlock, if mutex is locked in same order
	// std::thread thrA(funcAA);
	// std::thread thrB(funcBB);

	thrA.join(); thrB.join();

  return 0;
}