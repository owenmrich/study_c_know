#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
static char gpio_path[100];
static int gpio_config(const char *attr, const char *val) 
{
    char file_path[100];
    int len;
    int fd;
    sprintf(file_path, "%s/%s", gpio_path, attr);
    if (0 > (fd = open(file_path, O_WRONLY))) 
    {
        perror("open error");
        return fd;
    }
    len = strlen(val);
    if (len != write(fd, val, len)) 
    {
        perror("write error");
        close(fd);
        return -1;
    }
    close(fd); //关闭文件
    return 0; 
}
int main(int argc, char *argv[])
{
    char file_path[100];
    char val;
    int fd;
    /* 校验传参 */
    if (2 != argc) 
    {
        fprintf(stderr, "usage: %s <gpio>\n", argv[0]);
        exit(-1);
    }
    /* 判断指定编号的 GPIO 是否导出 */
    sprintf(gpio_path, "/sys/class/gpio/gpio%s", argv[1]);
    if (access(gpio_path, F_OK)) 
    {//如果目录不存在 则需要导出
        int len;
        if (0 > (fd = open("/sys/class/gpio/export", O_WRONLY))) 
        {
            perror("open error");
            exit(-1);
        }
        len = strlen(argv[1]);
        if (len != write(fd, argv[1], len)) 
        {//导出 gpio
            perror("write error");
            close(fd);
            exit(-1);
        }
        close(fd); //关闭文件
    }
    /* 配置为输入模式 */
    if (gpio_config("direction", "in"))
        exit(-1);
    /* 极性设置 */
    if (gpio_config("active_low", "0"))
        exit(-1);
    /* 配置为非中断方式 */
    if (gpio_config("edge", "none"))
        exit(-1);
    /* 读取 GPIO 电平状态 */
    sprintf(file_path, "%s/%s", gpio_path, "value");
    if (0 > (fd = open(file_path, O_RDONLY))) 
    {
        perror("open error");
        exit(-1);
    }
    if (0 > read(fd, &val, 1)) 
    {
        perror("read error");
        close(fd);
        exit(-1);
    }
    printf("value: %c\n", val);
    /* 退出程序 */
    close(fd);
    exit(0);
}