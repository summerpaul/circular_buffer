/**
 * @Author: Xia Yunkai
 * @Date:   2024-09-02 13:48:51
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-11-04 16:41:50
 */

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <vector>
template <typename T, typename Time>

class CircularBuffer
{
private:
    T *m_buffer;
    Time *m_timeBuffer;
    int m_head;
    int m_tail;
    int m_capacity;
    int m_size;

public:
    CircularBuffer(int size)
        : m_capacity(size), m_head(0), m_tail(0), m_size(0)
    {
        m_buffer = new T[m_capacity];
        m_timeBuffer = new Time[m_capacity];
    }
    ~CircularBuffer()
    {
        delete[] m_buffer;
        delete[] m_timeBuffer;
    }

    int capacity() const { return m_capacity; }

    void Add(const T &value)
    {
        if ((m_tail + 1) % m_capacity == m_head)
        {
            m_head = (m_head + 1) % m_capacity;
        }
        m_buffer[m_tail] = value;
        m_tail = (m_tail + 1) % m_capacity;
        if (m_size < m_capacity + 1)
        {
            m_size++;
        }
        else
        {
            m_size = m_capacity;
        }
    }

    void Add(const T &value, const Time &time)
    {
        if ((m_tail + 1) % m_capacity == m_head)
        {
            m_head = (m_head + 1) % m_capacity;
        }
        m_buffer[m_tail] = value;
        m_timeBuffer[m_tail] = time;
        m_tail = (m_tail + 1) % m_capacity;
        if (m_size < m_capacity + 1)
        {
            m_size++;
        }
        else
        {
            m_size = m_capacity;
        }
    }

    int GetClosestTimeIndex(const Time &time, const Time &eps)
    {
        int minDistance = std::numeric_limits<int>::max();
        int minIndex = 0;
        for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
        {
            int distance = std::abs(m_timeBuffer[i] - time);
            if (distance < minDistance)
            {
                minDistance = distance;
                minIndex = i;
            }
        }
        if (minDistance < eps)
        {
            return minIndex;
        }
        else
        {
            return -1; // not found
        }
    }

    const T &Get(int index) const
    {
        assert(index >= 0 && index < m_capacity);
        int trueIndex = (m_head + index) % m_capacity;
        return m_buffer[trueIndex];
    }

    std::vector<T> GetBufferArray()
    {
        std::vector<T> buff;
        for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
        {
            buff.emplace_back(m_buffer[i]);
        }
        return buff;
    }

    const int Size() const
    {
        return m_size;
    }
};
#endif /* __CIRCULAR_BUFFER_H__ */
