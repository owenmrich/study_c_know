#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
int main(int argc, char *argv[])
{
    int srcfd, dstfd;
    void *srcaddr;
    void *dstaddr;
    int ret;
    struct stat sbuf;
    /* 打开源文件 */
    srcfd = open("./1.txt", O_RDONLY);
    if (-1 == srcfd) 
    {
        perror("open error");
        exit(-1);
    }
    /* 打开目标文件 */
    dstfd = open("./1_test.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
    if (-1 == dstfd) 
    {
        perror("open error");
        ret = -1;
        goto out1;
    }
    /* 获取源文件的大小 */
    fstat(srcfd, &sbuf);
    /* 设置目标文件的大小 */
    ftruncate(dstfd, sbuf.st_size);
    /* 将源文件映射到内存区域中 */
    srcaddr = mmap(NULL, sbuf.st_size,
    PROT_READ, MAP_SHARED, srcfd, 0);
    if (MAP_FAILED == srcaddr) 
    {
        perror("mmap error");
        ret = -1;
        goto out2;
    }
    /* 将目标文件映射到内存区域中 */
    dstaddr = mmap(NULL, sbuf.st_size,
    PROT_WRITE, MAP_SHARED, dstfd, 0);
    if (MAP_FAILED == dstaddr) 
    {
        perror("mmap error");
        ret = -1;
        goto out3;
    }
    /* 将源文件中的内容复制到目标文件中 */
    memcpy(dstaddr, srcaddr, sbuf.st_size);
    /* 程序退出前清理工作 */
    out4:
    /* 解除目标文件映射 */
    munmap(dstaddr, sbuf.st_size);
    out3:
    /* 解除源文件映射 */
    munmap(srcaddr, sbuf.st_size);
    out2:
    /* 关闭目标文件 */
    close(dstfd);
    out1:
    /* 关闭源文件并退出 */
    close(srcfd);
    exit(ret);
}