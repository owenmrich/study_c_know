#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h> 
int main(void)
{
    pid_t child1, child2, child;
    /*创建子进程1*/
    child1 = fork();
    if (child == -1)
    {
        printf("child1 fork error\n");
        exit(1);
    }
    else if (child1 == 0)
    {
        /*进程1中调用execlp()函数执行"ls -l"*/
        printf("In child1: execute 'ls -l'\n");
        execlp("ls", "ls", "-a", "-l", NULL);

    }
    else /*在父进程中再创建进程2,然后等待两个子进程的退出*/
    {
        child2 = fork();
        if (child2== -1) /*子进程2的创建出错*/
        {
            printf("child2 fork error\n");
            exit(1);
        }
        else if (child2 == 0) /*在子进程2中停留5秒*/
        {
            printf("in child2 :sleep for 5s and then exit\n");
            sleep(5);
            exit(0);
        }
        printf("in father process:\n");
        child = waitpid(child1, NULL, 0);
        if (child == child1)
        {
            printf("Get child1 exit code\n");
        }
        else
        {
            printf("error occured\n"); 
        }
        do
        {
            child = waitpid(child2, NULL, WNOHANG); /*非阻塞式等待*/
            if (child == 0)
            {
                printf("the child2 process has not exited\n");
                sleep(1);
            }
        } while (child == 0);
        if (child == child2)
        {
            printf("get child2 exit code\n");
        }
        else 
        {
            printf("ERRor occured\n");
        }
    }
exit(0);
}