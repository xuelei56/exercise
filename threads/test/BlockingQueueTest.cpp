#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include "BlockingQueue.h"

BlockingQueue<int> g_dataQueue;

void* threadPut(void* arg)
{
	static int num = 0;
	while (1)
	{
		g_dataQueue.Put(num);
		//warning: no lock
		++num;
		sleep(1);
	}
	return NULL;
}

int main()
{
	pthread_t tid;
	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&tid, NULL, threadPut, NULL);
	}

	while (1)
	{
		int num = g_dataQueue.Take();
		std::cout << num << std::endl;
	}

	return 0;
}
