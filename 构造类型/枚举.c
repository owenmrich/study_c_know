//  enum 标识符
//  {
//      成员1 = 1,//顺次往下排
//      成员2
//  }
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
enum day
{
	mon = 1,
	tus,
	thr,
	wes,
	fri,
	sat,
	sun
};

int main()
{
	enum day a = mon;
	printf("%d\n", a);
	
	exit(0);
}