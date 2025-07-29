#include <algorithm>
#include <barrier>
#include <iostream>
#include <latch>
#include <numeric>
#include <thread>
#include <vector>
#include <syncstream>

#define sync_out std::osyncstream(std::cout) // C++20

void multiply_add_latch() {
    const int NUM_THREADS{3};

    std::latch map_latch{NUM_THREADS};
    std::latch reduce_latch{1};

    std::vector<int> numbers(3000);
    int sum{};
    std::iota(numbers.begin(), numbers.end(), 0);

    auto map_thread = [&](std::vector<int>& numbers, int start, int end) {
        for (int i = start; i < end; ++i) {
            numbers[i] *= 2;
        }

        map_latch.count_down();
    };

    auto reduce_thread = [&](const std::vector<int>& numbers, int& sum) {
        map_latch.wait();

        sum = std::accumulate(numbers.begin(), numbers.end(), 0);

        reduce_latch.count_down();
    };

    for (int i = 0; i < NUM_THREADS; ++i) {
        std::jthread t(map_thread, std::ref(numbers), 1000 * i, 1000 * (i + 1));
    }

    std::jthread t(reduce_thread, numbers, std::ref(sum));

    reduce_latch.wait();

    std::cout << "All threads finished. The total sum is: " << sum << '\n';
}

void multiply_add_barrier() {
    const int NUM_THREADS{3};

    std::vector<int> sum(3, 0);
    std::vector<int> numbers(3000);
    std::iota(numbers.begin(), numbers.end(), 0);

    std::barrier map_barrier{NUM_THREADS};

    auto worker_thread = [&](std::vector<int>& numbers, int start, int end, int id) {
        sync_out << "Thread " << id << " is starting...\n";

        for (int i = start; i < end; ++i) {
            numbers[i] *= 2;
        }

        map_barrier.arrive_and_wait();

        for (int i = start; i < end; ++i) {
            sum[id] += numbers[i];
        }

        auto tk = map_barrier.arrive();
        (void) tk;
    };

    std::vector<std::jthread> workers;
    for (int i = 0; i < NUM_THREADS; ++i) {
        workers.emplace_back(worker_thread, std::ref(numbers), 1000 * i, 1000 * (i + 1), i);
    }

    for (auto& t : workers) {
        t.join();
    }

    sync_out << "All threads finished. The total sum is: "
             << std::accumulate(sum.begin(), sum.end(), 0) << "\n";
}

int main() {
    std::cout << "Multiplying and reducing vector using barriers..." << std::endl;
    multiply_add_barrier();

    std::cout << "Multiplying and reducing vector using latches..." << std::endl;
    multiply_add_latch();
    return 0;
}
