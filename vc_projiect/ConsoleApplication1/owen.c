#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"owen.h"

struct llist_st* llist_create(int size)
{
	LLIST* new;
	new = malloc(sizeof(*new));
	if (new == NULL)
		return NULL;
	new->size = size;
	new->head->data = NULL;
	new->head->prev = &new->head;
	new->head->next = &new->head;
	return new;
}
void llist_dedtory(LLIST *me)
{
	struct llist_st* cur,*tmp;
	for (cur = me->head->next; cur != &me->head; cur = cur->next)
	{
		tmp = cur->next;
		free(cur->data);
		free(cur);
	}
	free(me);
}
llist_find(LLIST* me)
{

}
llist_insert(LLIST* me,const void *data,int mode)
{
	struct llist_st* newnode;
	if (newnode == NULL)
		return -1;
	newnode->data == malloc(me->size);
	memcpy(newnode->data,data,me->size);
	if (mode == LLIST_FORWARD)
	{
		newnode->prev = &me->head;
		newnode->next = me->head->next;

	}
	else if (mode == LLIST_BACKWARD)
	{
		newnode->prev = me->head->prev;
		newnode->next = &me->head;
	}
	else
	{
		return -3;
	}
	newnode->prev->next = newnode;
	newnode->next->prev = newnode;
	return 0;
}

llist_show(LLIST* me)
{

}