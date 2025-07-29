#include <chrono>
#include <functional>
#include <iostream>
#include <syncstream> // C++20
#include <thread>

#define sync_cout std::osyncstream(std::cout) // C++20

using namespace std::chrono_literals;

using ThreadFunc = std::function<void(const std::string&)>;

class JthreadWrapper {
   public:
    JthreadWrapper(const ThreadFunc& func, const std::string& str)
        : m_thd(func, str), m_name(str) {
            sync_cout << "Thread " << m_name << " being created" << std::endl;
        }

    ~JthreadWrapper() {
        sync_cout << "Thread " << m_name << " being destroyed" << std::endl;
    }

   private:
    std::jthread m_thd; // C++20
    std::string m_name;
};

void func(const std::string& name) {
    sync_cout << "Thread " << name << " starting..." << std::endl;
    std::this_thread::sleep_for(1s);
    sync_cout << "Thread " << name << " finishing..." << std::endl;
}

int main() {
    JthreadWrapper t1(func, "t1");
    JthreadWrapper t2(func, "t2");
    JthreadWrapper t3(func, "t3");

    std::this_thread::sleep_for(2s);

    // t1, t2, t3 will be destroyed when main exits
    sync_cout << "Main thread exiting..." << std::endl;

    return 0;
}
