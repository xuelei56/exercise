//MutexLock and MutexLockGuard
#include <pthread.h>
#include <iostream>

class MutexLock
{
public:
	MutexLock()
	{
		pthread_mutexattr_init(&m_mutexattr);
		pthread_mutexattr_settype(&m_mutexattr, PTHREAD_MUTEX_NORMAL);
		pthread_mutex_init(&m_mutex, &m_mutexattr);
	}
	
	~MutexLock()
	{
		pthread_mutex_destroy(&m_mutex);
		pthread_mutexattr_destroy(&m_mutexattr);
	}

	void Lock()
	{
		std::cout << "lock()" << std::endl;
		pthread_mutex_lock(&m_mutex);
	}

	void UnLock()
	{
		pthread_mutex_unlock(&m_mutex);
		std::cout << "unlock()" << std::endl;
	}

protected:
	MutexLock(const MutexLock& other);
	MutexLock& operator=(const MutexLock& other);

private:
	pthread_mutexattr_t m_mutexattr;
	pthread_mutex_t m_mutex;
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
