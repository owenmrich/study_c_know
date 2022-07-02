//const 变量常量化 不会再改变
//const char *value 保证不会对用户的值进行修改，可以放心传递参数 用在函数的封装中
#include<stdio.h>
#include<stdlib.h>
int main()
{
    const int i = 1;
    int j = 3;
    const int* p = &i;//常量指针 指向的值不可以改变,不能通过*p去改值，可以直接改j
    printf("i is %d\n", *p);
    p = &j;
    printf("j is %d\n", *p);

    int* const q = &j;//指针常量 指向位置不变，位置值可变
    *q = 10;
    printf("p_j is %d\n", *p);
    printf("q_j is %d\n", *q);

    const int* const qc = &i;//指向位置不变，位置值也不可以变

    //无return 
    //返回最后一个执行函数的返回值
}