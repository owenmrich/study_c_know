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
#define FIFO "/tmp/myfifo"
int main(int argc, char **argv)
{
    int fd = -1;
    char buf[BUF_MAX_LEN] = {0};
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
    /*步骤2:打开有名管道，并设置非阻塞标志*/
    if((fd = open(FIFO, O_RDONLY | O_NONBLOCK,0)) < 0)
    {
        perror("open fifo! ");
        exit(1);
    }
    /*步骤3:从管道中读取消息字符串*/
    while(1)
    {
        memset(buf, 0,sizeof(buf)) ;
        if((len = read(fd, buf, sizeof(buf))) > 0)
        {    
            printf("read %s from FIFO\n", buf) ;
            break;
        }
        printf("no data yet\n") ;
        sleep(1) ;
    }
    /*步骤4:关闭有名管道*/
    close(fd);
    return 0;
}