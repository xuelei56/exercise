#include "Mutex.h"
#include <iostream>
#include <vector>

class Foo
{
public:
	Foo() {}
	~Foo() {}
	void doit() 
	{ 
		std::cout << "doit()" << std::endl; 
	}
private:
	int m_num;
};

MutexLock g_ml;
std::vector<Foo> g_foos;

void post(const Foo& foo)
{
	MutexLockGuard guard(g_ml);
	g_foos.push_back(foo);
}

void traverse()
{
	MutexLockGuard guard(g_ml);
	std::vector<Foo>::iterator it;
	for (it = g_foos.begin(); it != g_foos.end(); ++it)
	{
		it->doit();
	}
	Foo foo;
	post(foo);
}

int main()
{
	Foo foo;
	post(foo);
	post(foo);
	traverse();	

	return 0;
}
