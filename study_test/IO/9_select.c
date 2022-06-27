#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>
#define MOUSE "/dev/input/event6"
int main(void) 
{
    char buf[100];
    int fd, ret = 0, flag;
    fd_set rdfds;
    int loops = 5;
    /* 打开鼠标设备文件 */
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
    /* 同时读取键盘和鼠标 */
    while (loops--) 
    {
        FD_ZERO(&rdfds);
        FD_SET(0, &rdfds); //添加键盘
        FD_SET(fd, &rdfds); //添加鼠标
        ret = select(fd + 1, &rdfds, NULL, NULL, NULL);
        if (0 > ret) 
        {
            perror("select error");
            goto out;
        }
        else if (0 == ret) 
        {
            fprintf(stderr, "select timeout.\n");
            continue;
        }
        /* 检查键盘是否为就绪态 */
        if(FD_ISSET(0, &rdfds)) 
        {
            ret = read(0, buf, sizeof(buf));
            if (0 < ret)
                printf("键盘: 成功读取<%d>个字节数据\n", ret);
        }
        /* 检查鼠标是否为就绪态 */
        if(FD_ISSET(fd, &rdfds)) 
        {
            ret = read(fd, buf, sizeof(buf));
            if (0 < ret)
                printf("鼠标: 成功读取<%d>个字节数据\n", ret);
        }
    }
    out:
    /* 关闭文件 */
    close(fd);
    exit(ret);
}