#include <iostream>
#include <mutex>
#include <thread>

namespace {

std::mutex mtx;
int counter = 0;

}

int main() {
    // lambda function without lock
    auto funcWithoutLocks = [] {
        for (int i = 0; i < 1000000; ++i) {
            ++counter;
        };
    };

    // lambda function with lock
    auto funcWithLocks = [] {
        for (int i = 0; i < 1000000; ++i) {
            mtx.lock();
            ++counter;
            mtx.unlock();
        };
    };

    {
        counter = 0;
        std::thread t1(funcWithoutLocks);
        std::thread t2(funcWithoutLocks);

        t1.join();
        t2.join();

        std::cout << "Counter without using locks: " << counter << std::endl;
    }
    {
        counter = 0;
        std::thread t1(funcWithLocks);
        std::thread t2(funcWithLocks);

        t1.join();
        t2.join();

        std::cout << "Counter using locks: " << counter << std::endl;
    }

    return 0;
}