#include "Mutex.h"
#include <iostream>

class WorkThread
{
public:
	WorkThread()
	 : count(0) {}
	~WorkThread() {}
	void Run()
	{
		MutexLockGuard guard(m_ml);
		count++;
		std::cout << "count=" << count << std::endl;
	}

private:
	MutexLock m_ml;
	int count;
};

int main()
{
	WorkThread thread1;
	thread1.Run();
	
	return 0;
}	
