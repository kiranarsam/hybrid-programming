#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

void func() {
    std::this_thread::sleep_for(1s);
    std::cout << "Thread ID: " << std::this_thread::get_id() << std::endl;
}

int main() {
    std::jthread t(func); // jthread C++20
    std::cout << "Main Thread ID: " << std::this_thread::get_id() << std::endl;
    return 0;
}
