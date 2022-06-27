#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
static pthread_rwlock_t rwlock;//定义读写锁
static int g_count = 0;
static void *read_thread(void *arg)
 {
    int number = *((int *)arg);
    int j;
    for (j = 0; j < 10; j++)
    {
        pthread_rwlock_rdlock(&rwlock); //以读模式获取锁
        printf("读线程<%d>, g_count=%d\n", number+1, g_count);
        pthread_rwlock_unlock(&rwlock);//解锁
        sleep(1);
    }
    return (void *)0; 
}
static void *write_thread(void *arg) 
{
    int number = *((int *)arg);
    int j;
    for (j = 0; j < 10; j++) 
    {
        pthread_rwlock_wrlock(&rwlock); //以写模式获取锁
        printf("写线程<%d>, g_count=%d\n", number+1, g_count+=20);
        pthread_rwlock_unlock(&rwlock);//解锁
        sleep(1);
    }
    return (void *)0; 
}
static int nums[5] = {0, 1, 2, 3, 4};
int main(int argc, char *argv[])
{
    pthread_t tid[10];
    int j;
    /* 对读写锁进行初始化 */
    pthread_rwlock_init(&rwlock, NULL);
    /* 创建 5 个读 g_count 变量的线程 */
    for (j = 0; j < 5; j++)
        pthread_create(&tid[j], NULL, read_thread, &nums[j]);
    /* 创建 5 个写 g_count 变量的线程 */
    for (j = 0; j < 5; j++)
        pthread_create(&tid[j+5], NULL, write_thread, &nums[j]);
    /* 等待线程结束 */
    for (j = 0; j < 10; j++)
        pthread_join(tid[j], NULL);//回收线程
        /* 销毁自旋锁 */
    pthread_rwlock_destroy(&rwlock);
    exit(0);
}