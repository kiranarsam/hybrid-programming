#include <iostream>
#include <mutex>
#include <thread>

namespace {

std::mutex mtx;
uint32_t counter{};

}

void function_throws()
{
    throw std::runtime_error("Error throwing from functions_throws()");
}

int main() {
    auto worker = [] {
        for (int i = 0; i < 1000000; ++i) {
            mtx.lock();
            counter++;
            mtx.unlock();
        }
    };

    auto worker_try = [] {
        int i = 0;
        while (i < 1000000) {
            if (mtx.try_lock()) {
                ++counter;
                ++i;
                mtx.unlock();
            }
        }
    };

    auto worker_exceptions = [] {
        for (int i = 0; i < 1000000; ++i) {
            try {
                std::lock_guard<std::mutex> lock(mtx);
                counter++;
                function_throws();
            } catch (std::system_error& e) {
                std::cout << e.what() << std::endl;
                return;
            } catch (const std::exception &e) {
                std::cout << "Caught Error: " << e.what() << std::endl;
                return;
            }
        }
    };

    std::thread t1(worker);
    std::thread t2(worker_exceptions);
    std::thread t3(worker_try);

    t1.join();
    t2.join();
    t3.join();

    std::cout << "Final counter value: " << counter << "\n";

    return 0;
}