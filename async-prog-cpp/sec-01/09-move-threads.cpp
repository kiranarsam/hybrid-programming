#include <chrono>
#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;

void func() {
    for (auto idx = 0; idx < 10; ++idx) {
        sync_cout << "Thread ID: " << std::this_thread::get_id() << " is working." << std::endl;
        std::this_thread::sleep_for(500ms);
    }
}

int main() {
    std::thread t1(func);
    sync_cout  << "T1 id: " << t1.get_id() << std::endl;
    std::this_thread::sleep_for(1s);

    // Thread 1 moved to thread 2. It keeps the same ID, and t1 is no longer joinable.
    std::thread t2 = std::move(t1);

    sync_cout  << "T2 id: " << t2.get_id() << std::endl;
    std::this_thread::sleep_for(1s);

    // Check whether threads are joinable or not, when moved from one object to another object
    sync_cout << "Are threads joinable? t1=" << t1.joinable() << "  t2=" << t2.joinable() << std::endl;

    t2.join();

    return 0;
}
