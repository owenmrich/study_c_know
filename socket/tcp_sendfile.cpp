#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#define RECEIVE_BUF_SIZE 1024
#define SERVER_PORT 7800
int main(int argc, char *argv[])
{
    //定义socket
    int sock_fd = 0;
    //定义接收文件的内存
    char file[RECEIVE_BUF_SIZE] = {0};
    //定义接收数据的内存
    char buf[RECEIVE_BUF_SIZE] = {0};
    //定义服务器的socket通讯地址
    struct sockaddr_in ser_addr;
    //设置服务器的socket参数
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family= AF_INET;
    inet_aton("127.0.0.1", (struct in_addr *)&ser_addr.sin_addr);
    ser_addr.sin_port = htons(SERVER_PORT);
    //创建socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(sock_fd < 0)
    {
        printf("create socket failed\n");
        exit(1);
    }
    //连接到服务器
    if(connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
    {
        printf("connect socket failedn");
        close(sock_fd);
        exit(1);
    }
    //接收文件名称
    int receivelength = 0;
    while(receivelength <= 0)
    {
        receivelength = read(sock_fd, file, sizeof(file));
    }
    printf("receive name length :%d\n", receivelength);
    sprintf(buf,"%s",file);
    printf("begin receive file %s\n", file);
    //创建接受文件
    FILE *target;
    target = fopen(buf, "wb");
    if(target == NULL)
    {
        printf("open file failed\n");
        close(sock_fd);
        exit(1);
    }
    //通知服务器准备好了
    sprintf(buf, "ready");
    write(sock_fd, buf, strlen(buf));
    //开始接收文件内容
    memset(buf, 0, RECEIVE_BUF_SIZE);
    while((receivelength = read(sock_fd, buf, RECEIVE_BUF_SIZE)) > 0)
    {
        if(receivelength < 0)
        {
            printf("receive file error\n");
            fclose(target);
            close(sock_fd);
            exit(1);
        }
        printf("receive file length:%d\n", receivelength);
        fwrite(buf, 1, receivelength, target);
        memset(buf, 0, RECEIVE_BUF_SIZE);
    }
    printf("receive file success\n");
    //关闭文件句柄
    fclose(target);
    //关闭socket
    close(sock_fd);
}