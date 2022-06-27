#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main(void)
{
    int fd;
    printf("%d\n", errno);
    ret =  lseek(fd1, 0, SEEK_END);
    fd = open("1.txt",O_RDONLY | O_TRUNC);//把文件内容清零
    //每一个errno 都用一个数字去记录这个错误的内容
    printf("%d\n", errno);//错误号
    printf("%s\n",strerror(errno));//错误号对应的内容
    perror("");
    perror("open file");//不需要使用printf

    return 0;
}