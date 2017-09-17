//Mutex and MutexLock
#ifndef MUTEX_H
#define MUTEX_H

#include <pthread.h>
#include <unistd.h>
#include <syscall.h>
#include <assert.h>
#include <iostream>

class Mutex
{
public:
	Mutex()
	 : m_holder(0)
	{
		pthread_mutexattr_init(&m_mutexattr);
		pthread_mutexattr_settype(&m_mutexattr, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&m_mutex, &m_mutexattr);
	}
	
	~Mutex()
	{
		assert(m_holder == 0);
		pthread_mutex_destroy(&m_mutex);
		pthread_mutexattr_destroy(&m_mutexattr);
	}

	void Lock()
	{
		pthread_mutex_lock(&m_mutex);
		m_holder = syscall(SYS_gettid);
	}

	void UnLock()
	{
		m_holder = 0;
		pthread_mutex_unlock(&m_mutex);
	}

	pthread_mutex_t* getThreadMutex() 
	{
		return &m_mutex;
	}

	bool IsLockedByThisThread()
	{
		return m_holder == syscall(SYS_gettid);
	}

	void AssertLocked()
	{
		assert(IsLockedByThisThread());
	}

protected:
	Mutex(const Mutex& other);
	Mutex& operator=(const Mutex& other);

private:
	pthread_mutexattr_t m_mutexattr;
	pthread_mutex_t m_mutex;
	pid_t m_holder;
};

class MutexLock
{
public:
	explicit MutexLock(Mutex& mutex)
	 : m_mutex(mutex)
	{
		m_mutex.Lock();
	}
	~MutexLock()
	{ 
		m_mutex.UnLock();
	}

protected:
	MutexLock(const MutexLock& other);
	MutexLock& operator=(const MutexLock& other);

private:
	Mutex& m_mutex;
};

#define MutexLock(x) static_assert(false, "missing MutexLock var name")

#endif
