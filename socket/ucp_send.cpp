#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define SERVER_PORT 7801

int main(int argc,char *argv[])
{
    //定义socket
    int sock_fd = 0;
    //定义发送数据的内存
    char sendbuf[SEND_BUF_SIZE] = {0};
    //定义接收数据中长度
    int sendlen = 0;
    char recvbuf[RECV_BUF_SIZE]= {0};
    //定义服务器的socket通讯地址
    struct sockaddr_in ser_addr;
    //设置服务器的socket参数
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    inet_aton("127.0.0.1",(struct in_addr *)&ser_addr.sin_addr);
    ser_addr.sin_port = htons(SERVER_PORT);
    //创建Socket
    sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock_fd < 0)
    {
        printf("create socket failed\n");
        exit(1);
    }
    //发送数据
    while(1)
    {
        
        printf("请输入：\n");
        fgets(sendbuf, SEND_BUF_SIZE, stdin);
        int iRealSend = sendto(sock_fd, sendbuf, strlen(sendbuf) + 1, 0, (struct sockaddr *)(&ser_addr),sizeof(struct sockaddr_in));
        printf("send data is : %s, send length:%d\n", sendbuf, iRealSend);
        int iRealLength = recv(sock_fd, recvbuf, RECV_BUF_SIZE, 0);
        if(iRealLength < 0)
        {
            close(sock_fd);
            exit(1);
        }
        printf("receive data is : %s length:%d\n", recvbuf, iRealLength);

      
    }
    //关闭socket
    close(sock_fd);
}