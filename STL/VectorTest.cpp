//vector扩容和迭代器失效
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::endl;

void capacity_size()
{
	cout << "capacity_size()-------------\n";
	vector<int> tmp;
	cout << "sizeof(tmp)" << sizeof(tmp) << endl;
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	tmp.push_back(5);
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	tmp.push_back(85);
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	tmp.push_back(87);
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	cout << "sizeof(tmp)" << sizeof(tmp) << endl;
	tmp.resize(10);
	tmp.push_back(45);
	cout << tmp.capacity() << endl;
}	

//如果容量不够,push_back()的时候扩展容量并拷贝所有元素
void iterator_losseffect_push()
{
	cout << "iterator_losseffect_push()---------------\n";
	vector<int> tmp;
	tmp.resize(10);
	tmp.assign(tmp.size(), 5);
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	vector<int>::iterator it = tmp.end() - 1;
	cout << *it << endl;
	tmp.push_back(12);
	tmp[9] = 9;
	//losseffect
	cout << *it << endl;
}

void iterator_effect()
{
	cout << "iterator_effect()--------------\n";
	vector<int> tmp;
	tmp.resize(10);
	tmp.assign(tmp.size(), 5);
	cout << tmp.capacity() << ' ' << tmp.size() << endl;
	vector<int>::iterator it = tmp.end() - 1;
	cout << *it << endl;
	tmp.push_back(12);
	tmp[9] = 9;
	//assign
	it = tmp.end() - 2;
	cout << *it << endl;
}

//erase()的时候后边的元素向前移动
void iterator_losseffect_erase()
{
	cout << "iterator_losseffect_erase()-------\n";
	vector<int> tmp;
	tmp.reserve(10);
	for(int i = 0; i < 10; i++)
	{
		tmp.push_back(i);
	}
	vector<int>::iterator it = tmp.begin();
	cout << *it << endl;
	it += 5;
	cout << *it << endl;
	tmp.erase(it);
	//指向删除点的迭代器全部失效，后边的元素迭代器也全部失效
	cout << *it << endl;
	cout << endl;
}

void eraseall()
{
	cout << "eraseall()----------\n";
	vector<int> tmp;
	tmp.resize(10);
	vector<int>::iterator it = tmp.begin();
	//每一次erase都移动所有元素，效率特别低
	for ( ; it!=tmp.end(); )
	{
		it = tmp.erase(it);	
	}
}

int main()
{
	capacity_size();
	iterator_losseffect_push();
	iterator_effect();
	iterator_losseffect_erase();
	eraseall();

	return 0;
}
