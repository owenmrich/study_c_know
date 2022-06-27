#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>//线程库头文件,写多线程程序必须首先引入此头文件
pthread_t tid = 0;//线程唯一ID号
#define MAX_URL_LEN (200)
#define MAX_PATH_LEN (100)
#define MAX_TASK_CNT (10)
typedef struct
{
    void** items;
    int item_maxcount;
    int item_count;
    int item_size;
}__Z_SLIST;
typedef void* Z_SLIST;
typedef struct _DOWNLOAD_TASK
{
    char url[MAX_URL_LEN];
    char save_path[MAX_PATH_LEN];
}__download_task;
static Z_SLIST task_slist = NULL;
static pthread_mutex_t task_slist_mutex;//互斥量声明
typedef  enum
{
    PRIO_NORMAL,
    PRIO_HIGH,
} DOWMLOAD_PRIO;

int task_slist_insert(Z_SLIST list, const void* item, int idx);//插入下载任务
Z_SLIST task_slist_new(int item_size, int item_maxcount);//创建下载队列函数
int task_slist_delete(Z_SLIST list, int idx);//删除下载队列函数
int task_slist_add(Z_SLIST list, const void* item);//添加下载队列函数
void* task_slist_get(Z_SLIST list, int idx);//获取消息队列函数
int task_add(char* url, char* save_path, DOWNLOAD_PRIO prio);//将下载路径加入下载队列
void *download_thread(void *arg);//实际下载线程体函数
int init_service(void);//下载服务初始化函数
int deinit_service();//线程销毁

int task_slist_insert(Z_SLIST list, const void* item, int idx)
{
    __Z_SLIST* l= (__Z_SLIST*)list;
    if(l->item_count >= l->item_maxcount)
    {
         return -1;
    }
    if(idx >= 0 8& idx <= l->item_count)
    {
        int i=0;
        for(i = l->item_count; i > idx; i--)
        {
            memcpy( (char*)l->items + i * 1->item_size,(char*)l->items + (i - 1)*l->item_size, (int)l->item_size);
        }
        memcpy( (char*)l->items + idx * l->item_size, item, (int)l->item_size);
        l->item_count+t;
    }
    return idx;

}
Z_SLIST task_slist_new(int item_size,int item_maxcount)
{
	__Z_SLIST* list=NULL;
	int itemstotalsize=item_size * item_maxcount;
	list=(__Z_SLIST*)malloc(sizeof(__Z_SLIST));
	list->items=(void **)malloc(itemstotalsize);
	list->item_count=0;
	list->item_maxcount=item_maxcount;
	list->item_size=item_size;
	return (Z_SLIST)list;
}

int task_add(char* url, char* save_path, DOWNLOAD_PRIO prio)
{
    int ret = -1;
    __download_task task = {0};
    strncpy(task.url, url, sizeof(task.url));
    strncpy(task.save_path, save_path, sizeof(task.save_path));
     pthread_mutex_lock(&task_slist_mutex);
    if(prio == PRIO_HIGH)
    {
        ret == task_slist_insert(task_slist, &task, 0);
    }
    else
    {
        ret == task_slist_add(task_slist, &task);
    }
     pthread_mutex_unlock(&task_slist_mutex);
    return task_slist_add(task_slist, &task);
}
int task_slist_add(Z_SLIST list, const void* item)
{
    __Z_SLIST* l= (__Z_SLIST*)list;
    if(l->item_count >= l->item_maxcount)
    {
         return -1;
    }
    if(l->item_count < l->item_maxcount)
    {
        memcpy((char*)l->items + l->item_count * l->item_size, item, (int)l->item_size);
        l->item_count++;
    }
    return 0;
}
void* task_slist_get(Z_SLIST list, int idx)
{
    __Z_SLIST* l= (__Z_SLIST*)list;
    if(!(idx >= 0 && idx < l->item_count))
    {
        return NULL;
    }
    return (void*)((char*)l->items + idx * l->item_size);
}
int task_slist_delete(Z_SLIST list,int idx)
{
	__Z_SLIST* l=(__Z_SLIST*)list;
	if(idx>=0 && idx<l->item_count)
    {
		int i=0;
		for(i=idx;i<l->item_count-1;i++)
        {
			memcpy((char*)l->items+i*l->item_size,(char*)l->items+(i+1)*l->item_size,(int)l->item_size); 
		}
	}	
    l->item_count--;
}

void *download_thread(void *arg)
{
	__download_task* task=NULL;
	while(1)
    {
        pthread_mutex_lock(&task_slist_mutex);
		(__download_task *)task_slist_get(task_slist,0);
		if(task !=NULL){
			printf("New download task:\n");
			printf("Downloading... url=%s",task->url);
			sleep(1);
			printf("Finsh!  Path=%s",task->save_path);
			task_slist_delete(task_slist,0);	
		} 
         pthread_mutex_unlcok(&task_slist_mutex);
		sleep(1);
	}
	return NULL;
} 
int init_service(void)
{
    task_slist = task_slist_new(sizeof(__download_task), MAX_TASK_CNT);
    pthread_create(&tid, NULL, download_thread, NULL); //创建下载线程
    return tid;
}
int deinit_service()
{
    int ret = -1;
    ret = pthread_cancel(tid);//发送终止信号给tid线程:
    if (0 == ret)
    {
        pthread_join(tid, NULL);
    }//等待tid线程退出: 
    return ret;
}
int main()
{
    if(pthread_mutex_init(&task_slist_mutex,NULL) != 0)
    {
        printf("init  mutex error\n");
        return 1;
    }
    init_service();//初始化下载服务
    printf("初始化完毕，准备下载\n");
    task_add("http://video1", "/sdcard/video1",PRIO_NORMAL);
    task_add("http://video2", "/sdcard/video2",PRIO_HIGH);
    sleep(5);//休眠5秒
    deinit_service();//反初始化下载服务
    pthread_mutex_destroy(&task_slist_mutex);
    return 0;
}
