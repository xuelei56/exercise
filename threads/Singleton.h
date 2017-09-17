#ifndef SINGLETON_H
#define SINGLETON_H

#include <pthread.h>

template<typename T>
class Singleton
{
public:
	static T& getInstance()
	{
		pthread_once(&m_ponce, &Singleton<T>::Init);
		return *m_value;
	}
	static void Init()
	{
		m_value = new T();
	}

private:
	Singleton();
	~Singleton();
	Singleton(const Singleton& other);
	Singleton& operator=(const Singleton& other);

	static pthread_once_t m_ponce;
	static T* m_value;
};

template<typename T>
pthread_once_t Singleton<T>::m_ponce = PTHREAD_ONCE_INIT; 

template<typename T>
T* Singleton<T>::m_value = NULL;

#endif
