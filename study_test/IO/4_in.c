#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    char buf[128]={"owen"};
    char buf1[10]={"hello"};
    char buf2[8]={"i is 111"};
    strcat(buf,buf1);
    puts(buf);
    strncat(buf,buf2,8);
    puts(buf);
    puts(buf1);
    puts(buf2);

    memset(buf2, 6, sizeof(buf2));
    puts(buf2);
    printf("=======");
    bzero(buf2,3);
    return 0;
}