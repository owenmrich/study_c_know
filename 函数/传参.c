#include<stdio.h>
#include<stdlib.h>
int print_a(int a, int b)//值传递
{
    printf("a is %d,b is %d\n", a, b);
    return 0;
}
int print_b(int *a, int *b)//地址传递,可以用于改变另外一个函数的值
{
    int tmp;
    printf("a is %d,b is %d\n", *a, *b);
    tmp = *a;
    *a = *b;
    *b = tmp;
    printf("a is %d,b is %d\n", *a, *b);

    return 0;
}
int main()
{
    int d = 1;
    int c = 2;
    print_a(d, c);
    print_b(&d, &c);
    print_a(d, c);
    exit(0);
}