#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) 
{
    int fd1, fd2, fd3;
    int ret;
    /* 第一次打开文件 */
    fd1 = open("1.txt", O_RDWR | O_TRUNC | O_APPEND);
    if (-1 == fd1) 
    {
        perror("open error");
        exit(-1);
    }
    write(fd1, "owen1",5);
    /* 第二次打开文件 */
    fd2 = open("1.txt", O_RDWR | O_APPEND);
    if (-1 == fd2) 
    {
        perror("open error");
        ret = -1;
        goto err1;
    }
    write(fd2, "hello",5);
    /* 第三次打开文件 */
    fd3 = open("1.txt", O_RDWR | O_APPEND);
    if (-1 == fd3) 
    {
        perror("open error");
        ret = -1;
        goto err2;
    }
    write(fd3, "world",5);
    /* 打印出 3 个文件描述符 */
    printf("%d %d %d\n", fd1, fd2, fd3);
    close(fd3);
    ret = 0;
    err2:
    close(fd2);
    err1:
    /* 关闭文件 */
    close(fd1);
    exit(ret);
}