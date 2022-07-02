#include<stdio.h>
#include<stdlib.h>
typedef struct pol_st
{
    int x;
    int y;
} pol;
struct LinkNode
{
    struct pol_st data;
    struct LinkNode* next;
};
struct LinkNode* Init_Linklist(int a[][2], int n)
{
    int i;
    struct LinkNode* header = malloc(sizeof(*header));
    struct LinkNode* tmp,*cur;
    if (header == NULL)
        return NULL;
    header->next = NULL;
    cur = header;
    for (i =0;i<n;i++)
    {
        tmp = malloc(sizeof(*tmp));
        tmp->data.x = a[i][0];
        tmp->data.y = a[i][1];
        tmp->next = NULL;
        cur->next = tmp;
        cur = tmp;
    }
    return header;
}
void list_show(struct LinkNode* list)
{
    struct LinkNode* cur;

    for (cur = list->next; cur != NULL; cur = cur->next)
        printf("%d %d\n", cur->data.x, cur->data.y);
    printf("\n");
}
void un_LinkNode(struct LinkNode* p1, struct LinkNode* p2)
{
    struct LinkNode* p, * q, * r;
    p = p1->next;
    q = p2->next;
    r = p1;
    while (p && q)
    {
        if (p->data.y < q->data.y)
        {
            r->next = p;
            r = p;
            p = p->next;
        }
        else if (p->data.y > q->data.y)
        {
            r->next = q;
            r = q;
            q = q->next;
        }
        else //==
        {
            p->data.x += q->data.x;
            if (p->data.x != 0)
            {
                r->next = p;
                r = p;
            }
            p = p->next;
            q = q->next;
        }
    }
    if (p == NULL)
        r->next = q;
    if (q == NULL)
        r->next = p;
}
int main()
{
    int a[][2] = { {5,0},{3,2} };
    int b[][2] = { {4,1},{-3,2} };
    struct LinkNode* p1, * p2;
    p1 = Init_Linklist(a,2);
    p2 = Init_Linklist(b,2);
    list_show(p1);
    list_show(p2);
    un_LinkNode(p1, p2);
    list_show(p1);
}