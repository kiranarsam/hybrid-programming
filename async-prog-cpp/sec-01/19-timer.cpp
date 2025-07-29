#include <chrono>
#include <functional>
#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;
using namespace std::chrono;

using Callback = std::function<void(void)>;

template<typename Duration>
class Timer {
   public:
    Timer(const Duration interval, const Callback& callback) {
        auto value = duration_cast<milliseconds>(interval);
        sync_cout << "Timer: Starting with interval of " << value << std::endl;

        m_thd = std::jthread([&](std::stop_token stop_token) {
            while (!stop_token.stop_requested()) {
                sync_cout << "Timer: Running callback " << m_counter.load() << " ...\n";
                m_counter++;
                callback();

                sync_cout << "Timer: Sleeping...\n";
                std::this_thread::sleep_for(interval);
            }
            sync_cout << "Timer: Exit\n";
        });
    }

    void stop() {
        m_thd.request_stop();
    }

   private:
    std::jthread m_thd;
    std::atomic_int32_t m_counter{0};
};

int main(void) {
    // Create timer executing callback function every second
    sync_cout << "Main: Create timer\n";
    Timer timer(1s, [&]() {
        sync_cout << "Callback: Running...\n";
    });

    // Wait main thread for 3 seconds
    std::this_thread::sleep_for(3s);

    // Stop timer
    sync_cout << "Main thread: Stop timer\n";
    timer.stop();

    // Wait main thread for 500ms while timer stops
    std::this_thread::sleep_for(500ms);
    sync_cout << "Main thread: Exit\n";
    return 0;
}
