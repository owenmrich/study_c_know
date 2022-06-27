#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>
#include <signal.h>
static void sig_handler(int sig) 
{
    printf("执行信号处理函数...\n");
}
int main ()
{
    int ret;
    int second = 10;
    //注册信号函数
    struct sigaction sig = {0};
    sig.sa_sigaction = sig_handler;
    sig.sa_flags = 0;
    ret = sigaction(SIGINT, &sig, NULL);

    //信号集初始化
    sigset_t new_mask, wait_mask;
    sigemptyset(&new_mask);

    //添加 删除 
    sigaddset(&new_mask, SIGINT);
    /* 向进程的信号掩码中添加信号 */
    sigprocmask(SIG_BLOCK, &new_mask, NULL);
    printf("定时时长: %d 秒\n", second);
    alarm(second);
    
     /* 挂起、等待信号唤醒 */
    if (-1 != sigsuspend(&wait_mask))
        exit(-1);
    /* 从信号掩码中移除信号 */
    sigprocmask(SIG_UNBLOCK, &new_mask, NULL);
    while(1)
    {
        sleep(1);
        printf("\n");
    }
    

    //向进程发送信号
    kill(pid, SIGINT);
    //raise(SIGINT); = kill(getpid(),SIGINT);

    return 0;
}