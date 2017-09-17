#include "CountDownLatch.h"
#include <unistd.h>
#include <iostream>

CountDownLatch g_latch(3);

void* subThread1(void* arg)
{
	sleep(2);
	std::cout << "subThread1 ok\n";
	g_latch.CountDown();
	return NULL;
}
void* subThread2(void* arg)
{
	sleep(1);
	std::cout << "subThread2 ok\n";
	g_latch.CountDown();
	return NULL;
}
void* subThread3(void* arg)
{
	std::cout << "subThread3 ok\n";
	g_latch.CountDown();
	return NULL;
}

int main()
{
	pthread_t tid1, tid2, tid3;
	pthread_create(&tid1, NULL, subThread1, NULL);
	pthread_create(&tid2, NULL, subThread2, NULL);
	pthread_create(&tid3, NULL, subThread3, NULL);

	g_latch.Wait();
	std::cout << "mainWork start\n";

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	return 0;
}
