#include<stdio.h>
#include<stdlib.h>
int a = 0; 
static int b = 0;
int c;
const int test = 10;
int main ()
{
    int d = 1;
    int e;
    static int f = 0;
    int *g=(int *)malloc(sizeof(int)*10);
    int *h=(int *)malloc(sizeof(int)*10);
    if(g == NULL || h == NULL)
    {
        printf("malloc error");
        goto _end;
    }
    printf("a:%p\n",&a);
    printf("b:%p\n",&b);
    printf("c:%p\n",&c);
    printf("d:%p\n",&d);
    printf("e:%p\n",&e);
    printf("f:%p\n",&f);
    printf("g:%p\n",&g);
    printf("*g:%p\n",&*g);
    printf("h:%p\n",&h);
    printf("*h:%p\n",&*h);
    printf("%p\n","123");
_end:
    if(g != NULL)
    {
        free(g);
    }
    if(h != NULL)
    {
        free(h);
    }
    return 0;



}