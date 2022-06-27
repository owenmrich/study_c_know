#include<stdio.h>
int main (int argc, char **argv)
{
    //int argc  参数个数  argument count
    //char **argv 参数值  argument value
    if(argc >=2)
        printf("hellp,%s",argv[1]);
    else
        printf("hello world");
}
/*
.h 声明函数
.c 实现函数
预处理 main.i-> 编译main.S  -> 汇编mian.o -> 链接 ->  app

/*
./hello 1.txt 2.txt
argc=3
argc[0]="./hello"
argc[1]="1.txt"
argc[2]="2.txt"

