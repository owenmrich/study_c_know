#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h> 
int func_waitpid(int signo)
{
    pit_t pid;
    while ((pid = waited(-1, NULL, 0)) > 0)
    {
        printf("chiled %d clear\n", pid);
        sleep(1);
    }
    return 0;
}
int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        perror("fork");
        exit(1);
    }
    else if (pid >0)
    {
        signal(SIGCHLD, &func_waitpid);
        printf("in parent process, sleep for one minute....\n");
        while (1)
        {
            sleep(1);
        }
    }
    else 
    {
        printf("in child process:%d, and exit\n", getpid());
        exit(0);
    }
    return 0;
}