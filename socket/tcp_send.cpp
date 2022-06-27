#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define SERVER_PORT 7800
int main(int argc, char *argv[])
{
    //定义socket
    int sock_fd = 0;
    //定义接收数据的内存
    char recvbuf[RECV_BUF_SIZE] = {0};
    //定义发送数据的内存
    char sendbuf[SEND_BUF_SIZE] = {0};
    //定义接收数据中长度
    int recvlen = 0;
    int retlen = 0;
    int sendlen = 0;
    int leftlen = 0;
    char *ptr = NULL;
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
    //接收数据
    recvlen = 0;
    retlen = 0;
    ptr = recvbuf;
    leftlen = RECV_BUF_SIZE - 1;
    //do
    {
        retlen = recv(sock_fd, ptr, leftlen, 0) ;
        if(retlen < 0)
        {
            printf("receive data error\n");
            close(sock_fd);
            exit(1);
        }
        //recvlen += retlen;
        //leftlen -= retlen;
        //ptr += retlen;
    }
    //while(recvlen && leftlen);
    printf("receive data is : %s\n", recvbuf);
    //发送数据
    sprintf(sendbuf, "hello server");
    sendlen = strlen(sendbuf) + 1;
    retlen = 0;
    leftlen = sendlen;
    ptr = sendbuf;
    //while(leftlen)
    {
        retlen = send(sock_fd, ptr, sendlen, 0);
        if(retlen < 0)
        {
            printf("send data error\n");
            close(sock_fd);
            exit(1);
        }
        //leftlen -= retlen;
        //ptr += retlen;
    }
    printf("send data is : %s\n", sendbuf);
    //关闭socket
    close(sock_fd);
}