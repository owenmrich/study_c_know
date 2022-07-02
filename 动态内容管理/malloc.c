#if 0
找一个连续的内存空间
malloc 
calloc
realloc(void*ptr)//ptr必须为前面两个函数声明的空间地址
返回一个地址
free
原则:谁申请谁释放
#endif
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
//动态地址传参，分配空间
void func(int** p, int n)
{
	*p = malloc(n);
	if (*p == NULL)
		exit(1);
}
void* func1(int* p, int n)
{
	p = malloc(n);
	if (p == NULL)
		exit(1);
	return p;
}
int main()
{
	int nmu = 5;
	int* p = NULL;
	p = malloc(sizeof(int));
	if (p != NULL)
	{
		*p = 10;
	}
	printf("%d", *p);
	
	p = realloc(p,sizeof(int)*nmu);
	func(&p, nmu);//等价于 p = func1(p,nmu)
	free(p);
	p = NULL;//释放完 要直接把指针赋值为空，要不然会产生野指针，可能会造成内存访问的错误
	exit(0);
}