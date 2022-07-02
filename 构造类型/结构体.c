//  struct name_st
//  {
//      数据结构 成员1;
//      数据结构 成员2; 
//      int b;
//      .........  
//  };
// 使用 struct name_st ba; 类似于int a;
// 结构体输出
//  printf("%d",ba.b);
//  变量名.成员名
//  指针->成员名
// (*指针).成员名
// 结构体的对齐
//  以什么结构对齐,不够就要补齐，要满足对齐结构的整数倍
// struct nooacke
//{
//    int a;
//    char b;
//    float c;
//}__attribute((packed));//结构体不需要地址对其,常用于socket
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
void set_stu(struct study_st* p,const struct study_st* q)
{
    p->id = q->id;
    strncpy(p->name,q->name, 6);//字符串不能直接赋值
    p->brith.day = q->brith.day;
    //*p = *q


}
void show_stu(struct study_st* p)
{
    printf("name: %s id: %d,year: %d\n", p->name, p->id, p->brith.day);
}
int main()
{
    //struct study_st stu = { "owen",1,{2001,1,11} };
    //printf("name: %s id: %d,year: %d\n", stu.name, stu.id, stu.brith.year);
    struct study_st stu = { .name="owen",.id = 3,.brith.year = 88};
    printf("name: %s id: %d,year: %d\n", stu.name, stu.id, stu.brith.year);
    struct study_st *p = &stu;
    printf("name: %s id: %d,year: %d\n", p->name, p->id, p->brith.year);
    struct study_st arr[2] = { { "owen",1,{2001,1,11} } ,{ "owen2",2,{2002,2,12} } };
    int i;
    p = &arr[0];
    for (i = 0; i < 2; i++, p++)
    {
        printf("name: %s id: %d,year: %d\n", p->name, p->id, p->brith.year);
    }
    func(stu);
    func1(p);

    struct study_st stu1,tmp;
    scanf("%s%d%d", &tmp.name, &tmp.id, &tmp.brith.day);
    set_stu(&stu1,&tmp);
    show_stu(&stu1);
    exit(0);
}