/*动态分配内存*/
#define MAX_LEN 8* 1024*102411最大长度
void test(void)
{
    char *p = (char *)malloc(MAX_LEN);//采用动态分配
}
free(p); //malloc 与 free 一起出现

/*消息队列*/
/*msgget msgrcv msgsnd msgctl */
/*https://blog.csdn.net/guoping16/article/details/6584024*/
msgget()
头文件: #include <sys/types.h> #include<sys/ipc.h> #include <sys/msg.h>
说明: 得到消息队列标识符或创建一个消息队列对象并返回消息队列标识符
int msgget(key_t,int msgflg)
qid_phone=msgget(MSG_KEY_PHONE,0666|IPC_CREAT)
/*
IPC_CREAT：当msgflg&IPC_CREAT为真时，如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列，返回此消息队列的标识符
IPC_CREAT|IPC_EXCL：如果内核中不存在键值与key相等的消息队列，则新建一个消息队列；如果存在这样的消息队列则报错

函数返回值：成功 返回队列标识符 出错 -1
*/
msgctl()
说明: 获取和设置消息队列的属性
int msgctl(int msqid, int cmd, struct msqid_ds *buf)
msgctl(qid_phone,IPC_RMID,NULL)/*移除消息队列*/
/*函数返回值：成功 0 出错 -1*/
msgsnd()
说明: 将msgp消息写入到标识符为msqid的消息队列
int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg)
/*
const void *msgp 发送给队列的消息
msgflg == 0 / IPC_NOWAIT / IPC_NOERROR
0：当消息队列满时，msgsnd将会阻塞，直到消息能写进消息队列
IPC_NOWAIT：当消息队列已满的时候，msgsnd函数不等待立即返回
IPC_NOERROR：若发送的消息大于size字节，则把该消息截断，截断部分将被丢弃，且不通知发送进程。

函数返回值：成功 0 出错 -1
*/
msgrcv()
说明:从标识符为msqid的消息队列读取消息并存于msgp中,读取后把此消息从消息队列中删除
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);
/*
msgp:存放消息的结构体，结构体类型要与msgsnd函数发送的类型相同
msgflg:
0: 阻塞式接收消息.没有该类型的消息msgrcv函数一直阻塞等待
IPC_NOWAIT:如果没有返回条件的消息调用立即返回,此时错误码为ENOMSG
IPC_EXCEPT:与msgtype配合使用返回队列中第一个类型不为msgtype的消息
IPC_NOERROR:如果队列中满足条件的消息内容大于所请求的size字节,则把该消息截断，截断部分将被丢弃

函数返回值：成功 读取到的消息数据长度 出错 -1
*/

/*信号sig*/
int get_phone_pid() 
{
    int pid = -1;
    FILE *fp = NULL;
    char buf[12] = {0};
    //打开管道，执行shell命令查找进程名为task_phone_sig的pid
    fp = popen("ps -e | grep \'task_phone_sig\' | awk \'{print $1}\'","r") ;
    fgets(buf,sizeof(buf), fp) ;
    if(strlen(buf) > 0)
    {
        pid = atoi (buf) ;//转换为长整型
    }
    return pid; 
}

/*有名管道*/
    //所有进程都可访问，一般用于单向传输，否则消息容易混乱
    #define FIFO "/home/study/work/work1/1.txt" //有名管道标识符
    /*步骤1:创建有名管道*/
    if(access(FIFO, F_OK) != 0)
    {
        if(mkfifo(FIFO,0666) < 0)
        {
            perror("cannot create fifo! ");
            exit(1) ;
        }
    }
    /*步骤2:打开有名管道，并设置非阻塞标志*/
    fd = open(FIFO, O_RDONLY | O_NONBLOCK,0)
    /*步骤3:从管道中读取消息字符串*/
    read(fd, buf, sizeof(buf)
    write(fd2, writebuf, sizeof(writebuf));
    /*步骤4:关闭有名管道*/
    close(fd2);