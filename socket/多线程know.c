头文件: pthread.h
定义线程: pthread_t
创建线程函数:
int pthread_create(pthread_t *tidp,const pthread_attr_t *attr,(void*)(*start_rtm)(void*),void *arg)
参数:
第一个参数为指向线程标识符的指针。
第二个参数用来设置线程属性。
第三个参数是线程运行函数的起始地址。
最后一个参数是运行函数的参数。
若线程创建成功,则返回0。若线程创建失败,则返回出错编号,并且*thread中的内容是未定义的。
等待线程执行完成:
int pthread_join(pthread_t thread, void **retval)
描述: pthread_join()函数,以阻塞的方式等待thread指定的线程结束。当函数返回时,被
等待线程的资源被收回。如果线程已经结束,那么该函数会立即返回。并且thread指定的线程必须是joinable的。
参数: thread: 线程标识符,即线程ID,标识唯一线程。retval: 用户定义的指针,用来存储被等待线程的返回值。
返回值: 0代表成功。失败, 返回的则是错误号。
线程终止退出:
void pthread_exit(void* retval)
