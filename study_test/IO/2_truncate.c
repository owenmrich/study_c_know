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
    fd1 = open("1.txt", O_RDWR |  O_APPEND);
    ret = lseek(fd1, 0, SEEK_END);
    printf("1.txt size is %d\n",ret);
    ftruncate(fd1,1024);
    ret = lseek(fd1, 0, SEEK_END);
    printf("1.txt size is %d\n",ret);
    close(fd1);

    truncate("./1.txt",512);
    return 0;
    
}