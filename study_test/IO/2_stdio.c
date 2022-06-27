#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(void) 
{
    FILE *p = NULL;
    FILE *f = NULL;
    int ret;
    char buf[128] = {0};
    char buf1[128] = {0};
    p = fopen("./1.txt","w+");
    f = fopen("./2.txt","w+");
    if(NULL == p)
    {
        perror("fopen err");
        return 1;
    }
    ret = fwrite("hello", 1, 5, p);
    if(ret < 5){
        printf("fwrite err");
        fclose(p);
    }
    ret = fseek(p,0, SEEK_SET);
    if(ret == -1)
    {
        perror("fseek err");
        fclose(p);
        return 0;
    }
    ret = fread(buf, 1, 5, p);//操作可能发生错误
    if(ret < 5)
    {
        if(ferror(p))
        {
            printf("fread err \n");
            fclose(p);
            return 1;
        }
        else
        {
            if(feof(p))
            {
                printf("fread end of file\n");
                fclose(p);
                return 1;
            }
        }
        clearerr(p);
        fclose(p);
    }
    fprintf(f, "hello 2.txt %d\n",100);//写入到文件输出中
    fprintf(stdout, "hello 2.txt %d\n",100);//写入到标准输出
    //dprintf(1,"hello %d",100);//写入到标准输出
    sprintf(buf,"hello owen %d",111);
    snprintf(buf1,128,"hello 111+%d",56454);
    printf("fread:%s",buf);
    printf("%s",buf1);
    fclose(p);
    fclose(f);

    printf("\n");
    int a;
    char b[25];
    char c[25];
    char buff[128];
    sscanf("100 hekk owen","%d %s %s",&a,b,c);
    printf("%d,%s %s\n",a,b,c);
    p = fopen("./1.txt","r+");
    fscanf(p,"%s",buff);
    printf("%s",buff);



    return 0;
    
}