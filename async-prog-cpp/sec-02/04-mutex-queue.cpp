#include <chrono>
#include <iostream>
#include <thread>
#include <syncstream>

#include "mutex_queue.h"

#define sync_out std::osyncstream(std::cout) // c++20

void push_pop(std::size_t queue_size, int items, int producer_wait, int consumer_wait) {
    async_prog::Queue<int> queue(queue_size);

    std::jthread producer([&] {
        for (int i = 0; i < items; ++i) {
            queue.push(i);
            sync_out << "push_pop: Producer push " << i << "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(producer_wait));
        }
    });

    std::jthread consumer([&] {
        for (int i = 0; i < items; ++i) {
            int item{};
            queue.pop(item);
            sync_out << "push_pop: Consumer pop " << item << "\n";

            std::this_thread::sleep_for(std::chrono::milliseconds(consumer_wait));
        }
    });
}

void try_push_try_pop(std::size_t queue_size, int items, int producer_wait, int consumer_wait) {
    async_prog::Queue<int> queue(queue_size);

    std::jthread producer([&] {
        int i{};

        while (i < items) {
            if (queue.try_push(i)) {
                sync_out << "try_push_try_pop: Producer push " << i << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(producer_wait));

                ++i;
            }
        }
    });

    std::jthread consumer([&] {
        int i{};

        while (i < items) {
            int item{};

            if (queue.try_pop(item)) {
                sync_out << "try_push_try_pop: Consumer pop " << item << "\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(consumer_wait));

                ++i;
            }
        }
    });
}

int main() {
    push_pop(5, 20, 1, 5);
    try_push_try_pop(5, 20, 1, 5);

    return 0;
}