#ifndef COUNTDOWNLATCH_H
#define COUNTDOWNLATCH_H

#include "Mutex.h"
#include "Condition.h"

class CountDownLatch
{
public:
	explicit CountDownLatch(int count)
	 : m_mutex(), m_cond(m_mutex), m_count(count)
	{
	}
	void Wait();
	void CountDown();
protected:
	CountDownLatch(const CountDownLatch& other);
	CountDownLatch& operator=(const CountDownLatch& other);
private:
	mutable Mutex m_mutex;
	Condition m_cond;
	int m_count;
};

#endif
