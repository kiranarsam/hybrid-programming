#include <chrono>
#include <functional>
#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;

using Callback = std::function<void(void)>;

class Counter {
   public:
    // Constructor
    Counter(const Callback &callback)
    {
        sync_cout << "Counter: Starting..." << std::endl;
        m_thd = std::jthread([&]() {
            while (m_running.load() == true) {
                sync_cout << "Counter: Running callback..." << std::endl;
                callback();
                std::this_thread::sleep_for(1s);
            }
            sync_cout << "Counter: Exit" << std::endl;
        });
    }

    void stop()
    {
        m_running.store(false);
    }

   private:
    std::jthread m_thd;
    std::atomic_bool m_running{true};
};

int main() {
    // Create timer executing callback function every 500ms
    sync_cout << "Main: Create Counter\n";
    Counter counter([]() {
        sync_cout << "Callback: Running...\n";
    });

    // Wait main thread for 3 seconds
    std::this_thread::sleep_for(3s);

    // Stop counter and wait for 1 second
    counter.stop();
    std::this_thread::sleep_for(1s);

    sync_cout << "Main thread: Exit\n";
    return 0;
}
