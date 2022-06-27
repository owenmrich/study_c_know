#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
void tran(int sock);
void *tranFile(void *sendSocket);
#define RECEIVE_BUF_SIZE 1024
int main(int argc,char **argv)
{
	if(argc < 3)
	{
		perror("param must >= 3");
		return -1;
	}
    //设置本机与服务器udp socket地址
	struct sockaddr_in addr;
    struct sockaddr_in sendaddr;
    memset((void *)&addr, 0, sizeof(addr));
    memset((void *)&sendaddr, 0, sizeof(sendaddr)); 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
    
    //定义服务器的tcp socket通讯地址
    struct sockaddr_in ser_addr;
    ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(atoi(argv[2]));
	ser_addr.sin_addr.s_addr = inet_addr(argv[1]);
    //定义tcp socket
    int sock_fd = 0;
    //创建tcp socket
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //定义udp socket
    int udp_socket;
    //创建udp socket
    udp_socket = socket(AF_INET,SOCK_DGRAM,0);
    //连接到服务器tcp
    if(connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)) < 0)
    {
        printf("connect socket failedn");
        close(sock_fd);
        exit(1);
    }
    //定义udp服务器端的长度
	int size = sizeof(struct sockaddr);
    //接收数据的内存长度
   	char read_buf[128] = {0};
    //写入数据的内存长度
	char write_buf[128] = {0};

	while(1)
	{
        //发送文字
		bzero(read_buf,sizeof(read_buf));
		bzero(write_buf,sizeof(write_buf));
		printf("send:");
		fgets(write_buf,sizeof(write_buf),stdin);
	    int len = sendto(udp_socket,write_buf,strlen(write_buf),0,(struct sockaddr *)&addr,sizeof(struct sockaddr));
	    printf("send successful!!send len = %d\n",len);
		//关闭对话
        if(strcmp(write_buf,"quit\n") == 0)
		{
		   printf("you quit the communication!\n");
		   break;
		}
        //接收文件
        if(strcmp(write_buf,"file\n") == 0)
		{
		   tran(sock_fd);
		}
        //接收文字
		recvfrom(udp_socket,read_buf,sizeof(read_buf) - 1,0,(struct sockaddr *)&sendaddr,(socklen_t *)&size);
		printf("recv:%s",read_buf);
        //关闭聊天
        if(strcmp(read_buf,"quit\n") == 0)
		{
		   printf("recv quit the communication!\n");
		   break;
		}
        //发送文件
        if(strcmp(read_buf,"file\n") == 0)
		{
		    pthread_t tid;
            int ret = pthread_create(&tid, NULL, tranFile, (void *)&sock_fd);
            if(ret != 0)
            {
                printf("thread create error\n");
                close(sock_fd);
                exit(1);
            }
            else
            {
                printf("thread create ok\n");
            }
		}
	}

	//关闭socket
    close(sock_fd);
	close(udp_socket);
}
//接收文件
void tran(int sock_fd)
{
    int sock = sock_fd;
    printf("start recv file\n");
    //定义接收文件的内存
    char file[RECEIVE_BUF_SIZE] = {0};
    //定义接收数据的内存
    char buf[RECEIVE_BUF_SIZE] = {0};
    //接收文件名称
    int receivelength = 0;
    while(receivelength <= 0)
    {
        receivelength = read(sock, file, sizeof(file));
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
        close(sock);
        exit(1);
    }
    //通知服务器准备好了
    sprintf(buf, "ready");
    write(sock, buf, strlen(buf));
    //开始接收文件内容
    memset(buf, 0, RECEIVE_BUF_SIZE);
    while((receivelength = read(sock, buf, RECEIVE_BUF_SIZE)) > 0)
    {
        if(receivelength < 0)
        {
            printf("receive file error\n");
            fclose(target);
            close(sock);
            exit(1);
        }
        printf("receive file length:%d\n", receivelength);
        fwrite(buf, 1, receivelength, target);
        memset(buf, 0, RECEIVE_BUF_SIZE);
    }
    printf("receive file success\n");
    //关闭文件句柄
    fclose(target);
    close(sock);
}
//发送文件 
void *tranFile(void *sendSocket)
{
    int sock = *(int *)sendSocket;
    unsigned char buf[1024];
    int buflen = 1024, k = 0;
    char file[256] = {0};
    sprintf(file, "1.bat");
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