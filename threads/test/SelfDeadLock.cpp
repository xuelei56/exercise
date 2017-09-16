#include "Mutex.h"

class Request
{
public:
	void Process()
	{
		MutexLockGuard guard(m_ml);
		std::cout << "Process()\n";
		Print();
	}
	void Print()
	{
		std::cout << "Print()" << std::endl;
		MutexLockGuard guard(m_ml);
	}
private:
	MutexLock m_ml;
};

int main()
{
	Request request;
	request.Process();

	return 0;
}
