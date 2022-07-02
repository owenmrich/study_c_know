#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

//定义信号，此处直接使用系统信号，项目中可根据需要自定义信号值
#define SIG_UI_QUIT 35
#define SIG_PHONE_QUIT 36
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
int get_phone_pid() 
{
    int pid = -1;
    FILE *fp = NULL;
    char buf[12] = {0};
    //打开管道，执行shell命令查找进程名为task_phone_sig的pid
    fp = popen("ps -e | grep \'task_phone_sig\' | awk \'{print $1}\'","r") ;
    fgets(buf,sizeof(buf), fp) ;
    if(strlen(buf) > 0)
    {
        pid = atoi (buf) ;
    }
    return pid; 
}
//信号处理函数
void sig_deal(int sig)
{
    if(sig == SIG_PHONE_QUIT)
    {
        printf("task ui recv quit!\n") ;
        exit(0) ;
    }
}
//改变通话状态
static void change_state (void)
{
    if(get_phone_pid() > 0)
    {
        kill (get_phone_pid(),SIG_PHONE_QUIT) ;//发送信号给task_ phone
    }
    printf ("Send quit msg ok! \n") ;
}
int main(void)
{
    int ch=0;
    //设置SIG_PHONE_QUIT信号处理函数
    signal(SIG_PHONE_QUIT, sig_deal) ;
    while(1)
    {
        /*获取键盘输入，若为'q'，则通知通话任务改变状态*/
        ch = get_char() ;
        if(ch == 'q')
        {
            change_state();
        }
        else if(ch == 'c') //退出task_ ui_ sig
        {
            break;
        }
    }
    return 0;
}