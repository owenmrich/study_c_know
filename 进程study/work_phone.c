#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//消息最大长度
#define BUF_MAX_LEN 64
//定义有名管道标识
#define FIFO "/home/study/work/work1/1.txt"
#define FIFO2 "/home/study/work/work1/2.txt"
int main(int argc, char **argv)
{
    int fd = -1;
    int fd2 = -1;
    char buf[BUF_MAX_LEN] = {0};
    char writebuf[BUF_MAX_LEN] = {0};
    int len = 0;
    /*步骤1:创建有名管道*/
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
    /*步骤2:打开有名管道，并设置非阻塞标志*/
    if((fd = open(FIFO, O_RDONLY | O_NONBLOCK,0)) < 0)
    {
        perror("open read fifo! ");
        exit(1);
    }
    if((fd2 = open(FIFO2, O_WRONLY | O_NONBLOCK,0)) < 0)
    {
        perror("open write fifo! ");
        exit(1);
    }
    /*步骤3:从管道中读取消息字符串*/
    while(1)
    {
        memset(buf, 0,sizeof(buf));
        if((len = read(fd, buf, sizeof(buf))) > 0)
        {    
            printf("read %s from FIFO\n", buf);
            if(strcmp(buf,"quit") == 0)
            {
                printf("ui %s \n", buf);
            }
            printf("send:\n");
            scanf("%s",writebuf);
            write(fd2, writebuf, sizeof(writebuf));
        }
        printf("no data yet\n") ;
        sleep(1) ;
        

    }
    /*步骤4:关闭有名管道*/
    close(fd);
    close(fd2);
    return 0;
}