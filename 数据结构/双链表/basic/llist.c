#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "llist.h"

LLIST *llist_create(int initsize)
{
    LLIST *new;

    new = malloc(sizeof(*new));
    if(new == NULL)
        return NULL;

    new->size = initsize;
    new->head.data = NULL;
    new->head.prve = &new->head;
    new->head.next = &new->head;

    return new;
}

int llist_insert(LLIST *ptr, const void *data, int mode)
{
    struct llist_node_st *newnode;

    newnode = malloc(sizeof(*newnode));
    if(newnode == NULL)
        return -1;

    newnode->data = malloc(ptr->size);
    if(newnode == NULL)
        return -2;
    memcpy(newnode->data, data, ptr->size);

    if(mode == LLIST_FORWARD)
    {   
        newnode->prve = &ptr->head;
        newnode->next = ptr->head.next;
    }
    else if(mode == LLIST_BACKWARD)
    {
        newnode->prve = ptr->head.prve;
        newnode->next = &ptr->head;
    }
    else
    {
        return -3;
    }

    newnode->prve->next = newnode;
    newnode->next->prve = newnode;
    return 0;
}

static struct llist_node_st * find_(LLIST *ptr, const void *key, llist_cmp * cmp)
{   //不希望外部扩展
    struct llist_node_st *cur;

    for(cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        if(cmp(key, cur->data) == 0)
            break;
    }

    return cur;
}

void * llist_find(LLIST *ptr, const void *key, llist_cmp * cmp)//返回数据
{
    return find_(ptr, key, cmp)->data;
}


int llist_fetch(LLIST *ptr, const void *key, llist_cmp * cmp, void *data)//删除并把值带回
{
    struct llist_node_st *node;
    node = find_(ptr, key, cmp);
    if(node == &ptr->head)
        return -1;
    
    node->prve->next = node->next;
    node->next->prve = node->prve;

    if(data != NULL)
        memcpy(data, node->data, ptr->size);
    free(node->data);
    free(node);
    return 0;

}

int llist_delete(LLIST *ptr, const void *key, llist_cmp * cmp)
{
    struct llist_node_st *node;
    node = find_(ptr, key, cmp);
    if(node == &ptr->head)
        return -1;
    
    node->prve->next = node->next;
    node->next->prve = node->prve;
    free(node->data);
    free(node);
    return 0;

}

void llist_travel(LLIST *ptr, llist_op * op)//提供回调函数 来指明函数类型
{
    struct llist_node_st *cur;

    for(cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        op(cur->data);
    }

}

void llist_destroy(LLIST *ptr)
{

    struct llist_node_st *cur, *next;

    for(cur = ptr->head.next; cur != &ptr->head; cur= next)
    {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
    free(ptr);
}


