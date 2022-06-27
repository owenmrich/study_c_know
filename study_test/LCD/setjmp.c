#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>
static jmp_buf buf;
static void hello(void) 
{
    printf("hello world!\n");
    longjmp(buf,1);
    printf("Nice to meet you!\n");
}
int main(void) 
{
    int i = 0;
    setjmp(buf); //设置跳转
    printf("First return\n");
    i++;
    if(i==5)
        exit(0);
    hello();

    printf("Second return\n");
    exit(0);
}