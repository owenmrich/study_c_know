#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
extern char **environ;//获取系统外部全局变量
static void bye(void)
{
    printf("bby\n");
}
int main(int argc, char *argv[])
{
    int i;
    pid_t pid = getpid();
    pid_t ppid = getppid();
    for(i=0;NULL != environ[i]; i++)
    {
        puts(environ[i]);//打印全局变量
    }

    //获得指定环境变量
    const char *str_val = NULL;
    str_val = getenv(argv[1]);
    printf("%s is %s\n",argv[1], str_val);

    char *p[10]={"owem"};
    char *p1[10]={"./pid"};//添加环境变量
    setenv(p[0], p1[0], 0);

    setenv(argv[2], argv[3], 0);
    //移除环境变量unsetenv(argv[2]);
    for( i=0;NULL != environ[i]; i++)
    {
        puts(environ[i]);//打印全局变量
    }


    atexit(bye);
    exit(0);
}