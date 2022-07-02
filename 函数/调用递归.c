#include<stdio.h>
#include<stdlib.h>
int i = 3;
int join(int i, int j)
{
    return i * j;
}
int xbox(int i, int j)
{
    return join(i, j);//嵌套
}
//递归,直接/间接调用自身 需要有结束条件
//可能会导致栈的破裂,因为递归次数不确定
int change(void)
{
    i--;
    printf("%s begin!\n", __FUNCTION__);
    if(i == 0)
        return 99;
    printf("%s will call change()\n", __FUNCTION__);
    change();
}
//阶乘
int x_result(int x)
{
    if (x < 0)
    {
        return -1;
    }
    if (x == 0 || x == 1)
    {
        return 1;
    }
    
    return x * x_result(x - 1);
}
//fibn数列 可以指定初始的两个值

int filb(int count,const int *p,const int *q)
{   
    if (count < 1)
    {
        return -1;
    }
    if (count == 1)
    {
        return *p;
    }
    if (count == 2)
    {
        return *q;
    }

    return filb(count - 1,p,q)+filb(count -2,p,q);
}
void move(char a, char c)
{
    printf("move %d -> %d\n", a, c);
}
static void hanoi(int n, char A, char B, char C)
{
    if (n == 1) {
        move(A, C);
    }
    else {
        hanoi(n - 1, A, C, B);//将n-1个盘子由A经过C移动到B
        move(A, C);             //执行最大盘子n移动
        hanoi(n - 1, B, A, C);//剩下的n-1盘子，由B经过A移动到C
    }
}
int main()
{
    int d = 1;
    int c = 2;
    int count = 3;
    int result = xbox(d, c);
    printf("result is %d\n", result);
    result = change();
    printf("result is %d\n", result);
    int x = 5;
    printf("%d! is %d\n", x, x_result(x));
    printf("%d_filb is %d\n",count, filb(count, &d, &c));
    int n = 5; char A = 'a'; char B = 'b'; char C = 'c';
    hanoi(n, A, B, C);
    exit(0);
}