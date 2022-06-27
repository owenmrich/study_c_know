#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
    int fd1,fd2;
    char buf[1024];
    int ret;
    fd1 = open("./1.txt",ORDONLY);
    if(fd1 < 0)
    {
        printf("open 1.txt err\n");
        return 0;
    }
    fd2 = open("./2.txt", O_WRONLY |  O_CREAT | O_EXCL, 0644);
    if(fd2 < 0)
    {
        printf("open 2.txt err\n");
        return 0;
    }
    ret = read(fd1,buf,sizeof(buf));
    if(ret == -1)
    {
        printf("read 1.txt err\n");
        return 0;
    }
    //strcpy(buf,"hello");
    ret = write(fd2, buf, sizeof(buf));
    if(ret == -1)
    {
        printf("write file err\n");
        return -1;
    }
    ret =  lseek(fd1, 0, SEEK_END);//到文件尾部，相当于获得文件的大小size，ret返回值为头部到指针位置的距离
    printf("1.txt size is %d",ret);
    sleep(1);
    close(fd1);
    close(fd2);

}