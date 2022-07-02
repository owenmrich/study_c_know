#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "llist.h"

#define NAMESIZE 32

struct score_st
{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

static void print_s(const void *record)
{
    const struct score_st *r = record;
    printf("%d %s %d %d\n", r->id, r->name, r->math, r->chinese);
}

static int id_cmp(const void *key, const void * record)
{
    const int *k = key;
    const struct score_st *r = record;

    return (*k - r->id);
}

static int name_cmp(const void *key, const void * record)
{
    const char *k = key;
    const struct score_st *r = record;

    return strcmp(k, r->name);
}


int main()
{
     LLIST *handler;
    struct score_st tmp;
    
    handler = llist_create(sizeof(tmp));
    if(handler == NULL)
        exit(1);
    int ret;

    for (int i = 0; i< 7; i++)
    {
        tmp.id = i;
        snprintf(tmp.name, NAMESIZE, "std_%d",i);
        tmp.math = rand()%100;
        tmp.chinese = rand()%100;
        ret = llist_insert(handler, &tmp, LLIST_BACKWARD);
        if(ret)
            exit(1);
    }
    

    llist_travel(handler, print_s);

    
    char * n = "std_5";
    llist_delete(handler, n, name_cmp);

    printf("\n");

    llist_travel(handler, print_s);


    llist_destroy(handler);


    exit(0);
}


