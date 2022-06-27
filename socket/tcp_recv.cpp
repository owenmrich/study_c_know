#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
# include <unistd.h>
#define MAX_LISTEN_NUM 5
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define LISTEN_PORT 7800
int main(int argc, char *argv[])
{
    //服务器监听的Socket
    int listen_sock = 0;
    //与客户端连接的Socket
    int app_sock = 0;
    //本机的socket地址
    struct sockaddr_in hostaddr;
    //客户端的socket地址
    struct sockaddr_in clientaddr;
    //客户端地址数据大小
    int socklen = sizeof(clientaddr);
    //发送数据的内存
    char sendbuf[SEND_BUF_SIZE]= {0};
    //接收数据的内存
    char recvbuf[RECV_BUF_SIZE]= {0};
    //参数初始化
    int sendlen = 0;
    int recvlen = 0;
    int retlen = 0;
    int leftlen = 0;
    char *ptr = NULL;
    memset((void *)&hostaddr, 0, sizeof(hostaddr));
    memset((void *)&clientaddr, 0, sizeof(clientaddr)); 
    //设置本机的socket地址
    hostaddr.sin_family = AF_INET;
    hostaddr.sin_port = htons(LISTEN_PORT);
    hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //创建Socket
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_sock < 0)
    {
        printf( "create socket failed\n");
        exit(1);
    }
    //绑定Socket
    if(bind(listen_sock, (struct sockaddr*)&hostaddr, sizeof(hostaddr)) < 0)
    {
        printf("bind socket failed\n");
        close(listen_sock);
        exit(1);
    }
    //开始监听客户端请求
    if(listen(listen_sock, MAX_LISTEN_NUM) < 0)
    {
        printf("listen failed\n");
        close(listen_sock);
        exit(1);
    }
    while(1)
    //按收窖户端的连接请求
    {
        app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
        if(app_sock < 0)
        {
            printf("accept failedn");
            continue;
        }
        //发送数据
        sprintf(sendbuf, "welcome %s:%d here!", inet_ntoa(clientaddr.sin_addr), clientaddr.sin_port);
        sendlen = strlen(sendbuf) + 1;
        retlen = 0;
        leftlen = sendlen;
        ptr = sendbuf;
        //while(leftlen)
        {
            retlen = send(app_sock, ptr, sendlen, 0);
                if(retlen < 0)
            {
                printf("receive data failed\n");
                close(app_sock);
                continue;
            }
            //leftlen -= retlen;
            //ptr += retlen;
        }
        printf("send data is : %s\n", sendbuf);
        //接收数据
        recvlen = 0;
        retlen = 0;
        ptr = recvbuf;
        leftlen = RECV_BUF_SIZE - 1;
        //do
        {
            retlen = recv(app_sock, ptr, leftlen, 0) ;
            if(retlen < 0)
            {
                printf("receive data error\n");
                close(app_sock);
                continue;
            }
            //recvlen += retlen;
            //leftlen -= retlen;
            //ptr += retlen;
        }
        //while(recvlen && leftlen);
        printf("receive data is : %s\n", recvbuf);
        //关闭连接客户端的socket
        close(app_sock);
    }
    //关闭监听的socket
    close(listen_sock);
    return 0;
}