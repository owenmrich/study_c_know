#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"owen.h"
struct stu_st
{
    int id;
    char name[32];
    int math;
};
int main()
{
    int i;
    struct stu_st tmp;
    LLIST* handler;
    handler = llist_create(sizeof(struct stu_st));
    for (i = 0; i < 7; i++)
    {
        tmp.id = i;
        tmp.math = rand() % 100;
        strcpy(&tmp.name,"stu");
        llist_insert(handler,&tmp,LLIST_FORWARD );
    }
    llist_show(handler);
    llist_dedtory(handler);
}