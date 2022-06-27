#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
int main(void) {
    pid_t pid;
    int i;
    /* 创建子进程 */
    pid = fork();
    if (0 > pid) 
    {
        perror("fork error");
        exit(-1);
    }
    else if (0 < pid)//父进程
        exit(0); //直接退出
    /*
    *子进程
    */
    /* 1.创建新的会话、脱离控制终端 */
    if (0 > setsid()) 
    {
        perror("setsid error");
        exit(-1);
    }
    /* 2.设置当前工作目录为根目录 */
    if (0 > chdir("/")) 
    {
        perror("chdir error");
        exit(-1);
    }
    /* 3.重设文件权限掩码 umask */
    umask(0);
    /* 4.关闭所有文件描述符 */
    for (i = 0; i < sysconf(_SC_OPEN_MAX); i++)
            close(i);
    /* 5.将文件描述符号为 0、1、2 定位到/dev/null */
    open("/dev/null", O_RDWR);
    dup(0);
    dup(0);
    /* 6.忽略 SIGCHLD 信号 */
    signal(SIGCHLD, SIG_IGN);
    /* 正式进入到守护进程 */
    for ( ; ; ) 
    {
        sleep(1);
        puts("守护进程运行中......");
    }
    exit(0);
}