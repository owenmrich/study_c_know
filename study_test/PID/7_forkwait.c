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
#include <sys/wait.h>
static void wait_close(int sig) 
{
    int status;
    int ret;
    printf("执行信号处理函数...\n");
    /* 替子进程收尸 */
    printf("父进程回收子进程\n");
    while ((ret = waitpid(0, &status, WNOHANG)) > 0)
    {
        printf("回收子进程<%d>, 终止状态<%d>\n", ret,WEXITSTATUS(status));         
    }
}
int main()
{
    int i=3;
    struct sigaction sig = {0};
    sigset_t wait_mask;
    sigemptyset(&wait_mask);
    sigemptyset(&sig.sa_mask);
    sig.sa_handler = wait_close;
    sig.sa_flags = 0;
    if (-1 == sigaction(SIGCHLD, &sig, NULL)) 
    {
        perror("sigaction error");
        exit(-1);
    }
    for(;i>0;i--)
    {
        switch(fork())
        {
            case -1:
                perror("fork error");
                exit(-1);
            case 0:
                printf("子进程%d open\n",getpid());
                sleep(2);
                execv("./hello",NULL);
                _exit(0);
            default:
                printf("start oprn 父进程\n");      
        }
    }
    sleep(5);
    return 0;
}