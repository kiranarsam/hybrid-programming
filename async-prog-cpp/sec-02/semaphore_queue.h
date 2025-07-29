#pragma once

#include <mutex>
#include <semaphore> // C++20
#include <vector>

namespace async_prog {

template <typename T>
class SemaphoreQueue {
   public:
    SemaphoreQueue(std::size_t capacity)
        : m_sem_empty(capacity), m_sem_full(0), m_capacity{capacity}, m_buffer(capacity) {}

    void push(const T& item) {
        m_sem_empty.acquire();

        std::unique_lock<std::mutex> lock(m_mtx);

        m_buffer[m_tail] = item;
        m_tail = next(m_tail);

        lock.unlock();

        m_sem_full.release();
    }

    bool try_push(const T& item) {
        if (!m_sem_empty.try_acquire()) {
            return false;
        }

        std::unique_lock<std::mutex> lock(m_mtx);

        m_buffer[m_tail] = item;
        m_tail = next(m_tail);

        lock.unlock();

        m_sem_full.release();

        return true;
    }

    void pop(T& item) {
        m_sem_full.acquire();

        std::unique_lock<std::mutex> lock(m_mtx);

        item = m_buffer[m_head];
        m_head = next(m_head);

        lock.unlock();

        m_sem_empty.release();
    }

    bool try_pop(T& item) {
        if (!m_sem_full.try_acquire()) {
            return false;
        }

        std::unique_lock<std::mutex> lock(m_mtx);

        item = m_buffer[m_head];
        m_head = next(m_head);

        lock.unlock();

        m_sem_empty.release();

        return true;
    }

   private:
    [[nodiscard]] std::size_t next(std::size_t idx) const noexcept { return ((idx + 1) % m_capacity); }

   private:
    std::mutex m_mtx;
    std::counting_semaphore<> m_sem_empty; // Counting semaphore
    std::counting_semaphore<> m_sem_full; // Counting Semaphore

    std::size_t m_head{0};
    std::size_t m_tail{0};
    std::size_t m_capacity;
    std::vector<T> m_buffer;
};

}  // namespace async_prog
