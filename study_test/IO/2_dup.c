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
    char buf[100] = {0};
    /* 第一次打开文件 */
    fd1 = open("1.txt", O_RDWR | O_TRUNC | O_APPEND);
    fd2 = dup(fd1);
    if (-1 == fd1) 
    {
        perror("open error");
        exit(-1);
    }
    write(fd1, "owen1",5);
    /* 第二次打开文件 */
    if (-1 == fd2) 
    {
        perror("open error");
        close(fd1);
        return 0;
    }
    fd3 = dup2(fd1, 1000);
    printf("fd2 is %d\n", fd2);
    printf("fd1 is %d\n", fd1);

    printf("fd3 is %d\n",fd3);
    //lseek(fd2, 0 ,SEEK_SET);
    read(fd2, buf ,5);//指针已经到了文件尾部
    printf("read %s\n",buf);//数据为空
    close(fd1);
    close(fd2);
    return 0;
    
}