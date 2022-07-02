#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
int sokcetbind();
#define MAX_LISTEN_NUM 5
#define BUF_MAX_LEN 64
#define LISTEN_PORT 7800
//有名管道的标识符
#define FIFO "/fiforead"
#define FIFO2 "/fifowrite"
int main(int argc,char **argv)
{
	int fd = -1;
    int fd2 = -1;
    int len;
    int time = 50;//等待时间
	char buf[1000] = {0};
    char recvbuf[BUF_MAX_LEN] = {0};
    //创建有名管道
     if(access(FIFO, F_OK) != 0)
    {
        if(mkfifo(FIFO,0666) < 0)
        {
            perror("cannot create fifo! ");
            exit(1) ;
        }
    }
    if(access(FIFO2, F_OK) != 0)
    {
        if(mkfifo(FIFO2,0666) < 0)
        {
            perror("cannot create fifo! ");
            exit(1) ;
        }
    }
	// 打开FIFO管道 设置非阻塞标识
    fd = open(FIFO, O_WRONLY | O_NONBLOCK,0);
	fd2 = open(FIFO2, O_RDONLY | O_NONBLOCK,0);
    /*
    //服务器监听的Socket
    int listen_sock = 0;
    int app_sock = 0;
    //本机与客户端socket地址
    struct sockaddr_in hostaddr;
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
    bind(listen_sock, (struct sockaddr*)&hostaddr, sizeof(hostaddr));
    //开始监听客户端请求
    ilisten(listen_sock, MAX_LISTEN_NUM);
    while(1)
    //按收窖户端的连接请求
    {
        app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
    }
    */
    while(1)
    {
        printf("wait call\n");
        memset(buf, 0 ,sizeof(buf));
        /*
            if((len = recv(app_sock,buf,sizeof(buf),0)) > 0)
            {
                write(fd,buf,sizeof(buf));
            }
        */
        memset(recvbuf, 0 ,sizeof(recvbuf));
        if((len = read(fd2, recvbuf, sizeof(recvbuf))) > 0)
        {
            printf("ring\n");
            printf("read %s from fifo\n",recvbuf);
            if(strcmp(recvbuf,"quit") == 0)
            {
                printf("ui hangup\n");
                printf("bgein to wait\n");
                sleep(1);
            }
            else
            {
                printf("chat with outdoor\n");
                /*
                send(app_sock,buf,sizeof(buf),0);
                recv(app_sock,buf,sizeof(buf),0);
                */
            }
        }
        else
        {
            memset(buf, 0 ,sizeof(buf));
            scanf("%s",buf);
            write(fd,buf,sizeof(buf));
        }
        sleep(1);
    }
    close(fd);
	close(fd2);
	return 0;
}
