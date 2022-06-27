#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/msg.h> 
#include<sys/ipc.h>
#include<sys/types.h>
//下一步时间间隔
#define TIME_NEXT 50

//定义消息队列标识
#define MSG_KEY_UI 60001
#define MSG_KEY_PHONE 60002

//定义消息结构体
#define MSG_DATA_LEN 128
struct message{
    long msg_type;
    long msg_data[MSG_DATA_LEN];
    
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

//定义通话状态
enum TASK_PHONE_STATE
{
    TASK_PHONE_STATE_NONE = 0,
    TASK_PHONE_STATE_RING,
    TASK_PHONE_STATE_TALK,
    TASK_PHONE_STATE_HANGUP,
};

int phone_state = TASK_PHONE_STATE_NONE;

//设置通话状态
void set_state(int state)
{
    phone_state = state;
}
//获取通话状态
int get_state(void)
{
    return phone_state;
}

int main(void)
{
    int qid_ui = 0, qid_phone = 0;
    int len = 0;
    int time = 0;
    struct message msg;
    /*创建消息队列*/
    if((qid_phone=msgget(MSG_KEY_PHONE,0666|IPC_CREAT)) == -1)
    {
        perror("msgget");
        exit(1);
    }//0666是赋予所有用户读写权限
    while(1)
    {
        /*读取消息队列*/
        memset(&msg, 0, sizeof(msg));
        if(msgrcv(qid_phone,&msg,MSG_DATA_LEN,0,IPC_NOWAIT) >= 0)
        {
            if(msg.msg_type == MSG_TYPE_UI_QUIT)
            {
                printf("task ui hangup\n");
                set_state(TASK_PHONE_STATE_HANGUP);
            }
        }
        /*模拟与其他用户处理通讯协议，每5s进入下一状态*/
        time++;
        if(time >= TIME_NEXT)
        {
            time = 0;
            if(get_state() == TASK_PHONE_STATE_RING)
            {
                set_state(TASK_PHONE_STATE_TALK);
            }
            else if(get_state() == TASK_PHONE_STATE_TALK)
            {
                set_state(TASK_PHONE_STATE_HANGUP);
            }
            else
            {
                set_state(TASK_PHONE_STATE_RING);
            }
            printf("current state is %d\n",get_state());
        }
        /*若当前通话状态为挂断，则退出任务，并发送信息给ui*/
        if(get_state() == TASK_PHONE_STATE_HANGUP)
        {
            if(qid_ui=msgget(MSG_KEY_PHONE, IPC_EXCL) > 0)
            {
                printf("send quit msg\n");
                memset(&msg, 0, sizeof(msg));
                msg.msg_type = MSG_TYPE_UI_QUIT;
                msgsnd(qid_ui,&msg,MSG_DATA_LEN,0);
            }
            break;
        }
        usleep(100*1000);
    }
    /*从系统内核中移走消息队列*/
    if((msgctl(qid_phone,IPC_RMID,NULL)) < 0)
    {
        perror("msgctl");
        exit(1);
    }
    return 0;

}