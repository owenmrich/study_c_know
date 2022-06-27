#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static void *clean(void *arg)
{
    printf("clean\n");
}
static void bye(void)
{
    time_t t;
    struct tm t1;
    char buf[128]={0};
    char tm_str[128]={0};
    t = time(NULL);//获得日历时间
    localtime_r(&t,&t1);
    strftime(tm_str, sizeof(tm_str), "%Y-%m-%d %A %H:%M:%S", &t1);//自定义打印时间 
    printf("当前时间: %s\n", tm_str);
    printf("感谢使用!!!!\n");
    printf("——Owenmrich\n");
}
static void *fun(void *arg)
{
    //添加
    pthread_cleanup_push(clean,NULL);
    printf("子线程：pid is %d\n",getpid());
    printf("子线程：thread is %lu\n",pthread_self());
    pthread_exit((void*)10);
    pthread_cleanup_pop(1);
    //pthread_cleanup_pop(0);移除
    //
}
static void *fun2(void *arg)
{
    int size = 10;
    pthread_detach(pthread_self());
    printf("tid2子线程：pid is %d\n",getpid());
    printf("tid2子线程：thread is %lu\n",pthread_self());
    for(;size>0;size--)
    {
        printf("1\n");
    }
    pthread_exit((void*)10);
}
static void *fun1(void *arg)
{
    int b=30000;
    /* 设置为不可被取消 */
    //pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

    for(;;)
    {   
        //没有取消点，这段时候是不会取消的，使用下面的产生取消点
        pthread_testcancel();
    }
    printf("tid1子线程：pid is %d\n",getpid());
    printf("tid1子线程：thread is %lu\n",pthread_self());
    pthread_exit((void*)11);
}
int main(void)
{
    
    pthread_t tid, tid1,tid2;
    int ret;
    void *tatu;
    //注册线程
    ret = pthread_create(&tid, NULL, fun, NULL);
    ret = pthread_create(&tid1, NULL, fun1, NULL);
    ret = pthread_create(&tid2, NULL, fun2, NULL);

    if (ret) 
    {
        fprintf(stderr, "Error: %s\n", strerror(ret));
        exit(-1);
    }
    printf("主线程：pid is %d\n",getpid());
    printf("主线程：thread is %lu\n",pthread_self());
    //取消线程
    pthread_cancel(tid1);
    ret = pthread_join(tid1,&tatu);
    printf("tid1线程取消子线程, code=%ld\n", (long)tatu);
    sleep(10);

    //回收线程
    ret = pthread_join(tid,&tatu);
    if (ret) 
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }
    printf("tid线程终止, code=%ld\n", (long)tatu);
    
    ret = pthread_join(tid2,&tatu);
    if (ret) 
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }
    printf("tid线程终止, code=%ld\n", (long)tatu);
    
    
    atexit(bye);
    exit(0);
}