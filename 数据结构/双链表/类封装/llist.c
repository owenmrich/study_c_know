#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "llist.h"

// 对 struct 类型的定义进行封装
// 声明在h文件，定义在c文件 
// 实现类成员封装
struct llist_node_st
{
    struct llist_node_st *prve;
    struct llist_node_st *next;
    //char类型占位符，用于实现变长结构体
    char data[1];
};

struct llist_head_st
{
    int size;
    struct llist_node_st head;
};



LLIST *llist_create(int initsize)
{
    struct llist_head_st *new;

    new = malloc(sizeof(*new));
    if(new == NULL)
        return NULL;

    new->size = initsize;
    new->head.prve = &new->head;
    new->head.next = &new->head;

    return new;
}

int llist_insert(LLIST *p, const void *data, int mode)
{
    struct llist_node_st *newnode;
    struct llist_head_st *ptr = p;

    newnode = malloc(sizeof(*newnode) + ptr->size);
    if(newnode == NULL)
        return -1;

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

static struct llist_node_st * find_(struct llist_head_st *ptr, const void *key, llist_cmp * cmp)
{
    struct llist_node_st *cur;

    for(cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        if(cmp(key, cur->data) == 0)
            break;
    }

    return cur;
}

void * llist_find(LLIST *p, const void *key, llist_cmp * cmp)
{
    struct llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_(ptr, key, cmp);
    if(node == &ptr->head)
        return NULL;
    return node->data;
}


int llist_fetch(LLIST *p, const void *key, llist_cmp * cmp, void *data)
{
    struct llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_(ptr, key, cmp);
    if(node == &ptr->head)
        return -1;
    
    node->prve->next = node->next;
    node->next->prve = node->prve;

    if(data != NULL)
        memcpy(data, node->data, ptr->size);
    free(node);
    return 0;

}

int llist_delete(LLIST *p, const void *key, llist_cmp * cmp)
{
    struct llist_node_st *node;
    struct llist_head_st *ptr = p;
    node = find_(ptr, key, cmp);
    if(node == &ptr->head)
        return -1;
    
    node->prve->next = node->next;
    node->next->prve = node->prve;
    free(node);
    return 0;

}

void llist_travel(LLIST *p, llist_op * op)
{
    struct llist_node_st *cur;
    struct llist_head_st *ptr = p;

    for(cur = ptr->head.next; cur != &ptr->head; cur = cur->next)
    {
        op(cur->data);
    }

}

void llist_destroy(LLIST *p)
{

    struct llist_node_st *cur, *next;
    struct llist_head_st *ptr = p;

    for(cur = ptr->head.next; cur != &ptr->head; cur= next)
    {
        next = cur->next;
        free(cur);
    }
    free(ptr);
}


