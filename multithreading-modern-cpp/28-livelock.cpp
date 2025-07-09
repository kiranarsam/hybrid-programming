// Livelock caused by poorly implemented deadlock avoidance
// If the thread cannot get a lock, sleep and try again
// However, all the threads wake up at the same time
// both threads are constantly trying to lock the mutexes, but none of them can make progress
#include <thread>
#include <mutex>
#include <iostream>
#include <string>
#include <chrono>

/* To Avoid Deadlocks and Livelocks
1. Lock ordering: Always lock mutexes in the same order to avoid deadlocks and livelocks.
2. Avoid busy-waiting: Instead of constantly trying to lock a mutex, use a condition variable to wait for the mutex to be unlocked.
3. Use a timeout: Set a timeout when trying to lock a mutex to avoid infinite waiting.
*/
using namespace std::literals;

std::mutex mut1, mut2;

// With Livelock
void funcA()
{
	std::this_thread::sleep_for(10ms);
	bool locked = false;
	while (!locked) {
		std::lock_guard<std::mutex> lck_guard(mut1);  // Lock mut1
		std::cout << "After you, Claude!\n";
		std::this_thread::sleep_for(2s);
		locked = mut2.try_lock();                     // Try to lock mut2
	}
	if (locked)
		std::cout << "ThreadA has locked both mutexes\n";
}

void funcB() {
	bool locked = false;
	while (!locked) {
		std::lock_guard<std::mutex> lck_guard(mut2);  // Lock mut2
		std::cout << "After you, Cecil!\n";
		std::this_thread::sleep_for(2s);
		locked = mut1.try_lock();                     // Try to lock mut1
	}
	if (locked)
		std::cout << "ThreadB has locked both mutexes\n";
}

std::mutex mtx1, mtx2;

// std::shared_lock and std::lock() avoid deadlock
// when locking multiple mutexes. They also avoid livelock.
void funcNoLivelock1() {
	std::this_thread::sleep_for(10ms);

	std::cout << "funcNoLivelock1: After you, Claude! \n;";
	std::scoped_lock scoped_lck(mtx1, mtx2);		 // Lock both mutexes
	std::this_thread::sleep_for(2s);
	std::cout << "funcNoLivelock1: Thread A has locked both mutexes\n";
}

void funcNoLivelock2() {
	std::cout << "funcNoLivelock2: After you, Cecil!\n";
	std::scoped_lock scoped_lck(mtx2, mtx1);		 // Lock both mutexes
	std::this_thread::sleep_for(2s);
	std::cout << "funcNoLivelock2: Thread B has locked both mutexes\n";
}

int main() {
	std::thread thrA(funcA);
	std::this_thread::sleep_for(10ms);
	std::thread thrB(funcB);

  std::thread thr1(funcNoLivelock1);
	std::this_thread::sleep_for(10ms);
	std::thread thr2(funcNoLivelock2);

  thr1.join(); thr2.join();

  // Not able join thrA and thrB, due to livelock
	thrA.join(); thrB.join();

  return 0;
}