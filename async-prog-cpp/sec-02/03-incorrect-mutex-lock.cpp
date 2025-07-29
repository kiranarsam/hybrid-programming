#include <deque>
#include <iostream>
#include <mutex>
#include <thread>

int main() {
    std::deque<int> dq;

    dq.push_back(1);
    dq.push_back(2);
    dq.push_back(3);

    dq.pop_front();

    std::cout << dq[0] << std::endl;

    std::mutex mtx;

    auto func = [&] {
        std::cout << "Lamda: entry\n";
        std::cout << "Lamda: locked\n";
        // double lock
        mtx.lock();
        std::cout << "Lamda: locking again (double locking)\n";
        mtx.lock(); // you cannot lock same mutex morethan once.
        std::cout << "Lamda: done double locking\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        // double unlock
        mtx.unlock();
        std::cout << "Lamda: release one lock\n";
        mtx.unlock();
        // mutex destroyed with the thread still running and owning the lock
        std::cout << "Lamda: entry\n";
    };

    std::thread t1(func);
    t1.join();
    return 0;
}