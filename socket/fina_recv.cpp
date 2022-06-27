#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define RECEIVE_BUF_SIZE 1024
#define MAX_LISTEN_NUM 5
void *tranFile(void *sendSocket);
void tran(int sock_fd);
int main(int argc,char **argv)
{
	if(argc < 3)
	{
		perror("param must >= 3");
		return -1;
	}
    //客户端的udp socket地址与本机的udp socket地址
	struct sockaddr_in addr;
    struct sockaddr_in sendaddr;
    memset((void *)&addr, 0, sizeof(addr));
    memset((void *)&sendaddr, 0, sizeof(sendaddr)); 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);
    //服务器监听的tcp Socket
    int listen_sock = 0;
    //服务器监听的udp Socket
    int udp_socket = 0;
    //与客户端连接的tcp Socket
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
    hostaddr.sin_port = htons(atoi(argv[2]));
    hostaddr.sin_addr.s_addr = inet_addr(argv[1]);
    //创建Socket
    listen_sock = socket(AF_INET, SOCK_STREAM, 0);
    udp_socket = socket(AF_INET,SOCK_DGRAM,0);
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
    //绑定Socket
	int res = bind(udp_socket,(struct sockaddr *)&addr,sizeof(struct sockaddr));
	printf("bind res = %d\n",res);
    //接收数据的内存长度
	char read_buf[128] = {0};
    //写入数据的内存长度
	char write_buf[128] = {0};
    //定义udp客户端的长度
	int size = sizeof(struct sockaddr);
    //等待接收连接
    app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
	while(1)
	{
        //接收文字
		bzero(read_buf,sizeof(read_buf));
		bzero(write_buf,sizeof(write_buf));
		recvfrom(udp_socket,read_buf,sizeof(read_buf) - 1,0,(struct sockaddr *)&sendaddr,(socklen_t *)&size);
		char ipbuf[16] = {0};
		inet_ntop(AF_INET,&sendaddr.sin_addr.s_addr,ipbuf,sizeof(ipbuf));
		printf("send:%s",read_buf);
		printf("send addr: ip = %s,port = %d\n",ipbuf,ntohs(sendaddr.sin_port));
        //关闭聊天
        if(strcmp(read_buf,"quit\n") == 0)
		{
		   printf("send quit the communication!\n");
		   break;
		}
        //发送文件
        if(strcmp(read_buf,"file\n") == 0)
        {
            pthread_t tid;
           
            int ret = pthread_create(&tid, NULL, tranFile, (void *)&app_sock);
            if(ret != 0)
            {
                printf("thread create error\n");
                close(app_sock);
                exit(1);
            }
            else
            {
                printf("thread create ok\n");
            }
        }
		//发送文字
		printf("recv:");
		fgets(write_buf,sizeof(write_buf),stdin);
		sendto(udp_socket,write_buf,strlen(write_buf),0,(struct sockaddr *)&sendaddr,sizeof(struct sockaddr));
		if(strcmp(write_buf,"quit\n") == 0)
		{
		   printf("you quit the communication!\n");
		   break;
		}
        //接收文件
        if(strcmp(write_buf,"file\n") == 0)
		{
		   tran(app_sock);
		}
		
	}
	close(udp_socket);
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