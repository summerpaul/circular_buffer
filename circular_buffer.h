/**
 * @Author: Xia Yunkai
 * @Date:   2024-09-02 13:48:51
 * @Last Modified by:   Xia Yunkai
 * @Last Modified time: 2024-11-04 19:22:06
 */

#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <vector>
#include <cassert>
#include <iostream>
#include <limits>

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
	CircularBuffer(int size = 15)
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

	void PopFront()
	{
		if (m_size > 0)
		{
			m_head = (m_head + 1) % m_capacity;
			m_size--;
		}
	}

	int GetClosestTimeIndex(const Time &time, const Time &eps)
	{
		int minDistance = INT_MAX;
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

	int GetGetClosestPreTimeIndex(const Time &time, const Time &eps)
	{
		int minDistance = 1000;
		int minIndex = 0;
		for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
		{
			int distance =m_timeBuffer[i] - time;
			if (distance < 0)
			{
				distance = -distance;
			}
			if (distance < minDistance && m_timeBuffer[i] < time)
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

	int GetTimeIndex(const Time &time)
	{
		int index = -1;
		for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
		{
			if (m_timeBuffer[i] == time)
			{
				index = i;
				break;
			}
		}

		return index;
	}

	bool IsHead(const int index)
	{
		return index == m_head;
	}

	const T &Get(int index) const
	{
		assert(index >= 0 && index < m_capacity);
		int trueIndex = (m_head + index) % m_capacity;
		return m_buffer[trueIndex];
	}

	const T &GetHeadData() const
	{
		assert(m_head >= 0 && m_head < m_capacity);
		return m_buffer[m_head];
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

	std::vector<T *> GetBufferPointArray() const
	{
		std::vector<T *> buff;
		for (int i = m_head; i != m_tail; i = (i + 1) % m_capacity)
		{
			buff.push_back(&m_buffer[i]);
		}
		return buff;
	}

	const int Size() const
	{
		return m_size;
	}
};
#endif /* __CIRCULAR_BUFFER_H__ */
