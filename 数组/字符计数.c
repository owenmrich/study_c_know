#include<stdio.h>
#include<stdlib.h>
int main()
{
    int count,i;
    int flag = 0;
    char str[128];
    gets(str);
    for(i=0; str[i] != '\0';i++)
    {
        if(str[i] == ' ')
            flag = 0;
        else 
            if(flag ==0 )
            {
                count++;
                flag = 1;
            }
    }
    printf("count is %d",count);
}