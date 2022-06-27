/*
File : serve.cpp
author: 吴其亮
describe: 支持和客户端之间的相互聊天，相互发送文件
          文字皆udp传输 文件内容由tcp传输，文件名字由udp传输
use: ./serve 127.0.0.1 8888
*/
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
        if(strcmp(read_buf,"sendfile to send\n") == 0)
        {
            unsigned char buf[1024];
            int buflen = 1024, k = 0;
            char file[256] = {0};
            sprintf(file, "1.txt");
            FILE *source;
            source = fopen(file, "rb");
            if(source == NULL)
            {
                printf("open file error\n");
            }
            else
            {
                printf("begin tran file %s\n", file);
                //先把文件名发送过去
                int iSendLen = sendto(udp_socket,file,strlen(file),0,(struct sockaddr *)&sendaddr,sizeof(struct sockaddr));
                //等待对方准备好
                memset(buf, 0, buflen);
                int iRealLength = recvfrom(udp_socket,buf,sizeof(buf) - 1,0,(struct sockaddr *)&sendaddr,(socklen_t *)&size);
                printf("get string: %s , %d\n", buf, iRealLength);
                //开始发送文件内容
                memset(buf, 0, buflen);
                k = fread(buf, 1, buflen, source);
                printf("tran file length:%d",k);
                send(app_sock,buf,sizeof(buf),0);
                memset(buf, 0, buflen);
                printf("tran file finish\n");
                fclose(source);
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
        if(strcmp(write_buf,"sendfile to recv\n") == 0)
		{
            printf("start recv file\n");
            //定义接收文件的内存
            char file[RECEIVE_BUF_SIZE] = {0};
            //定义接收数据的内存
            char buf[RECEIVE_BUF_SIZE] = {0};
            //接收文件名称
            int receivelength = 0;
            while(receivelength <= 0)
            {
                receivelength = recvfrom(udp_socket,file,sizeof(file) - 1,0,(struct sockaddr *)&sendaddr,(socklen_t *)&size);
            }
            printf("receive name length :%d\n", receivelength);
            sprintf(buf,"%s",file);
            printf("begin receive file %s\n", buf);
            //创建接受文件
            FILE *target;
            target = fopen(buf, "wb");
            if(target == NULL)
            {
                printf("open file failed\n");
                exit(1);
            }
            //通知服务器准备好了
            sprintf(buf, "ready");
            sendto(udp_socket,buf,strlen(buf),0,(struct sockaddr *)&sendaddr,sizeof(struct sockaddr));
            //开始接收文件内容
            memset(buf, 0, RECEIVE_BUF_SIZE);
            receivelength = recv(app_sock, buf, RECEIVE_BUF_SIZE, 0);
            printf("receive file length:%d\n", receivelength);
            fwrite(buf, 1, receivelength, target);
            memset(buf, 0, RECEIVE_BUF_SIZE);
            printf("receive file success\n");
            //关闭文件句柄
            fclose(target);
		}
		
	}
    //关闭scoket
    close(app_sock);
	close(udp_socket);

}
  


   
