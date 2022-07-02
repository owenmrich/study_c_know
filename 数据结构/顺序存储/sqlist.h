#ifndef _SQLIST_H_
#define _SQLIST_H_

#define DATASIZE 1024
typedef int datatype;

typedef struct node_st
{
    datatype data[DATASIZE];
    // record the last data position
    int last; 
}sqlist;

sqlist* sqlist_create();

void sqlist_create2(sqlist **);

int sqlist_insert(sqlist *,int i, datatype *);

int sqlist_delete(sqlist *, int i);

int sqlist_find(sqlist *, datatype *);

int sqlist_isempty(sqlist *);

int sqlist_setempty(sqlist *);

int sqlist_getnum(sqlist *);

void sqlist_display(sqlist *);

int sqlist_destroy(sqlist *);

int sqlist_union(sqlist *, sqlist *);

#endif

