#ifndef LIST_H__
#define LIST_H__
#define LLIST_FORWARD 1
#define LLIST_BACKWARD 2
struct llist_st//��ͨ�ڵ�
{
    void* data;
    struct llist_st* prev;
    struct llist_st* next;
};
typedef struct //ͷ�ڵ�
{
    int size;
    struct llist_st* head;
} LLIST;
LLIST* llist_create(int size);//ֻ��ͷ�ڵ��˫����
void llist_dedtory(LLIST *me);
llist_find(LLIST* me);
llist_insert(LLIST* me, const void * data, int mode);
llist_show(LLIST* me);

#endif
