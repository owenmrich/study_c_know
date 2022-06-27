#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int ret;
    char buf[128]={0};
    ret = link("./1.txt","./hard_1.txt");//硬链接
    ret = symlink("./1.txt","./soft_1.txt")
    //软链接 第一个参数path不存在就成为悬空链接
    readlink("./soft_1.txt",buf, sizeof(buf));
    printf("read is %s \n",buf);
    return 0;
}