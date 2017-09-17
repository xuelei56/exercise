#include "Mutex.h"

class Request
{
public:
	void Process()
	{
		MutexLock lock(m_mutex);
		std::cout << "Process()\n";
		Print();
	}
	void Print()
	{
		std::cout << "Print()" << std::endl;
		MutexLock lock(m_mutex);
	}
private:
	Mutex m_mutex;
};

int main()
{
	Request request;
	request.Process();

	return 0;
}
