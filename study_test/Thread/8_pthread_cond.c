#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
static pthread_mutex_t mutex; //定义互斥锁
static pthread_cond_t cond; //定义条件变量
static int g_avail = 0; //全局共享资源
/* 消费者线程 */
static void *consumer_thread(void *arg) 
{
    for ( ; ; ) 
    {
        pthread_mutex_lock(&mutex);//上锁 
        while (0 >= g_avail)
        pthread_cond_wait(&cond, &mutex);//等待条件满足
        while (0 < g_avail)
        g_avail--; //消费
        printf("子线程 %lu 消费\n",pthread_self());
        sleep(3);
        pthread_mutex_unlock(&mutex);//解锁
    }
    return (void *)0; 
}
/* 消费者线程 */
static void *consumer_thread1(void *arg) 
{
    for ( ; ; ) 
    {
        pthread_mutex_lock(&mutex);//上锁
        while (0 >= g_avail)
        pthread_cond_wait(&cond, &mutex);//等待条件满足
        while (0 < g_avail)
        g_avail--; //消费
        printf("子线程1 %lu 消费\n",pthread_self());
        pthread_mutex_unlock(&mutex);//解锁
    }
    return (void *)0; 
}
/* 主线程（生产者） */
int main(int argc, char *argv[])
{
    pthread_t tid,tid1;
    int ret;
    /* 初始化互斥锁和条件变量 */
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);
    /* 创建新线程 */
    ret = pthread_create(&tid, NULL, consumer_thread, NULL);
    ret = pthread_create(&tid1, NULL, consumer_thread1, NULL);

    if (ret) 
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
        exit(-1);
    }
    for ( ; ; ) 
    {
        pthread_mutex_lock(&mutex);//上锁
        g_avail++; //生产
        pthread_mutex_unlock(&mutex);//解锁
        pthread_cond_signal(&cond);//向条件变量发送信号
    }
    exit(0);
}