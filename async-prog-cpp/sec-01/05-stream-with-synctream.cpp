#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

int main() {

    std::thread t1([]() {
        for (int count = 0; count < 10; ++count) {
            sync_cout << "1 " << "2 " << "3 " << "4 " << std::endl;
        }
    });

    std::thread t2([]() {
        for (int count = 0; count < 10; ++count) {
            sync_cout << "5 " << "6 " << "7 " << "8 " << std::endl;
        }
    });

    // Wait for threads to join
    t1.join();
    t2.join();

    return 0;
}

// g++ -std=c++20 sample.cpp
