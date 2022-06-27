#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int fd;
    int size;
    char buf[128] = {0};
    FILE *fp = NULL;
    fd = open("./1.txt",O_RDWR);
    fp = fdopen(fd,"r+");
    if(NULL == fp)
    {
        perror("fdopen err");
        close(fd);
        return 0;
    }
    fwrite("owenmrich",1,9,fp);
    if (12 > (size = fread(buf, 1, 9, fp))) 
    {
        if (ferror(fp)) 
        { //使用 ferror 判断是否是发生错误
            printf("fread error\n");
            fclose(fp);
            exit(-1);
        }
    }
    printf("read is %s",buf);
    close(fd);
    fclose(fp);
    return 0;
}