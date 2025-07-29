#include <chrono>
#include <iostream>
#include <thread>
#include <syncstream> // C++20

#include "semaphore_queue.h"

#define sync_out std::osyncstream(std::cout) // C++20

void push_pop(std::size_t capacity, int items, int producer_wait, int consumer_wait) {
    async_prog::SemaphoreQueue<int> queue(capacity);

    std::jthread t1([&] {
        for (int i = 0; i < items; ++i) {
            queue.push(i);
            sync_out << "push_pop: Producer push " << i << "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(producer_wait));
        }
    });

    std::jthread t2([&] {
        for (int i = 0; i < items; ++i) {
            int item{};
            queue.pop(item);
            sync_out << "push_pop: Consumer pop " << item << "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(consumer_wait));
        }
    });
}

void try_push_pop(std::size_t capacity, int items, int producer_wait, int consumer_wait) {
    async_prog::SemaphoreQueue<int> queue(capacity);

    std::jthread t1([&] {
        int i{};

        while (i < items) {
            if (!queue.try_push(i)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(producer_wait));
            } else {
                sync_out << "try_push_pop: Producer push " << i << "\n";
                ++i;
            }
        }
    });

    std::jthread t2([&] {
        int i{};
        while (i < items) {
            int item{};
            if (!queue.try_pop(item)) {
                std::this_thread::sleep_for(std::chrono::milliseconds(consumer_wait));
            } else {
                sync_out << "try_push_pop: Consumer pop " << item << "\n";
                ++i;
            }
        }
    });
}

int main() {
    auto pre = std::chrono::high_resolution_clock::now();
    push_pop(5, 10, 1, 1);
    auto post = std::chrono::high_resolution_clock::now();

    auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(post - pre);
    sync_out << "push/pop took " << millisec.count() << " to process " << 10 << "items\n";

    pre = std::chrono::high_resolution_clock::now();
    try_push_pop(5, 10, 1, 1);
    post = std::chrono::high_resolution_clock::now();

    millisec = std::chrono::duration_cast<std::chrono::milliseconds>(post - pre);
    sync_out << "try_push/try_pop took " << millisec.count() << " to process " << 10 << "items\n";

    return 0;
}