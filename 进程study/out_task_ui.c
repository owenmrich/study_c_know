#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define BUF_MAX_LEN 64
//有名管道的标识符
#define FIFO "/fiforead"
#define FIFO2 "/fifowrite"
//非阻塞检测键盘输入
static int get_char()
{
    fd_set rfds; 
    struct timeval tv;
    int ch=0;
    FD_ZERO(&rfds) ;
    FD_SET(0, &rfds) ;
    tv.tv_sec = 0;
    tv.tv_usec = 1; // 设置等待超时时间
    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar();
    }
    return ch;
}
int main(int argc,char **argv){
	int fd = -1;
    int fd2 = -1;
    int len;
    int time = 20;
    int ch = 0;
	char buf[BUF_MAX_LEN] = {0};
    char writebuf[BUF_MAX_LEN] = {0};
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
    fd = open(FIFO, O_RDONLY | O_NONBLOCK,0);
	fd2 = open(FIFO2, O_WRONLY | O_NONBLOCK,0);
	while(1)
    {
		memset(buf, 0,sizeof(buf));
        if((len = read(fd, buf, sizeof(buf))) > 0)
        {    
            printf("read %s from FIFO\n", buf);
            if(strcmp(buf,"quit") == 0) 
            {
                printf("phone close\n");
                continue;
            }
            printf("是否接听\n");
            printf("Yes:a No:q\n");
            while(time)
            {
                ch = getchar();
                printf("%d",ch);
                if(ch == 'a')
                {
                    strcpy(writebuf,"hello phone");
                    len = write(fd2, writebuf, sizeof(writebuf));
                    printf("wirte hello phone to fifo\n");
                    break;
                }
                sleep(1);  
                time--;
            }   
            time = 20;
            printf("ok\n");           
        }
        else
        {
            ch = get_char();
            if(ch == 'q')
            {
                printf("ui quit the chat\n");
                strcpy(writebuf,"quit");
                write(fd2, writebuf, sizeof(writebuf));
            }
            else if(ch == 'c') //退出
            {
                break;
            }
        }
        sleep(5);
	}
    close(fd);
	close(fd2);
	return 0;
}