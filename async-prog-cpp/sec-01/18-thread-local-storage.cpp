#include <iostream>
#include <syncstream> // C++20
#include <thread>
#include <string_view>

#define sync_cout std::osyncstream(std::cout) // C++20

// thread local variable will have its own copy in its thread enviroment.
thread_local int val = 0;

void setValue(int newval)
{
    val = newval;
}

void printValue()
{
    sync_cout << val << " \n";
}

void multiplyByTwo(int arg, std::string_view name)
{
    // The thread_local value is set and multiplied by 2
    sync_cout << name << ": entry, address val = " << &val << "\n";
    setValue(arg);
    val *= 2;
    printValue();

    sync_cout << name << ": exit\n";
}

int main() {
    val = 1;  // Value in main thread

    // Each thread set its own value
    std::thread t1(multiplyByTwo, 10, "T1");
    std::thread t2(multiplyByTwo, 20, "T2");
    std::thread t3(multiplyByTwo, 30, "T3");

    t1.join();
    t2.join();
    t3.join();

    std::cout << val << std::endl;

    return 0;
}