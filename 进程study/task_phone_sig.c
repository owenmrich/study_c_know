#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

//下一步时间间隔
#define TIME_NEXT 50
//定义信号，此处直接使用系统信号，项目中可根据需要自定义信号值
#define SIG_UI_QUIT 35
#define SIG_PHONE_QUIT 36
//定义通话状态
enum TASK_PHONE_STATE
{
    TASK_PHONE_STATE_NONE = 0,
    TASK_PHONE_STATE_RING, 
    TASK_PHONE_STATE_TALK,
    TASK_PHONE_STATE_HANGUP,
};
int phone_state = TASK_PHONE_STATE_NONE;
//设置通话状态
void set_state(int state)
{
    phone_state = state;
}
//获取通话状态
int get_state (void) 
{
    return phone_state;
}
int get_ui_pid() 
{
    int pid = -1;
    FILE *fp = NULL;
    char buf[12] = {0};
    //打开管道，执行shell命令查找进程名为task_ui_sig的pid
    fp = popen("ps -e | grep \'task_ui_sig\' | awk \'{print $1}\'","r") ;
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
    if(sig == SIG_UI_QUIT)
    {
    printf ("Task ui hangup! \n");
    set_state(TASK_PHONE_STATE_HANGUP);
    }
}
int main(void)
{
    int time = 0;
    //设置SIG_UI_QUIT信号处理函数
    signal(SIG_UI_QUIT, sig_deal) ;
    while (1)
    {
        /*模拟与其他用户处理通信协议，每隔5s进入下一状态*/
        time++;
        if (time >= TIME_NEXT)
        {
            time = 0;
            if(get_state() == TASK_PHONE_STATE_RING)
            {
                set_state(TASK_PHONE_STATE_TALK);
            }
            else if(get_state() == TASK_PHONE_STATE_TALK)
            {
                set_state(TASK_PHONE_STATE_HANGUP) ;
            }
            else
            {
                set_state(TASK_PHONE_STATE_RING) ;
            }
            printf("Current state is %d!\n", get_state()) ;
        }
        /*若当前通话状态为挂断，则退出任务，并发送信号给UI*/
        if(get_state() == TASK_PHONE_STATE_HANGUP)
        {
            if(get_ui_pid() > 0)
            {
                kill(get_ui_pid(), SIG_UI_QUIT);
                printf ("Send quit msg! \n");
            }
            break;
        }
        usleep (100*1000) ;
    }
    return 0;
}