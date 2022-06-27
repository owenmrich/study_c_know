#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct LinkNode
{
    int data;
    struct LinkNode *next;
};
//初始化链表
struct LinkNode *Init_Linklist()
{
    //创建指针
    struct LinkNode *header = malloc(sizeof(struct LinkNode));
    header->data = -1;
    header->next = NULL;
    //尾部指针
    struct LinkNode *pRear = header;
    int val = -1;
    while(1)
    {
        printf("请输入:\n");
        scanf("%d",&val);
        if(val == -1)
        {
            break;
        }
        //创建新的节点
        struct LinkNode *newnode = malloc(sizeof(struct LinkNode));
        newnode->data = val;
        newnode->next = NULL;
        //把新节点插入到链表中
        pRear->next = newnode;
        //更新尾部指针
        pRear = newnode;
    }
    return header;
}
//插入value
void Inset_Linklist(struct LinkNode *header, int oldval, int newval)
{
    if(NULL == header)
    {
        return;
    }
    //辅助指针变
    struct LinkNode *pRecv = header;
    struct LinkNode *pCurrent = header->next;
    while(pCurrent != NULL)
    {
        if(pCurrent->data == oldval)
        {
            break;
        }
        pRecv = pCurrent;
        pCurrent = pCurrent->next;
    }
    /*
    if(pCurrent == NULL)
    {
        return;
    }
    */
    //创建新的节点
    struct LinkNode *newnode = malloc(sizeof(struct LinkNode));
    newnode->data = newval;
    newnode->next = NULL;
    //新节点插入到链表中
    newnode->next = pCurrent;
    pRecv->next = newnode;
}
//删除value值的节点
void Remove_Linklist(struct LinkNode *header, int delval)
{
     if(NULL == header)
    {
        return;
    }
    //辅助指针变
    struct LinkNode *pRecv = header;
    struct LinkNode *pCurrent = header->next;
    while(pCurrent != NULL)
    {
        if(pCurrent->data == delval)
        {
            break;
        }
        pRecv = pCurrent;
        pCurrent = pCurrent->next;
    }
    if(pCurrent == NULL)
    {
        return;
    }
    pRecv->next = pCurrent->next;
    free(pCurrent);
}
//遍历
void Foreach_Linklist(struct LinkNode *header)
{
    if(NULL == header)
    {
        return;
    }
    //辅助指针变
    struct LinkNode *pCurrent = header->next;
    while(pCurrent != NULL)
    {
        printf("%d\n",pCurrent->data);
        pCurrent = pCurrent->next;
    }
}
//销毁
void Destory_Linklist(struct LinkNode *header)
{
    if(NULL == header)
    {
        return;
    }
    //辅助指针变
    struct LinkNode *pCurrent = header;
     while(pCurrent != NULL)
    {
        struct LinkNode *pNext = pCurrent->next;
        //释放当前节点内容
        printf("%d节点给销毁\n",&pCurrent->data);
        free(pCurrent);
        pCurrent = pNext;
    }
}
//清空
void Clear_Linklist(struct LinkNode *header)
{
    if(NULL == header)
    {
        return;
    }
    //辅助指针变
    struct LinkNode *pCurrent = header->next;
    while(pCurrent != NULL)
    {
        struct LinkNode *pNext = pCurrent->next;
        //释放当前节点内容
        free(pCurrent);
        pCurrent = pNext;
    }
    header->next = NULL;
}
int main()
{
    struct LinkNode *header = Init_Linklist();
    printf("1");
    Foreach_Linklist(header);
    printf("============================\n");
    Inset_Linklist(header,300,6666);
    Foreach_Linklist(header);
    Remove_Linklist(header,6666);
    Foreach_Linklist(header);
    printf("============================\n");
    Inset_Linklist(header,888,8888);
    Foreach_Linklist(header);
    printf("============================\n");
    Clear_Linklist(header);
    Inset_Linklist(header,888,155);
    Foreach_Linklist(header);
    Destory_Linklist(header);


}