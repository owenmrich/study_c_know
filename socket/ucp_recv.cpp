#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#define SEND_BUF_SIZE 100
#define RECV_BUF_SIZE 100
#define LISTEN_PORT 7801
int main(int argc,char *argv[])
{
    //服务器监听的Socket
    int listen_sock = 0;
    //本机的socket地址
    struct sockaddr_in hostaddr;
    //客户端的socket地址
    struct sockaddr_in clientaddr;
    //接收数据的内存
    char recvfuf[RECV_BUF_SIZE] = {0};
    //发送数据的内存
    //定义接收数据中长度
    
    int sendlen = 0;
    memset((void *)&hostaddr,0,sizeof(hostaddr));
    memset((void *)&clientaddr,0,sizeof(clientaddr));
    //设置本机的socket地址
    hostaddr.sin_family = AF_INET;
    hostaddr.sin_port = htons(LISTEN_PORT);
    hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    //创建Socket
    listen_sock = socket(AF_INET,SOCK_DGRAM,0);
    if(listen_sock < 0)
    {
        printf("create socket failed\n");
        exit(1);
    }
    //绑定Socket
    if(bind(listen_sock,(struct sockaddr *)&hostaddr,sizeof(hostaddr)) < 0)
    {
        printf("bind socket failed\n");
        close(listen_sock);
        exit(1);
    }
    while(1)
    {
        int iRealLength = recv(listen_sock, recvbuf, RECV_BUF_SIZE, 0);
        if(iRealLength < 0)
        {
            close(listen_sock);
            exit(1);
        }
        printf("receive data is : %s length:%d\n", recvbuf, iRealLength);


        
    }
    //关闭监听的socket
    close(listen_sock);
    return 0;

}