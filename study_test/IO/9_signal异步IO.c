#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#define MOUSE "/dev/input/event6"
static int fd;
static void sigio_handler(int sig) 
{
    static int loops = 5;
    char buf[100] = {0};
    int ret;
    if(SIGIO != sig)
    return;
    ret = read(fd, buf, sizeof(buf));
    if (0 < ret)
        printf("鼠标: 成功读取<%d>个字节数据\n", ret);
    loops--;
    if (0 >= loops) 
    {
        close(fd);
        exit(0);
    } 
}
int main(void) 
{
    int flag;
    /* 打开鼠标设备文件<使能非阻塞 I/O> */
    fd = open(MOUSE, O_RDONLY | O_NONBLOCK);
    if (-1 == fd) 
    {
        perror("open error");
        exit(-1);
    }
    /* 使能异步 I/O */
    flag = fcntl(fd, F_GETFL);
    flag |= O_ASYNC;
    fcntl(fd, F_SETFL, flag);
    /* 设置异步 I/O 的所有者 */
    fcntl(fd, F_SETOWN, getpid());
    /* 为 SIGIO 信号注册信号处理函数 */
    signal(SIGIO, sigio_handler);
    for ( ; ; )
        sleep(1);
}