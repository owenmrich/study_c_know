#include<stdio.h>
#include<stdlib.h>

void* test = NULL;
int main()
{
    int i = 1;
    void* w = NULL;
    //格式 int* name = 地址;
    // & 取地址符
    // * 取值
    //int* p = &i;
    int* p = NULL; 
    p = &i;
    int** q = &p;//二级指针
    printf("i is %d\n", i);
    printf("&i is %p\n", &i);//地址i
    printf("p is %p\n", p);//地址i
    printf("p is %p\n", &p);//地址p
    printf("*p is %d\n", *p);
    printf("q is %p\n", q);//地址p 
    printf("**q is %d\n", **q);
    printf("*q is %p\n", *q);//地址i

    printf("q is %p\n", &q);//地址q

    printf("i sizeof is %d\n", (int)sizeof(i));
    printf("p sizeof is %d\n", (int)sizeof(p));
    return 0;
}
