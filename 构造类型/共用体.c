//  union name_un
//  {
//    数据类型 成员1;
//    数据类型 成员2;
//  };
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
union mo_un
{
    double d;
};
union yes_un
{
    int i;
    float f;
    union mo_un a;
};
union weitu
{
    struct  
    {
        uint16_t i;
        uint16_t j;
    }x;
    uint32_t y;
}weitu;
//共用体只有一个成员生效,只分配最大数值的空间
int main()
{
    union yes_un a;
    union yes_un arr[3];
    union yes_un* p = &a;
    a.f = 3.12;
    p->f = 3.14;
    printf("%d\n", (int)sizeof(a));
    printf("%f\n", a.f);
    p->i = 4;
    printf("%d\n", p->i);
    //无用printf("%f\n", a.f);

    //位图计算 高位+低位
    weitu.y = 0x11223344;
    printf("%x\n", weitu.x.i+weitu.x.j);
    //如上使用union 
    uint32_t i = 0x11223344;
    printf("%x\n", (i >> 16) + (i & 0xFFFF));



    exit(0);
}