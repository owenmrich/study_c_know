#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "llist.h"

typedef LLIST QUEUE;

QUEUE *qu_create(int);

int qu_enqueue(QUEUE *,const void *);

int qu_dequeue(QUEUE *ptr,void *data);

void qu_destroy(QUEUE *);


#endif