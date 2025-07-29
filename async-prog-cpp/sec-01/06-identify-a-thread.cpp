#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void func() {
    std::this_thread::sleep_for(1s);
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(1s);
}

int main() {
    std::thread t1(func);
    std::cout << "Main thread ID: " << std::this_thread::get_id() << std::endl;

    t1.join();
    return 0;
}
