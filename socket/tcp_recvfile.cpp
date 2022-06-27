#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define MAX_LISTEN_NUM 5
#define RECEIVE_BUF_SIZE 1024
#define LISTEN_PORT 7800
void *tranFile(void *sendSocket);
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
    //线程定义
    pthread_t tid;
    while(1)
    {
        app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);//等待接收连接
        int ret = pthread_create(&tid, NULL, tranFile, (void *)&app_sock);
        if(ret != 0)
        {
            printf("thread create error\n");
            close(app_sock);
            exit(1);
        }
    }
    close(listen_sock);
    return 0;
}

void *tranFile(void *sendSocket)
{
    int sock = *(int *)sendSocket;
    unsigned char buf[1024];
    int buflen = 1024, k = 0;
    char file[256] = {0};
    sprintf(file, "1.txt");
    FILE *source;
    source = fopen(file, "rb");
    if(source == NULL)
    {
        printf("open file error\n");
        close(sock);
    }
    else
    {
        printf("begin tran file %s\n", file);
        //先把文件名发送过去
        int iSendLen = write(sock, file, strlen(file));
        if(iSendLen < 0)
        {
            printf("send file name error\n");
            fclose(source);
            close(sock);
            return 0;
        }
        //等待对方准备好
        memset(buf, 0, buflen);
        int iRealLength = read(sock, buf, 1024);
        printf("get string: %s , %d\n", buf, iRealLength);
        //开始发送文件内容
        memset(buf, 0, buflen);
        while((k = fread(buf, 1, buflen, source)) > 0)
        {
            printf("tran file length:%d",k);
            //循环发送直到，文件结束
            int iSendLen = write(sock, buf, k);
            if(iSendLen < 0)
            {
                printf("send file erroe\n");
                break;
            }
            memset(buf, 0, buflen);
        }
        printf("tran file finish\n");
        fclose(source);
        close(sock);
    }
    return 0;
}        