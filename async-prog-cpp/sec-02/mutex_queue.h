#pragma once

#include <condition_variable>
#include <mutex>
#include <vector>

namespace async_prog {

template <typename T>
class Queue {
   public:
    Queue(std::size_t capacity) : m_capacity{capacity}, m_buffer(capacity) {}

    // While push tail will move forward
    void push(const T& item) {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_not_full.wait(lock, [this] { return !is_full(); });

        m_buffer[m_tail] = item;
        m_tail = next(m_tail);

        lock.unlock();

        m_not_empty.notify_one();
    }

    bool try_push(const T& item) {
        std::unique_lock<std::mutex> lock(m_mtx, std::try_to_lock);
        if (!lock || is_full()) {
            return false;
        }

        m_buffer[m_tail] = item;
        m_tail = next(m_tail);

        lock.unlock();

        m_not_empty.notify_one();

        return true;
    }

    // While pop head is moved forward
    void pop(T& item) {
        std::unique_lock<std::mutex> lock(m_mtx);
        m_not_empty.wait(lock, [this] { return !is_empty(); });

        item = m_buffer[m_head];
        m_head = next(m_head);

        lock.unlock();

        m_not_full.notify_one();
    }

    bool try_pop(T& item) {
        std::unique_lock<std::mutex> lock(m_mtx, std::try_to_lock);
        if (!lock || is_empty()) {
            return false;
        }

        item = m_buffer[m_head];
        m_head = next(m_head);

        lock.unlock();

        m_not_empty.notify_one();

        return true;
    }

   private:
    [[nodiscard]] std::size_t next(std::size_t idx) const noexcept { return ((idx + 1) % m_capacity); }

    [[nodiscard]] bool is_empty() const noexcept { return (m_head == m_tail); }

    [[nodiscard]] bool is_full() const noexcept { return (next(m_tail) == m_head); }

   private:
    std::mutex m_mtx;
    std::condition_variable m_not_empty;
    std::condition_variable m_not_full;

    std::size_t m_head{0};
    std::size_t m_tail{0};
    std::size_t m_capacity;
    std::vector<T> m_buffer;
};

}  // namespace async_prog
