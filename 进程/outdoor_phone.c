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
#define SERVER_PORT 7800
#define MAX_LISTEN_NUM 5
#define BUF_MAX_LEN 64
#define LISTEN_PORT 7800
//有名管道的标识符
#define FIFO "/home/study/work/work1/1.txt"
#define FIFO2 "/home/study/work/work1/2.txt"
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
    //定义服务器的socket通讯地址
    struct sockaddr_in ser_addr;
    //设置服务器的socket参数
    memset(&ser_addr, 0, sizeof(ser_addr));
    ser_addr.sin_family= AF_INET;
    inet_aton("127.0.0.1", (struct in_addr *)&ser_addr.sin_addr);
    ser_addr.sin_port = htons(SERVER_PORT);
    //创建socket
    int sock_fd = 0;
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    //连接到服务器
    connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));
    */
    while(1)
    {
        printf("wait call\n");
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
            if(strcmp(recvbuf,"call") == 0)
            {
                printf("ui call\n");
                printf("wait a monment \n");
                sleep(1);
                /*
                cahr sendbuf[1000] = {0};
                strcpy(sendbuf,"hello use phone\n");
                send(sock_fd,buf,sizeof(buf),0);
                recv(sock_fd,buf,sizeof(buf),0);
                */
                if(strcmp(buf,"quit") == 0)
                {
                    printf("use qiut\n");
                    write(fd,buf,sizeof(buf));
                }
            }
        }
        sleep(1);
    }
    close(fd);
	close(fd2);
	return 0;
}
