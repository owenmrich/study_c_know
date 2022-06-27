#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct stu
{
    int id;  
    int age;
} stu1;
typedef struct stu stu3;
int main()
{
    stu1 z;
    stu3 w;
    struct stu q;
    z.id=1;
    w.id=2;
    scanf("%d",&q.id);
    printf("stu1.id=%d",&z.id);
    printf("stu2.id=%d",&w.id);
    printf("stu3.id=%d",&q.id);
}