#include <iostream>
#include <thread>

int main() {
    // Thread with embedded lambda function
    std::thread t1([]() {
        for (int count = 0; count < 10; ++count) {
            std::cout << "1 " << "2 " << "3 " << "4 " << std::endl;
        }
    });

    // second thread with embedded lambda function
    std::thread t2([]() {
        for (int count = 0; count < 10; ++count) {
            std::cout << "5 " << "6 " << "7 " << "8 " << std::endl;
        }
    });

    // Wait for the threads to join
    t1.join();
    t2.join();

    return 0;
}
