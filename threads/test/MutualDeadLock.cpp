#include "MutualDeadLock.h"

void Inventory::PrintAll() const
{
	MutexLockGuard guard(m_ml);
	sleep(1);
	for (std::set<Request*>::const_iterator it = m_requests.begin();
		it != m_requests.end();
		++it)
	{
		(*it)->Print();
	}
	std::cout << "PrintAll() ok\n";
}

void* threadFunc(void* arg)
{
	Request* request = new Request();
	request->Process();
	delete request;
	return NULL;
}

//main()线程是先调用Inventory::PrintAll()再调用Request::Print()
//threadFunc()线程是先调用Request::~Request()再调用Inventory::Remove()
//这两个调用对mutex加锁顺序正好相反，造成了经典的死锁
int main()
{
	pthread_t tid;
	pthread_create(&tid, NULL, threadFunc, NULL);
	usleep(500 * 1000);
	g_inventory.PrintAll();
	pthread_join(tid, NULL);

	return 0;
}
