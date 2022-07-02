//typedef 为已有的数据类型改名
// typedef int  INT;
// 类似于 #define INT int (在预处理的时候会替换)
// 在指针定义上的区别
//  typedef int* P;
//  #define P int*
//  P p,q; --> int *p,q;(define)
//  P p,q; --> int *p,*q;

#if 0
1) 为基本数据类型定义新的类型名
    typedef unsigned int COUNT;
2)为自定义数据类型（结构体、共用体和枚举类型）定义简洁的类型名称
    typedef struct tagPoint
    {
        double x;
        double y;
        double z;
    } Point;
3) 为数组定义简洁的类型名称
    typedef int INT_ARRAY_100[100];
    INT_ARRAY_100 arr;
4) 为指针定义简洁的名称
    typedef char* PCHAR;
    PCHAR pa;
typedef int llist_cmp(const void *, const void *);


#endif