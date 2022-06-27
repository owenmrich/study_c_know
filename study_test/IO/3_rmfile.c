#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int ret;
    link("./1.txt","./2.txt");
    ret = unlink("./2.txt");
    //remove("./2.txt");
    link("./1.txt","./3.txt");
    rename("./3.txt","./rename1.txt")
}