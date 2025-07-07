#include <thread>
#include <mutex>
#include <iostream>
#include <chrono>

using namespace std::literals;

std::mutex mut1;
std::mutex mut2;

// Use std::defer_lock and std::try_lock() to avoid deadlock
void funcA()
{
  std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // ...but don’t lock it yet

	std::cout << "funcA: Thread A trying to lock mutexes 1 and 2...\n";

	// Now lock both of them
	auto idx = std::try_lock(uniq_lk1, uniq_lk2);
	if (idx != -1)
  {
		std::cout << "funcA: try_lock failed on mutex with index " << idx << '\n';
	}
	else
  {
		std::cout << "funcA: Thread A has locked mutexes 1 and 2\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "funcA: Thread A releasing mutexes 1 and 2...\n";
	}
}

void funcB() {
    std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);   // Associate mutex with lock...
    std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);   // ...but don’t lock it yet

	std::cout << "funcB: Thread B trying to lock mutexes 2 and 1...\n";

	// Now lock both of them
	auto idx = std::try_lock(uniq_lk2, uniq_lk1);
	if (idx != -1) {
		std::cout << "funcB: try_lock failed on mutex with index " << idx << '\n';
	}
	else {
		std::cout << "funcB: Thread B has locked mutexes 2 and 1\n";
		std::this_thread::sleep_for(50ms);
		std::cout << "funcB: Thread B releasing mutexes 2 and 1...\n";
	}
}

// Use std::adopt_lock to avoid deadlock
void funcAA()
{
	std::cout << "funcAA: Thread A trying to lock mutexes 1 and 2...\n";
	std::lock(mut1, mut2);				               // Lock both mutexes
	std::cout << "funcAA: Thread A has locked mutexes 1 and 2\n";

	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::cout << "funcAA: Thread A has adopted the locks\n";

	std::this_thread::sleep_for(50ms);
	std::cout << "funcAA: Thread A releasing mutexes 1 and 2...\n";
}

void funcBB() {
	std::cout << "funcBB: Thread B trying to lock mutexes 2 and 1...\n";
	std::lock(mut2, mut1);				               // Lock both mutexes
	std::cout << "funcBB: Thread B has locked mutexes 2 and 1\n";

	// Adopt the locks
	std::unique_lock<std::mutex> uniq_lk2(mut2, std::adopt_lock);   // with a unique_lock
	std::unique_lock<std::mutex> uniq_lk1(mut1, std::adopt_lock);   // Associate each mutex
	std::cout << "funcBB: Thread B has adopted the locks\n";

	std::this_thread::sleep_for(50ms);
	std::cout << "funcBB: Thread B releasing mutexes 2 and 1...\n";
}

// Use std::defer_lock to avoid deadlock
void funcAD()
{
  std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);	// Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);	// ...but don’t lock it yet

	std::cout << "funcAD: Thread A trying to lock mutexes 1 and 2...\n";
  std::lock(uniq_lk1, uniq_lk2);								    // Now lock both of them
	std::cout << "funcAD: Thread A has locked mutexes 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "funcAD: Thread A releasing mutexes 1 and 2...\n";
}

void funcBD() {
  std::unique_lock<std::mutex> uniq_lk2(mut2, std::defer_lock);	// Associate mutex with lock...
  std::unique_lock<std::mutex> uniq_lk1(mut1, std::defer_lock);	// ...but don’t lock it yet

	std::cout << "funcAD: Thread B trying to lock mutexes 2 and 1...\n";
  std::lock(uniq_lk2, uniq_lk1);									// Now lock both of them
	std::cout << "funcAD: Thread B has locked mutexes 2 and 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "funcAD: Thread B releasing mutexes 2 and 1...\n";
}

//Using std::scoped_lock to avoid deadlock
void funcAS()
{
	std::cout << "funcAS: Thread A trying to lock mutexes 1 and 2...\n";
	std::scoped_lock scoped_lck(mut1, mut2);
	std::cout << "funcAS: Thread A has locked mutexes 1 and 2\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "funcAS: Thread A releasing mutexes 1 and 2...\n";
}

void funcBS()
{
	std::cout << "funcBS: Thread B trying to lock mutexes 2 and 1...\n";
	std::scoped_lock scoped_lck(mut2, mut1);
	std::cout << "funcBS: Thread B has locked mutexes 2 and 1\n";
	std::this_thread::sleep_for(50ms);
	std::cout << "funcBS: Thread B releasing mutexes 2 and 1...\n";
}


int main() {

  // std::try_lock() with std::defer_lock of std::unique_lock
	std::thread thrA(funcA);
	std::thread thrB(funcB);

	thrA.join(); thrB.join();

  // std::lock() with std::adopt_lock of std::unique_lock
  std::thread thrAA(funcAA);
	std::thread thrBB(funcBB);

	thrAA.join(); thrBB.join();

  // std::lock() with std::defer_lock of std::unique_lock
  std::thread thrAD(funcAD);
	std::thread thrBD(funcBD);

	thrAD.join(); thrBD.join();

  // std::scoped_lock
  std::thread thrAS(funcAS);
	std::thread thrBS(funcBS);

	thrAS.join(); thrBS.join();

  return 0;
}