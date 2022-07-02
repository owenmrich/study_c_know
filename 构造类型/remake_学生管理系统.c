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
    char *name;
    int id;
    struct brith_st brith;
};
void movie(void)
{
    printf("1:show\n2:change\n3:show\n");
}
void set_stu(struct study_st* p, int i)
{
    struct study_st temp;
    struct study_st* tmp = &temp;
    ret = scanf("%s%d%d", &(tmp->name), &(tmp->id), &(tmp->brith.day));
    p-> name =malloc(strlen(tmp->name)+1);
    if(p->name == NULL)
        exit(1);
    strcpy(p->name,tmp->name);
    p->id = temp-> id;
    p->brith.day = temp->brith.day;
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