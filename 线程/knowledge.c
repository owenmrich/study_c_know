/*二级指针 
int a=1;  int *p1= &a;  int **p2 = &p1;*/
//线程同步

pthread_mutex_lock (加锁)  pthread_mutex_unlock (解锁)
pthread_mutex_init (锁初始化) pthread_mutex_destroy (锁的销毁)

避免死锁,使用消息队列