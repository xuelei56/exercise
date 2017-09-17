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

Mutex g_mutex;
std::vector<Foo> g_foos;

void post(const Foo& foo)
{
	MutexLock lock(g_mutex);
	g_foos.push_back(foo);
}

void traverse()
{
	MutexLock lock(g_mutex);
	std::vector<Foo>::iterator it;
	for (it = g_foos.begin(); it != g_foos.end(); ++it)
	{
		it->doit();
	}
	//Foo foo;
	//post(foo);
}

int main()
{
	Foo foo;
	post(foo);
	post(foo);
	traverse();	

	return 0;
}
