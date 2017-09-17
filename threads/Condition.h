#ifndef CONDITION_H
#define CONDITION_H

#include "Mutex.h"
#include <unistd.h>
#include <syscall.h>
#include <iostream>

class Condition
{
public:
	explicit Condition(Mutex& mutex)
	 : m_mutex(mutex)
	{
		pthread_cond_init(&m_cond, NULL);
	}
	~Condition()
	{
		pthread_cond_destroy(&m_cond);
	}
	void Wait()
	{
		pthread_cond_wait(&m_cond, m_mutex.getThreadMutex());	//wait这一步会原子性的释放mutex，并在执行完毕后自动加锁
		std::cout << syscall(SYS_gettid) << " Wait() one\n";
	}
	void Signal()
	{
		pthread_cond_signal(&m_cond);
		std::cout << "Signal()\n";
	}
	void Broadcast()
	{
		pthread_cond_broadcast(&m_cond);
		std::cout << "Broadcast()\n";
	}
private:
	Mutex& m_mutex;
	pthread_cond_t m_cond;
};

#endif
