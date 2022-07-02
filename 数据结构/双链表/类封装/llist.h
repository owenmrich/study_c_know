#ifndef _LLIST_H_
#define _LLIST_H_


#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2

typedef void LLIST;
//void 百搭 .c内部使用自己的数据结构
//define some callback function 
typedef void llist_op(const void *);

typedef int llist_cmp(const void *, const void *);


int llist_insert(LLIST *, const void *, int);
int llist_delete(LLIST *, const void *, llist_cmp *);
void * llist_find(LLIST *, const void *, llist_cmp *);
int llist_fetch(LLIST *, const void *, llist_cmp *, void *);
void llist_travel(LLIST *, llist_op *);
LLIST * llist_create(int initsize);
void llist_destroy(LLIST *);

#endif
