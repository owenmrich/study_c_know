#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static pthread_mutex_t mutex;//申明互斥量
static int size = 0;
static void *fun(void *arg)
{

    printf("子线程：pid is %d\n",getpid());
    printf("子线程：thread is %lu\n",pthread_self());

}

int main(void)
{
    
    pthread_t tid, tid1,tid2;
    int ret;
    //注册线程
    ret = pthread_create(&tid, NULL, fun, NULL);
    if (ret) 
    {
        fprintf(stderr, "Error: %s\n", strerror(ret));
        exit(-1);
    }
    printf("主线程：pid is %d\n",getpid());
    printf("主线程：thread is %lu\n",pthread_self());
    while(1)
    {
        
    }
    sleep(30);
    ret = pthread_join(tid,&tatu);
    if (ret) 
    {
        fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
        exit(-1);
    }
    
    exit(0);
}