#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

#define NAMESIZE 32

struct score_st
{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

static void print_s(void * record)
{
    struct score_st *r = record;
    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

int main()
{
    QUEUE *qu;
    struct score_st tmp;

    qu = qu_create(sizeof(struct score_st));
    if(qu == NULL)
        exit(1);

    for(int i = 0; i < 7; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "std_%d",i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        if(qu_enqueue(qu, &tmp))
            break;
    }

    int ret;
    while(1)
    {
        ret = qu_dequeue(qu, &tmp);
        if (ret == -1)
            break;
        print_s(&tmp);
    }
    
    qu_destroy(qu);

    exit(0);
}