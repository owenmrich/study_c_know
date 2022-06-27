#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    /* 设置stdio缓冲模式
    printf("qpqpwpwq p\n");
    printf("111111");
    if (setvbuf(stdout, NULL, _IONBF, 0)) 
    {
        perror("setvbuf error");
        exit(0);
    }
    */
    //printf 是行缓冲，所以只会打印第一行
    printf("qpqpwpwq p\n");
    printf("111111");
    fflush(stdout);//强制刷新stdio缓冲
    //fclose(stdout); 也会刷新
    //程序退出时也会刷新
    while(1);
    return 0;
}