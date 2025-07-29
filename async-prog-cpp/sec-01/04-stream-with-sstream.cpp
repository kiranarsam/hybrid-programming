#include <iostream>
#include <sstream>
#include <thread>

int main() {
    // Thread with embedded lambda function, using string stream for synchronization
    std::thread t1([]() {
        for (int i = 0; i < 10; ++i) {
            std::ostringstream oss;
            oss << "1 " << "2 " << "3 " << "4 " << "\n";
            std::cout << oss.str();
        }
    });

    // Thread with embedded lambda function, using string stream for synchronization
    std::thread t2([]() {
        for (int i = 0; i < 10; ++i) {
            std::ostringstream oss;
            oss << "5 " << "6 " << "7 " << "8 " << "\n";
            std::cout << oss.str();
        }
    });

    // Wait for threads to join
    t1.join();
    t2.join();

    return 0;
}
