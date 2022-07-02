#include<stdio.h>
#include<stdlib.h>

struct score_st
{
    int id;
    char name[NAMESIZE];
    int math;
    int chinese;
};

struct node_st
{
    struct score_st data;
    struct node_st *next;
};
int list_insert(struct node_st **list, struct score_st *data)
{
    //可以判断错误
    struct node_st *new;

    new = malloc(sizeof(*new));
    if(new == NULL)
        return -1;

    new->data = *data;//头节点插入
    new->next = *list;
    *list = new;

    return 0;
}

void list_show(struct node_st *list)
{
    struct node_st *cur;

    for(cur = list; cur!=NULL; cur= cur->next)
        printf("%d %s %d %d\n",cur->data.id, cur->data.name, cur->data.math, cur->data.chinese);
    printf("\n");
}

int list_delete(struct node_st **list)
{
    struct node_st *cur;

    if(*list == NULL)
        return -1;

    cur = *list;
    *list = (*list)->next;

    free(cur);

    return 0;
}

struct score_st* list_find(struct node_st *list, int *id)
{
    struct node_st *cur;

    for(cur=list; cur != NULL; cur= cur->next)
    {
        if(cur->data.id == *id)
            return &cur->data;
    }

    return NULL;
}

void list_destroy(struct node_st *list)
{
    struct node_st *cur;

    if(list == NULL)
        return;

    for(cur = list; cur != NULL; cur = list)
    {

        list = cur->next;
        free(cur);
    }
}