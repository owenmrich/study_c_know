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
    /*步骤1:打开FIFo管道，并设置非阻塞标志*/
    fd=open(FIFO,O_WRONLY | O_NONBLOCK,0) ;
    if(fd == -1)
    {
        printf("open error; no reading process\n") ;
        return -1;
    }
    /*步骤2:获取将要发送的消息字符串*/
    if(argc == 1)
    {
        printf("Please send something\n") ;
        return -1;
    }
    strcpy(buf, argv[1]);
    /*步骤3:向管道中写入字符串*/
    if((len = write(fd, buf, sizeof(buf)))== -1)
    {
        printf ( "The FIFO has not been read yet.Please try later\n");   
    }
    else
    {
        printf("write %s to the FIFO\n", buf) ;
    }
    /*步骤4:关闭有名管道*/
    close (fd) ;
    return 0;
}