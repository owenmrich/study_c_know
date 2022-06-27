#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) 
{
    int fd1, fd2, fd3;
    int ret;
    char buf[100] = {0};
    int flag;
    /* 第一次打开文件 */
    fd1 = open("1.txt", O_RDWR );//O_APPEND 文件标志 flage
    fd2 = fcntl(fd1, F_DUPFD, 0);
    //复制文件描述符 cmd=F_DUPFD 或 cmd=F_DUPFD_CLOEXEC
    flag = fcntl(fd1, F_GETFL);
    printf("flags: 0x%x\n", flag);
    printf("flag:%d \n",flag);
    ret = fcntl(fd1, F_SETFL, flag | O_APPEND);
    flag = fcntl(fd1, F_GETFL);
    printf("flags: 0x%x\n", flag);
    printf("flag:%d \n",flag);
    //cmd=F_GETFL 可用于获取文件状态标志，cmd=F_SETFL 可用于设置文件状态标志。cmd=F_GETFL 时
    //不需要传入第三个参数，返回值成功表示获取到的文件状态标志；cmd=F_SETFL 时，需要传入第三个参数，
    //此参数表示需要设置的文件状态标志。
    // O_APPEND、O_ASYNC、O_DIRECT、O_NOATIME 以及 O_NONBLOCK 这些标志可以被修改，
    printf("fd1 is %d, fd2 is %d\n",fd1,fd2);
    close(fd1);
    close(fd2);
    return 0;
    
}