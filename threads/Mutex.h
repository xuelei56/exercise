//MutexLock and MutexLockGuard
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include <unistd.h>
#include <syscall.h>
#include <assert.h>
#include <iostream>

class MutexLock
{
public:
	MutexLock()
	 : m_holder(0)
	{
		pthread_mutexattr_init(&m_mutexattr);
		pthread_mutexattr_settype(&m_mutexattr, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&m_mutex, &m_mutexattr);
	}
	
	~MutexLock()
	{
		assert(m_holder == 0);
		pthread_mutex_destroy(&m_mutex);
		pthread_mutexattr_destroy(&m_mutexattr);
	}

	void Lock()
	{
		pthread_mutex_lock(&m_mutex);
		m_holder = syscall(SYS_gettid);
	//	std::cout << m_holder << " lock{" << std::endl;
	}

	void UnLock()
	{
	//	std::cout << m_holder << " }unlock" << std::endl;
		m_holder = 0;
		pthread_mutex_unlock(&m_mutex);
	}

	pthread_mutex_t* getThreadMutex() 
	{
		return &m_mutex;
	}

protected:
	MutexLock(const MutexLock& other);
	MutexLock& operator=(const MutexLock& other);

private:
	pthread_mutexattr_t m_mutexattr;
	pthread_mutex_t m_mutex;
	pid_t m_holder;
};

class MutexLockGuard
{
public:
	explicit MutexLockGuard(MutexLock& ml)
	 : m_ml(ml)
	{
		m_ml.Lock();
	}
	~MutexLockGuard()
	{ 
		m_ml.UnLock();
	}

protected:
	MutexLockGuard(const MutexLockGuard& other);
	MutexLockGuard& operator=(const MutexLockGuard& other);

private:
	MutexLock& m_ml;
};

#endif
