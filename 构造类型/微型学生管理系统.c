#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct brith_st
{
    int year;
    int mouth;
    int day;
};
struct study_st
{
    char name[6];
    int id;
    struct brith_st brith;
};
//函数传递结构体
void func(struct study_st b)
{
    printf("%d\n", (int)sizeof(b));
}
void func1(struct study_st *b)//常用地址传递
{
    printf("%d\n", (int)sizeof(b));
}
void set_stu1(struct study_st* p,const struct study_st* q)
{
    p->id = q->id;
    strncpy(p->name,q->name, 6);//字符串不能直接赋值
    p->brith.day = q->brith.day;
    //*p = *q
}
void movie(void)
{
    printf("1:show\n2:change\n3:show\n");
}
void set_stu(struct study_st* p, int i)
{
    int ret;
    struct study_st temp;
    struct study_st *tmp= &temp;
    printf("send name id day\n");
    ret = scanf("%s%d%d", &(tmp->name), &(tmp->id), &(tmp->brith.day));
    *(p + i) = *tmp;
}
void show_stu(struct study_st* p,int i)
{
    printf("name: %s id: %d,year: %d\n", (p+i)->name, (p+i)->id, (p+i)->brith.day);
}
void change_stu(struct study_st* p, int i)
{
    int ret;
    struct study_st temp;
    struct study_st* tmp = &temp;
    printf("send name id day\n");
    ret = scanf("%s%d%d", &(tmp->name), &(tmp->id), &(tmp->brith.day));
    *(p + i) = *tmp;
}

int main()
{
    struct study_st stu[10];
    struct study_st *p = stu;
    int i;
    int ret;
    do
    {
        movie();
        ret = scanf("%d:", &i);
        if (ret != 1)
        {
            break;
        }
        switch (i)
        {
            case 1:
                printf("Please send id\n");
                ret = scanf("%d:", &i);
                show_stu(p,i);
                break;
            case 2:
                printf("Please send id\n");
                ret = scanf("%d:", &i);
                change_stu(p,i);
                break;
            case 3:
                printf("Please send id\n");
                ret = scanf("%d:", &i);
                set_stu(p,i);
                break;
            default:
                break;
        }

    } while (1);
    
    exit(0);
}