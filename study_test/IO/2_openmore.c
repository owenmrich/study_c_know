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
    int ret;
    char buf[100];
    memset(buf, 0, sizeof(buf));
    printf("%d\n", errno);
    fd = open("1.txt",O_RDONLY);
    ret =  lseek(fd, 0, SEEK_END);
    printf("1.txt size is %d",ret);
    close(fd);
    fd = open("1.txt",O_RDONLY | O_TRUNC);// O_TRUNC把文件内容清零
    ret =  lseek(fd, 0, SEEK_END);
    printf("1.txt size is %d",ret);
    close(fd);
    fd = open("1.txt",O_RDWR);
    ret = write(fd, "hello",5);
    read(fd,buf,sizeof(buf));
    printf("%s",buf);
    close(fd);
    fd = open("1.txt",O_RDWR | O_APPEND);// O_APPEND文件尾写入
    write(fd, "owen",4);
    read(fd,buf,sizeof(buf));
    printf("%s",buf);
    close(fd);
    //fd = open("1.txt",O_RDWR | O_APPEND | O_TRUNC);
    return 0;
}