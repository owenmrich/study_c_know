#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static pthread_once_t once = PTHREAD_ONCE_INIT;
static void once_con(void)
{
    printf("hehhehehehheh\n");

}
static void *fun(void *arg)
{
    
    printf("子线程：pid is %d\n",getpid());
    printf("子线程：thread is %lu\n",pthread_self());
    pthread_once(&once,once_con);
    pthread_exit((void*)10);

}

int main()
{
    pthread_t tid[3];
    char name[3]={'1','2','3'};
    int i;
    for(i=0;i<3;i++)
    {
        pthread_create(&tid[i],NULL,fun,&name[i]);
    }
    sleep(5);
    exit(0);
}