#include "Mutex.h"
#include "Condition.h"
#include <assert.h>
#include <unistd.h>
#include <syscall.h>
#include <deque>

MutexLock g_ml;
Condition g_cond(g_ml);
std::deque<int> g_queue;

int dequeue()
{
	MutexLockGuard guard(g_ml);
	std::cout << syscall(SYS_gettid) << " get MutexLock"<< std::endl;
	//sleep(1);
	while (g_queue.empty())
	{
		std::cout << syscall(SYS_gettid) << " Wait()...\n";
		g_cond.Wait();//wait这一步会原子性的释放mutex并进入等待，不会与其他线程死锁
		//g_cond.Wait()执行完毕后自动重新加锁
	}
	assert(!g_queue.empty());
	int data = g_queue.front();
	g_queue.pop_front();
	std::cout << syscall(SYS_gettid) << " release MutexLock"<< std::endl;
	return data;
}

void enqueue(int x)
{
	{
		MutexLockGuard guard(g_ml);
		g_queue.push_back(x);
	}
	g_cond.Signal();
}

void* thread_func_get(void* arg)
{
	while (1)
	{
		int n =	dequeue();
	}
	return NULL;
}

void* thread_func_put(void* arg)
{
	for (int i = 0; i < 1000; ++i)
	{
		enqueue(i);
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid_get1, tid_get2;
	pthread_create(&tid_get1, NULL, thread_func_get, NULL);
	pthread_create(&tid_get2, NULL, thread_func_get, NULL);
	pthread_t tid_put;
	pthread_create(&tid_put, NULL, thread_func_put, NULL);

	pthread_join(tid_get1, NULL);
	pthread_join(tid_get2, NULL);
	pthread_join(tid_put, NULL);

	return 0;
}
