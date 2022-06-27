#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>
static pthread_key_t strerror_key;
static pthread_once_t once = PTHREAD_ONCE_INIT;
static void clean(void)
{
    printf("hehhehehehheh\n");
    frer(buf);
}
static void create_key(void) 
{
    /* 创建一个键(key)，并且绑定键的解构函数 */
    if (pthread_key_create(&strerror_key, clean))
            pthread_exit(NULL);
}
static void *fun(void *arg)
{
    char *buf;
    /* 创建一个键(只执行一次 create_key) */
    if (pthread_once(&once, create_key))
            pthread_exit(NULL);
    /* 获取 */
    buf = pthread_getspecific(strerror_key);
    if (NULL == buf) 
    { //首次调用 my_strerror 函数，则需给调用线程分配线程私有数据
        buf = malloc(MAX_ERROR_LEN);//分配内存
        if (NULL == buf)
            pthread_exit(NULL);
        /* 保存缓冲区地址,与键、线程关联起来 */
        if (pthread_setspecific(strerror_key, buf))
            pthread_exit(NULL);
    }
    if (errnum < 0 || errnum >= _sys_nerr || NULL == _sys_errlist[errnum])
            snprintf(buf, MAX_ERROR_LEN, "Unknown error %d", errnum);
    else 
    {
        strncpy(buf, _sys_errlist[errnum], MAX_ERROR_LEN - 1);
        buf[MAX_ERROR_LEN - 1] = '\0';//终止字符
    }
    return buf;

}
int main()
{
    pthread_t tid;
    pthread_create(&tid,NULL,fun,NULL);
    pthread_join(tid,NULL);
    exit(0);
}