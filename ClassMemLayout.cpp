//This is MemLayout example
#include <iostream>
using namespace std;

class Empty
{
};

class Person
{
public:
 	Person():m_id(0),m_age(20) { ++m_count; }
	virtual ~Person() { --m_count; }
	virtual void print()
	{
		cout << "id:" << m_id
			<< "age:" << m_age << endl;
	}	
	void work()
	{
		cout << "working" << endl;
	}
	static int personCount()
	{
		return m_count;
	}
private:
	static int m_count;
	int m_id;
	int m_age;
};

int main()
{
	cout << sizeof(Empty) << endl;
	cout << sizeof(Person) << endl;
	return 0;
}
