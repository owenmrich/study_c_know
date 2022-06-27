#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static int testsize = 666;
pthread_mutex_t mutex;//申明互斥量
pthread_mutex_t mutex1;//申明互斥量

/*******************************
*       死锁
*       两个阻塞
********************************/
static void *fun(void *arg)
{
    int i;
    pthread_mutex_lock(&mutex);//阻塞
    sleep(1);
    //pthread_mutex_lock(&mutex1);//阻塞
    pthread_mutex_trylock(&mutex1);//非阻塞
    sleep(2);
    printf("子线程：thread is %lu\n",pthread_self());
    for(i=3;i>0;i--)
    {
        printf("%d + 1 = %d\n",testsize,testsize++);

    }
    sleep(2);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex1);
    pthread_exit((void*)10);
}
static void *fun1(void *arg)
{
    int i;
    pthread_mutex_lock(&mutex1);//阻塞
    sleep(1);
    //pthread_mutex_lock(&mutex);//阻塞
    pthread_mutex_trylock(&mutex);//非阻塞
    sleep(2);
    printf("1\n");
    printf("子线程：thread is %lu\n",pthread_self());
    for(i=3;i>0;i--)
    {
        printf("%d + 1 = %d\n",testsize,testsize++);

    }
    sleep(2);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_unlock(&mutex1);
    pthread_exit((void*)10);
}
int main()
{
    pthread_t tid, tid1;
    pthread_mutexattr_t attr;   
    
    pthread_mutexattr_init(&attr);//初始化锁的对象属性
    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_NORMAL);//设置锁对象属性

    pthread_mutex_init(&mutex, &attr);//初始化互斥量
    pthread_mutex_init(&mutex1, NULL);//初始化互斥量

    pthread_create(&tid,NULL,fun,NULL);
    pthread_create(&tid1,NULL,fun1,NULL);
    pthread_join(tid,NULL);
    pthread_join(tid1,NULL);

    pthread_mutexattr_destroy(&attr);
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex1);

    sleep(10);
    exit(0);
}