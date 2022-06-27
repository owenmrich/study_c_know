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
int main()
{
    int i=3;
    pid_t pid;
    struct sigaction sig = {0};
    sigset_t wait_mask;
    sigemptyset(&wait_mask);
    sig.sa_handler = sig_handler;
    sig.sa_flags = 0;
    sigaction(SIGUSR1,&sig, NULL);
    sigaction(SIGINT,&sig, NULL);
    while(i)
    {
        printf("i is %d\n",i);
        i--;
    }
    switch(fork())
    {
        case -1:
            perror("fork error");
            exit(-1);
        case 0:
            printf("子进程open\n");
            sleep(2);
            kill(getppid(),SIGUSR1);
            _exit(0);
        default:
            if(-1 != sigsuspend(&wait_mask))//先执行子进程 等待子进程发送信号唤醒
                exit(-1);
            printf("start oprn 父进程\n");      
    }
    i=4;
    while(i)
    {
        printf("i is %d\n",i);
        i--;
    }
    exit(0);
}