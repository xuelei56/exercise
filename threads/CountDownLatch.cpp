#include "CountDownLatch.h"

void CountDownLatch::Wait()
{
	MutexLock lock(m_mutex);
	while (m_count != 0)
	{
		m_cond.Wait();
	}
}

void CountDownLatch::CountDown()
{
	MutexLock lock(m_mutex);
	--m_count;
	if (m_count == 0)
		m_cond.Broadcast();
}
