#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    struct stat st;
    int ret;
    ret = stat("./1.txt",&st);
    //ret = lstat("./1.txt",&st); stat与lstat区别如果是链接文件是符号文件，不是指向的文件
    //int fd;
    //fd = open("./1.txt",O_RDWE);
    //ret = fstat(fd, &st); 
    if( -1 == ret)
    {
        perror("stat err");
        return 1;
    }
    printf("inode:%d\n",st.st_ino);
    printf("size :%d\n",st.st_size);
    printf("type:");
    switch (st.st_mode & S_IFMT) 
    {
        case S_IFSOCK: printf("socket"); break;
        case S_IFLNK: printf("symbolic link"); break;
        case S_IFREG: printf("regular file"); break;
        case S_IFBLK: printf("block device"); break;
        case S_IFDIR: printf("directory"); break;
        case S_IFCHR: printf("character device"); break;
        case S_IFIFO: printf("FIFO"); break;
    }
    printf("\n");
    /* 判断该文件对其它用户是否具有读权限 */
    if (st.st_mode & S_IROTH)
        printf("Read: Yes\n");
    else
        printf("Read: No\n");
    /* 判断该文件对其它用户是否具有写权限 */
    if (st.st_mode & S_IWOTH)
        printf("Write: Yes\n");
    else
        printf("Write: No\n");
        
    return 0;
}