#ifndef _LLIST_H_
#define _LLIST_H_


#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

//define some callback function 
typedef void llist_op(const void *);

typedef int llist_cmp(const void *, const void *);

struct llist_node_st
{
    struct llist_node_st *prve;
    struct llist_node_st *next;
    //char类型占位符，用于实现变长结构体
    char data[1];
};

typedef struct llist_head
{
    int size;
    struct llist_node_st head;
}LLIST;

int llist_insert(LLIST *, const void *, int);
int llist_delete(LLIST *, const void *, llist_cmp *);
void * llist_find(LLIST *, const void *, llist_cmp *);
int llist_fetch(LLIST *, const void *, llist_cmp *, void *);
void llist_travel(LLIST *, llist_op *);
LLIST *llist_create(int initsize);
void llist_destroy(LLIST *);

#endif
