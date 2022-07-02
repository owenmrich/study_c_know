#ifndef _LLIST_H_
#define _LLIST_H_


#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

//define some function callback
typedef void llist_op(const void *);

typedef int llist_cmp(const void *, const void *);

struct llist_node_st
{
    void *data;
    struct llist_node_st *prve;
    struct llist_node_st *next;
};

typedef struct 
{
    int size;
    struct llist_node_st head;
}LLIST;

LLIST *llist_create(int initsize);

int llist_insert(LLIST *, const void *, int);

void * llist_find(LLIST *, const void *, llist_cmp *);

int llist_fetch(LLIST *, const void *, llist_cmp *, void *);

int llist_delete(LLIST *, const void *, llist_cmp *);

void llist_travel(LLIST *, llist_op *);

void llist_destroy(LLIST *);

#endif
