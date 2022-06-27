#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static void *fun(void *arg)
{

    printf("子线程：pid is %d\n",getpid());
    printf("子线程：thread is %lu\n",pthread_self());
    pthread_exit((void*)10);

}
static void *fun1(void *arg)
{

    printf("子线程：pid is %d\n",getpid());
    printf("子线程：thread is %lu\n",pthread_self());
    sleep(5);
    printf("zhehsdnalwi\n");
    pthread_exit((void*)10);

}
int main()
{
    pthread_t tid, tid1;
    size_t stacksize;
    pthread_attr_t attr, attr1;
    pthread_attr_init(&attr);//属性初始化
    pthread_attr_init(&attr1);//属性初始化

    pthread_attr_setstacksize(&attr,4096);//设置栈的大小
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);//设置线程分离态


    pthread_create(&tid,&attr,fun,NULL);
    pthread_create(&tid1,&attr1,fun1,NULL);
    pthread_join(tid,NULL);

    printf("1\n");
    sleep(5);
    pthread_attr_destroy(&attr);//销毁attr对象
    exit(0);
}