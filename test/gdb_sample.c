//gdb-sample, by xuelei

#include <stdio.h>

int nGlobalVar = 0;

int tempFunction(int a, int b)
{
    printf("tempFunction is called, a = %d, b = %d \n", a, b);
    return (a + b);
}

int testCoreDown()
{
    char *szStrLbm[] = {
		"U01001",
		"U01002",
		"U01003",
		"U01004"
	};

    printf("%d\n", strcmp("", szStrLbm[0]));
    printf("%d\n", strcmp("", szStrLbm[4]));
    printf("%d\n", strcmp(szStrLbm[4], ""));

    int tmp[4];
    printf("%d\n", tmp[0]);
    printf("%d\n", tmp[4]);

    return 0;
}

int testCoreDump()
{
  char *p = NULL;
  *p = 'a';
  return *p;
}

void test1()
{
  int ret = 0;
  ret = testCoreDump();
  ret += 2;
}

int main()
{
    int n;
    n = 1;
    n++;
    n--;

    nGlobalVar += 100;
    nGlobalVar -= 12;

    printf("n = %d, nGlobalVar = %d \n", n, nGlobalVar);

    testCoreDown();
    test1();

    n = tempFunction(1, 2);
    printf("n = %d \n", n);

    return 0;
}
