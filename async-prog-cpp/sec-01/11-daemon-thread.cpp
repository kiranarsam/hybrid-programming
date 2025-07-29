#include <chrono>
#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;

namespace {

int timeout = 3;

}

void daemonThread() {
    sync_cout << "Daemon thread starting...\n";
    while (timeout-- > 0) {
        sync_cout << "Daemon thread is running...\n";
        std::this_thread::sleep_for(1s);
    }
    sync_cout << "Daemon thread exiting...\n";
}

int main() {
    std::thread t(daemonThread);
    t.detach(); // Thread is detached. Acts as Daemon thread

    std::this_thread::sleep_for(std::chrono::seconds(timeout + 1));

    sync_cout << "Main thread exiting...\n";
    return 0;
}
