// 以下只针对64位机器测试，32位可能不同
#include <stdio.h>

// struct内存以4字节或8字节自动对齐,如果不排版会造成内存浪费
struct ST_PERSON_OLD
{
	char sex;	 // 4						
	int age;   // 4
	int money; // 4
};

// char数组相邻时，紧挨着排列
struct ST_PERSON
{
	char sex;							
  char work; // 4
	int age;   // 4
	int money; // 4
	char name[8+1];// 9
  //long long time;// 8
	char address[16+1];// 19
};

// 最后一个大字符数组占用24字节？
struct ST_PERSON2
{
	char sex;							
  char work; // 4
	int age;   // 4
	int money; // 4
	char name[8+1];// 12
  long long time;// 8
	char address[16+1];//24
};

struct ST_PERSON3
{
	char sex;							
  char work; // 4
	int age;   // 4
	int money; // 4
	char name[8+1];// 12
  long long time;// 8
	char address[8+1];//16
};

// int 4字节对齐
struct ST_PERSON4
{
	char name[4+1]; 		// 8
	int age;						// 4
	char address[8+1];	// 12
};

// long long 8字节对齐
struct ST_PERSON5
{
	char name[4+1];			// 8
	long long age;			// 8
	char address[8+1];	// 16
};

struct ST_PERSON6
{
	char name[8+1];			// 16
	long long age;			// 8
	char address[8+1];	// 16
};
int main()
{
	struct ST_PERSON_OLD stPersonOld;
	printf("%d\n", sizeof(stPersonOld));

	struct ST_PERSON stPerson;
	printf("%ld\n", sizeof(stPerson)); 	
	printf("%x,%x,%x,%x,%x,%x\n", &stPerson.sex, &stPerson.work, &stPerson.age, &stPerson.money, &stPerson.name, &stPerson.address);
	printf("%d\n", sizeof(stPerson.address));
	int *ptr;
	printf("%d\n", sizeof(ptr));

	struct ST_PERSON2 stPerson2;
	printf("%d\n", sizeof(stPerson2));

	struct ST_PERSON3 stPerson3;
	printf("%d\n", sizeof(stPerson3));

	struct ST_PERSON4 stPerson4;
	printf("%d\n", sizeof(stPerson4));

	struct ST_PERSON5 stPerson5;
	printf("%d\n", sizeof(stPerson5));

	struct ST_PERSON6 stPerson6;
	printf("%d\n", sizeof(stPerson6));

	return 0;
}
