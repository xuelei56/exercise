#include <stdio.h>
#include <iostream>
#include "ThreadPool.h"
#include "Thread.h"

void* Compute(void* arg)
{
	for (int i = 0; i < 6; ++i)
	{
		std::cout << CurrentThread::tid() << "---" << i << std::endl;
		usleep(1000 * 500);
	}
	return NULL;
}

int main()
{
	ThreadPool pool;
	pool.Start(3);
	for (int i = 0; i < 10; ++i)
	{
		pool.Put(Compute);
	}
	std::cout << "put all job to threadpool\n";

	getchar();
	pool.Stop();

	return 0;
}
