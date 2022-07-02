#include <stdio.h>
#include <stdlib.h>

#include "sqlist.h"

sqlist* sqlist_create()
{
    sqlist *me;

    me = malloc(sizeof(*me));
    if (me == NULL)
        return NULL;
    me->last = -1;

    return me;
}

void sqlist_create2(sqlist **ptr)
{
    *ptr = malloc(sizeof(**ptr));
    if (*ptr == NULL)
        return;

    (*ptr)->last = -1;

    return;
}

int sqlist_insert(sqlist *me, int i, datatype *data)
{

    if (me->last == DATASIZE - 1)
        return -1;

    if (i < 0 || i > me->last + 1)
        return -2;
    
    for(int j = me->last; i <= j; j--)
        me->data[j + 1] = me->data[j];

    //insert the data
    me->data[i] = *data;
    me->last++;

    return 0;
}

void sqlist_display(sqlist *me)
{
    if(me->last == -1)
        return ;
    
    for (int i = 0; i <= me->last; i++)
        printf("%d ", me->data[i]);
    printf("\nlast = %d\n", me->last);

    return ;
}

int sqlist_destroy(sqlist *me)
{
    if (me != NULL)
    {
        free(me);
        me = NULL;
        return 0;
    }

    return -1;
}

int sqlist_delete(sqlist *me, int i)
{
    if (i < 0 || i > me->last)
        return -1;

    for(int j = i + 1;j <= me->last; j++)
        me->data[j - 1] = me->data[j];

    me->last--;

    return 0;
    
}

int sqlist_find(sqlist *me, datatype *data)
{
    if(sqlist_isempty(me) == 0)
        return -1;
    
    for (int i = 0; i < me->last; i++)
        if (me->data[i] == *data)
            return i;

    return -2;
}

int sqlist_setempty(sqlist *me)
{
    me->last = -1;
    return 0;
}

int sqlist_isempty(sqlist *me)
{
    if(me->last == -1)
        return 0;
    return -1;
}

int sqlist_getnum(sqlist *me)
{
    return me->last + 1;
}

int sqlist_union(sqlist *list1, sqlist *list2)
{
    int ret = -1;
    for(int i =0 ; i <= list2->last; i++)
        if(sqlist_find(list1, &list2->data[i]) < 0)
            ret = sqlist_insert(list1, 0, &list2->data[i]);

    return ret;
}

