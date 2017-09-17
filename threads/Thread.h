#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

typedef void* (*StartRoutine)(void*);

class Thread
{
public:
	Thread(StartRoutine func, void* arg);
	~Thread();
	int Start();
	int Join();

private:
	pthread_t m_tid;
	StartRoutine m_func;
	void* m_arg;
};

namespace CurrentThread
{
pid_t tid();
}

#endif
