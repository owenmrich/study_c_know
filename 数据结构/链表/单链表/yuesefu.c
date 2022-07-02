#include<stdio.h>
#include<stdlib.h>
struct LinkNode
{
    int data;
    struct LinkNode* next;
};
struct LinkNode* Init_Linklist(int n)
{
    int i=1;
    struct LinkNode* header = malloc(sizeof(*header));
    struct LinkNode* tmp,*cur;
    if (header == NULL)
        return NULL;
    header->data = i;
    header->next = header;//循环链表
    i++;
    cur = header;
    for (; i <= n; i++)
    {
        tmp = malloc(sizeof(*tmp));
        if (tmp == NULL)
            return NULL;
        tmp->data = i;
        tmp->next = header;//单环链
        cur->next = tmp;
        cur = tmp;
    }
   
    return header;
}
void list_show(struct LinkNode* list)
{
    struct LinkNode* cur;
    //使用do while
    for (cur = list; cur->next != list; cur = cur->next)
        printf("%d \n", cur->data);
    printf("%d\n",cur->data);
    printf("=====\n");
    /*
    do
    {
        printf("%d \n", cur->data);
    } while (cur->next != list);
    */
}
void kill_sl(struct LinkNode** me, int n)
{
    struct LinkNode* tmp = malloc(sizeof(*tmp));
    struct LinkNode* cur;
    cur = *me;
    int i = 1;
    while (cur != cur->next)
    {
        while (i < n)
        {
            tmp = cur;
            cur = cur->next;
            i++;
        }
        printf("%d ", cur->data);
        tmp->next = cur->next;
        free(cur);
        cur = tmp->next;
        i = 1;
    }
    printf("\n");
    *me = cur;
}
int main()
{
    int num = 8;
    struct LinkNode* p1,*p2;
    p1 = Init_Linklist(num);
    p2 = p1;
    list_show(p1);
    kill_sl(&p1, num);
    list_show(p1);

}