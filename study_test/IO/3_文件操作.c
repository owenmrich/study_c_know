#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define file "./1.txt"
int main()
{
    int ret;
    ret = access(file, F_OK);
    if(ret == 0)
    {
        printf("%s: is ok",file);
    }
    ret = access(file, R_OK);
    if (!ret)
        printf("Read permission: Yes\n");
    else
        printf("Read permission: NO\n");
    
    chmod(file,0777);
    if (-1 == ret) 
    {
        perror("chmod error");
        exit(-1);
    }

}