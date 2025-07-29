#include <iostream>
#include <thread>
#include <vector>

// Using normal function
void func() {
    std::cout << "Using function pointer\n";
}

// Using functor
class FuncObjectClass {
public:
    void operator()() {
        std::cout << "Using function object class\n";
    }
};

// Start thread 5 using a non-static member function
class Obj {
public:
    void func() {
        std::cout << "Using a non-static member function\n";
    }
    static void static_func() {
        std::cout << "Using a static member function\n";
    }
};

int main() {

    std::vector<std::thread> threads;
    // Start thread 1 using a function pointer.
    std::thread t1(func);
    threads.push_back(std::move(t1));

    // Start thread 2 using a lambda function [](){}
    auto lambda_func = []() {
        std::cout << "Using lambda function\n";
    };
    std::thread t2(lambda_func);
    threads.push_back(std::move(t2));

    // Start thread 3 using an embedded lambda function [](){}
    std::thread t3([]() {
        std::cout << "Using embedded lambda function\n";
    });
    threads.push_back(std::move(t3));

    // Start thread 4 using a function object (overloading operator() )
    // FuncObjectClass obj1;
    std::thread t4{FuncObjectClass()};
    threads.push_back(std::move(t4));

    Obj obj2;

    // In this case, the first argument is the reference to the function
    // and second is the object reference.
    std::thread t5(&Obj::func, &obj2);
    threads.push_back(std::move(t5));

    // Start thread 6 using a static member function. Only the first argument is needed.
    std::thread t6(&Obj::static_func);
    threads.push_back(std::move(t6));

    // Wait threads to finish
    for(auto & thd : threads) {
        thd.join();
    }

    return 0;
}