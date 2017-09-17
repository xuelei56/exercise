#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <queue>
#include <vector>
#include "Mutex.h"
#include "Condition.h"

typedef void* (*Task)(void*);

class Thread;

class ThreadPool
{
public:
	explicit ThreadPool();
	~ThreadPool();
	void Start(int threadNum);
	void Stop();
	void Put(const Task task);
	void* ThreadProc(void* arg);

protected:
	ThreadPool(const ThreadPool& other);
	ThreadPool& operator=(const ThreadPool& other);

private:
	Task TakeOne();

private:
	Mutex m_mutex;
	Condition m_cond;
	std::queue<Task> m_tasks;
	std::vector<Thread*> m_threads;
	bool m_running;
};

#endif
