#include <iostream>

class Singleton
{
public:
	static Singleton* getInstance()
	{
		return m_instance;
	}

private:
	Singleton() { std::cout << "new obj" << std::endl; }
	Singleton(Singleton& other);
	Singleton& operator=(Singleton& other);

	static Singleton* m_instance;
};

Singleton* Singleton::m_instance = new Singleton();

int main()
{
	Singleton *pObj = Singleton::getInstance();
	return 0;
}
