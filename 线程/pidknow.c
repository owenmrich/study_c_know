#include <pthread.h>
void *func(void *arg)
{

}
pthread_t tid;
ret = pthread_create(&tid,NULL,func,NULL);
int ret = pthread_create(&tid1,NULL,fun1,(void *)&a);
//线程资源回收
pthread_join(tid1,&Tmp);//阻塞int pthread_join(pthread_t thread, void **retval);
pthread_tryjoin_np(tid1,&Tmp);
//非阻塞 回收成功,Tmp为返回值
//通过函数pthread_tryjoin_np,使用非阻塞回收,线程可以根据退出先后顺序自由的进行资源的回收。

//退出
pthread_exit();//主动
pthread_cancel();//被动

//互斥量
pthread_mutex_t mutex;//互斥量变量 一般申请全局变量
//初始化互斥量
ret = pthread_mutex_init(&mutex,NULL);
pthread_mutex_lock(&mutex)
pthread_mutex_unlock(&mutex)//阻塞
pthread_mutex_trylock(&mutex)//非阻塞
pthread_mutex_destory(&mutex)

//信号量
sem_t sem1,sem2,sem3;
ret = sem_init(&sem1,0,1);  //初始化信号量1 并且赋予其资源
sem_wait(&sem1);
sem_post(&sem2);
sem_trywait(sem_t *sem);
sem_destory(&sem1);

//条件变量
static pthread_cond_t  g_tConVar = PTHREAD_COND_INITIALIZER;
pthread_mutex_lock(&g_tMutex);
pthread_cond_wait(&g_tConVar, &g_tMutex);	
/* 打印 */
printf("recv: %s\n", g_buf);
pthread_mutex_unlock(&g_tMutex);
pthread_cond_signal(&g_tConVar); /* 通知接收线程 */