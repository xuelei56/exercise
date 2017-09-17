#include <unistd.h>
#include <iostream>
#include "Thread.h"

typedef struct Data 
{
	int first;
	int second;
} Data;

void* threadFunc1(void* arg)
{
	Data* data = (Data*)arg;
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "thread.. " << data->first << ' ' 
			<< data->second << std::endl;
		sleep(1);
	}
	return NULL;
}

int main()
{
	Data data;
	data.first = 1;
	data.second = 2;
	Thread thread(threadFunc1, &data);
	thread.Start();
	thread.Join();

	return 0;
}
