#include<stdio.h>
struct test
{
	struct test *p;
	int a;
	char b;

};
int main(int argc, char* argv[])
{
	struct test tct;
	int* q = &1;
	tct.a = 1;
	tct.p = &q;
	printf("%d\n", tct.a);
	printf("%c", tct.p);
}