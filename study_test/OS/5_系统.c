#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/times.h>
#include <string.h>

int main()
{
    time_t t;
    struct tm t1;
    char buf[128]={0};
    char tm_str[128]={0};
    t = time(NULL);//获得日历时间
    printf("日历时间time is %ld\n",t);
    printf("====\n");

    ctime_r(&t,buf);
    printf("打印时间time is %s\n",buf);//日历时间-> 打印时间
    printf("====\n");

    localtime_r(&t,&t1);
    //printf(" 分解时间time is %s\n",t1);//日历时间-> 分解时间
    printf("当前时间: %d 年%d 月%d 日 %d:%d:%d\n",t1.tm_year + 1900, t1.tm_mon, t1.tm_mday,t1.tm_hour, t1.tm_min, t1.tm_sec);
    printf("转换得到的秒数: %ld\n", mktime(&t1));//日历时间 <- 分解时间
    printf("====\n");

    strftime(tm_str, sizeof(tm_str), "%Y-%m-%d %A %H:%M:%S", &t1);//自定义打印时间 
    printf("本地时间: %s\n", tm_str);

    int b = 3;
    while(b)
    {
        printf("+++++++++\n");
        b--;
    }

    struct tms t_buf_start;
    struct tms t_buf_end;
    clock_t t_start;
    clock_t t_end;
    long tck;
    int i, j;
    /* 获取系统的节拍率 */
    tck = sysconf(_SC_CLK_TCK);
    /* 开始时间 */
    t_start = times(&t_buf_start);
    if (-1 == t_start) 
    {
        perror("times error");
        exit(-1);
    }
    /* *****需要进行测试的代码段***** */
    for (i = 0; i < 20000; i++)
    {
        for (j = 0; j < 20000; j++)
        {}
    }
    sleep(1); //休眠挂起
    /* *************end************** */
    /* 结束时间 */
    t_end = times(&t_buf_end);
    if (-1 == t_end) {
    perror("times error");
    exit(-1);
    }
    /* 打印时间 */
    printf("时间总和: %f 秒\n", (t_end - t_start) / (double)tck);
    printf("用户 CPU 时间: %f 秒\n", (t_buf_end.tms_utime - t_buf_start.tms_utime) / (double)tck);
    printf("系统 CPU 时间: %f 秒\n", (t_buf_end.tms_stime - t_buf_start.tms_stime) / (double)tck);
   
    int clocktime;
    clocktime = clock();
    printf("clocktime is %d\n",clocktime);

    int random_number_arr[8];
    int count;
    /* 设置随机数种子 */
    srand(time(NULL));
    /* 生成伪随机数 */
    for (count = 0; count < 8; count++)
        random_number_arr[count] = rand() % 100;
    /* 打印随机数数组 */
    for (count = 0; count < 8; count++) 
    {
        printf("%d", random_number_arr[count]);
        if (count != 8 - 1)
            printf(", ");
    }
    printf("==========\n");

    char *base = NULL;
    /* 申请堆内存 */
    base = (char *)malloc(1024);
    if (NULL == base) {
    printf("malloc error\n");
    exit(-1);
    }
    /* 初始化申请到的堆内存 */
    memset(base, 0x0, 1024);
    /* 使用内存 */
    /* ...... */
    /* 释放内存 */
    free(base);

    return 0;

}