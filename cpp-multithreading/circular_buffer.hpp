#ifndef _CIRCULAR_BUFFER_HPP_
#define _CIRCULAR_BUFFER_HPP_

#include <vector>

template <typename T>
class CircularBuffer
{
public:
    CircularBuffer() : m_front(-1), m_back(-1), m_count(0)
    {
    }

    void resize(int32_t max_size) {
        checkSize(max_size);
    }

    void push(T &&task)
    {
        if (empty()) {
            m_back = m_front = 0;
        } else {
            m_back = (m_back + 1) % m_max_size;
        }

        m_buffer[m_back] = std::move(task);
        ++m_count;
    }

    void pop()
    {
        if (m_front == m_back) {
            m_front = m_back = -1;
            m_count = 0;
        } else {
            m_front = (m_front + 1) % m_max_size;
            --m_count;
        }
    }

    T &&front() { return std::move(m_buffer[m_front]); }
    bool empty() { return m_count == 0; }
    bool full() { return m_count == m_max_size; }
    int32_t size() { return m_count; }
    int32_t max_size() { return m_max_size; }

    void clear()
    {
        m_buffer.clear();
        m_count = 0;
        m_front = -1;
        m_back = -1;
    }

private:
    int32_t m_max_size;
    std::vector<T> m_buffer;
    int32_t m_front;
    int32_t m_back;
    int32_t m_count;

    void checkSize(int32_t size)
    {
        if (size <= 0) {
            m_max_size = 0;
            std::cerr << "CircularBuffer: Invalid buffer\n";
        } else {
            m_max_size = size;
        }

        m_buffer.resize((uint32_t)m_max_size);
    }
};

#endif /*_CIRCULAR_BUFFER_HPP_*/