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
		MutexLock lock(m_mutex);
		count++;
		std::cout << "count=" << count << std::endl;
	}

private:
	Mutex m_mutex;
	int count;
};

int main()
{
	WorkThread thread1;
	thread1.Run();
	
	return 0;
}	
