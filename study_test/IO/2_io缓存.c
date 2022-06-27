#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
static char buf[4096] __attribute((aligned (4096)));
int main ()
{
    int fd;
    int ret;
    //文件io缓存
    fd = open("./3.txt",O_RDWR);
    ret = fsync(fd);
    //int fdatasync(int fd);
    //void sync(void);
    close(fd);

    //直接io
    fd = open("./3.txt",O_RDWR | O_DIRECT);
    return 0;
}