#include "ThreadPool.h"
#include <assert.h>
#include "Thread.h"

void* ThreadFunc(void* arg)
{
	ThreadPool* pool = (ThreadPool*)arg;
	//TODO: pass NULL, loss data!
	return pool->ThreadProc(NULL);
}

ThreadPool::ThreadPool()
	: m_mutex(),
	m_cond(m_mutex),
	m_running(false)
{
}

ThreadPool::~ThreadPool()
{
}

void* ThreadPool::ThreadProc(void* arg)
{
	while (m_running)
	{
		Task task = TakeOne();
		if (task != NULL)
			task(NULL);
	}
	return NULL;
}

Task ThreadPool::TakeOne()
{
	MutexLock lock(m_mutex);
	while (m_tasks.empty() && m_running)
	{
		m_cond.Wait();
	}

	if (!m_tasks.empty())
	{
		Task task = m_tasks.front();
		m_tasks.pop();
		return task;
	}
	else
	{
		return NULL;
	}
}

void ThreadPool::Start(int threadNum)
{
	m_running = true;
	m_threads.reserve(threadNum);
	for (int i = 0; i < threadNum; ++i)
	{
		Thread *thread = new Thread(ThreadFunc, this);
		thread->Start();
		m_threads.push_back(thread);
	}
}

void ThreadPool::Stop()
{
	m_running = false;
	m_cond.Broadcast();	
	for (unsigned int i = 0; i < m_threads.size(); ++i)
	{
		m_threads[i]->Join();
		delete m_threads[i];
	}
}

void ThreadPool::Put(const Task task)
{
	MutexLock lock(m_mutex);
	m_tasks.push(task);
	m_cond.Signal();
}
