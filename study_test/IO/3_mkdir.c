#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
int main()
{
    struct dirent *dir;
    DIR *dirp;
    int ret;
    char buf[128]={0};
    ret = mkdir("./testdir",0666);
    if(-1 == ret)
    {
       perror("mkdir err:");
       return 1; 
    }
    dirp = opendir("./");
    if (NULL == dirp) 
    {
        perror("opendir error");
        exit(-1);
    }
    /* 循环读取目录流中的所有目录条目 */
    errno = 0;
    while (NULL != (dir = readdir(dirp)))
    {
        printf("%s %ld\n", dir->d_name, dir->d_ino);
    }
    if (0 != errno) 
    {
        perror("readdir error");     
        closedir(dirp);
        return 0;
    } 
    else
    {
        printf("End of directory!\n");
    }
    rmdir("./testdir");
    closedir(dirp);
    getcwd(buf,sizeof(buf));
    printf("now work dir is %s\n",buf);
    printf("================\n");
    chdir("../");
    getcwd(buf,sizeof(buf));
    printf("now work dir is %s\n",buf);
    return 0;
}