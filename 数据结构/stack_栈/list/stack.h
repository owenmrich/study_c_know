#ifndef _STACK_H_
#define _STACK_H_

#include "llist.h"

typedef LLIST STACK;

STACK *stack_create(int);

int stack_push(STACK *, const void *);

int stack_pop(STACK *, void *data);

void stack_destroy(STACK *);


#endif
