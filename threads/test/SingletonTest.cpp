#include "Singleton.h"
#include <iostream>

class Foo
{
public:
	Foo():num(0) { std::cout << "new foo\n"; }
	~Foo() {}
	void Print()
	{
		std::cout << "Print\n";
	}
private:
	int num;
};

int main()
{
	Foo& foo = Singleton<Foo>::getInstance();
	foo.Print();
	return 0;
}

