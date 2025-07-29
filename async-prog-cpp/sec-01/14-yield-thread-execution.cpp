#include <iostream>
#include <random>
#include <string>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;

namespace {
    std::mutex mtx;
}

int main() {
    auto work = [&](const std::string& name) {

        while (true)
        {
            bool work_to_do = rand() % 2;
            if (work_to_do) {
                // Do some work: Active wait for 3 second
                sync_cout << name << ": working\n";
                std::lock_guard<std::mutex> lock(mtx);
                std::this_thread::sleep_for(std::chrono::seconds(2s));
            } else {
                // Let other threads do some work
                sync_cout << name << ": yielding\n";
                std::this_thread::yield();
                sync_cout << name << ": continuing after yield \n";
                std::this_thread::sleep_for(std::chrono::milliseconds(300ms));
            }
        }
    };

    // These threads will work forever as there is no exit condition in the work lambda
    std::jthread t1(work, "T1");
    std::jthread t2(work, "T2");

    return 0;
}