#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define MOUSE "/dev/input/event6"
int main(void) 
{
    char buf[100];
    int fd, ret, flag;
    /* 打开鼠标设备文件 非阻塞*/
    fd = open(MOUSE, O_RDONLY | O_NONBLOCK);
    if (-1 == fd) 
    {
        perror("open error");
        exit(-1);
    }
    /* 将键盘设置为非阻塞方式 */
    flag = fcntl(0, F_GETFL); //先获取原来的 flag
    flag |= O_NONBLOCK; //将 O_NONBLOCK 标准添加到 flag
    fcntl(0, F_SETFL, flag); //重新设置 flag
    for ( ; ; ) 
    {
        /* 读鼠标 */
        ret = read(fd, buf, sizeof(buf));
        if (0 < ret)
            printf("鼠标: 成功读取<%d>个字节数据\n", ret);
    /* 读键盘 */
        ret = read(0, buf, sizeof(buf));
        if (0 < ret)
            printf("键盘: 成功读取<%d>个字节数据\n", ret);
    }
    /* 关闭文件 */
    close(fd);
    exit(0);
}