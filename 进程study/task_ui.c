#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <string.h>
//定义消息队列标识
#define MSG_KEY_UI 60003
#define MSG_KEY_PHONE 60002
//定义消息结构体
#define MSG_DATA_LEN 128
struct message {
    long msg_type;
    char msg_data[MSG_DATA_LEN] ;
};
//定义消息类型
enum MSG_TYPE_UI
{
    MSG_TYPE_UI_QUIT = 1,
};
enum MSG_TYPE_PHONE
{
    MSG_TYPE_PHONE_QUIT = 1,
};
//非阻塞检测键盘输入
static int get_char()
{
    fd_set rfds;
    struct timeval tv ;
    int ch=0;
    FD_ZERO(&rfds) ;
    FD_SET(O, &rfds) ;
    tv.tv_sec = 0;
    tv.tv_usec = 1;//设置等待超时时间
    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar() ;
    }
    return ch; 
}
//改变通话状态
static void change_state (void)
{
    int qid_phone = 0;
    struct message msg; 
    //获取通话任务队列标识
    if((qid_phone=msgget(MSG_KEY_PHONE, IPC_EXCL)) == -1)
    {
        printf("get phone msg fail!\n");
        return ;
    }
//添加消息到消息队列
    memset(&msg, 0, sizeof(msg));
    msg.msg_type = MSG_TYPE_UI_QUIT;
    msgsnd(qid_phone, &msg, MSG_DATA_LEN,0) ;
    printf ("Send quit msg ok! \n") ;
}
int main(void)
{
    int qid_ui = 0;
    int ch = 0;
    int len = 0;
    struct message msg;
    /*创建消息队列*/
    if((qid_ui=msgget(MSG_KEY_UI,0666|IPC_CREAT)) == -1)
    {
        perror ("msgget") ;
        exit (1) ;
    }   
    while(1)
    {
        /*步骤2:读取消息队列*/
        memset(&msg, 0, sizeof(msg)) ;
        if (msgrcv(qid_ui, &msg, MSG_DATA_LEN,0, IPC_NOWAIT) >= 0) 
        {
            if (msg.msg_type == MSG_TYPE_PHONE_QUIT)
            {
                printf ("Task phone quit! \n") ;
                break;
            }
        }
        /*获取键盘输入，若为'q'，则通知通话任务改变状态*/
        ch = get_char() ;
        if(ch == 'q')
        {
            change_state();
        }
        else if(ch == 'c')//退出进程
        {
             break;
        }
    }
    /*从系统内核中移走消息队列*/
    if((msgctl(qid_ui, IPC_RMID,NULL)) < 0)
    {
        perror("msgctl");
        exit(1);
    }
    return 0;
}