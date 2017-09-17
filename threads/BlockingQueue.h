#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <assert.h>
#include <queue>
#include "Mutex.h"
#include "Condition.h"

template<typename T>
class BlockingQueue
{
public:
	BlockingQueue()
	 : m_mutex(), m_cond(m_mutex), m_queue()
	{
	}
	
	~BlockingQueue()
	{
	}

	int Size() const
	{
		return m_queue.size();
	}

	void Put(const T& value)
	{
		MutexLock lock(m_mutex);
		m_queue.push(value);
		m_cond.Signal();
	}

	T Take()
	{
		MutexLock lock(m_mutex);
		//always use a while loop, due to spurious wakeup(wakeup but no data)
		while (m_queue.empty())
		{
			m_cond.Wait();
		}
		assert(!m_queue.empty());
		T value = m_queue.front();
		m_queue.pop();
		return value;
	}

protected:
	BlockingQueue(const BlockingQueue& other);
	BlockingQueue& operator=(const BlockingQueue& other);

private:
	mutable Mutex m_mutex;
	Condition m_cond;
	std::queue<T> m_queue;
};

#endif
