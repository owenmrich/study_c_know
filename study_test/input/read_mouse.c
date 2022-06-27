#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <linux/input.h>
 
#define DEV_NAME   "/dev/input/event5"
 
#define DBG_PRINTF printf
//#define DBG_PRINTF(...)
 
struct input_event input_mouse;
 
int main(int argc, char **argv)
{
	int fd,retval;
	fd_set readfds;
	fd = open(DEV_NAME, O_RDONLY);
	if (fd < 0)
	{
		printf("can't open %s\n",DEV_NAME);
		return -1;
	}
	
 
while(1)
{
  	FD_ZERO( &readfds );  
	FD_SET( fd, &readfds );    
	retval = select( fd+1, &readfds, NULL, NULL, NULL);  
	if(retval==0) 
	{  
		printf( "Time out!\n" );  
	}  
	if(FD_ISSET(fd,&readfds)) 
	{  
		read(fd, &input_mouse,sizeof(struct input_event)); 
        printf("%c\n",input_mouse.type);
		switch(input_mouse.type)
		{
            case EV_KEY:
			{/* have key is press */
				switch(input_mouse.code)
				{
					case BTN_LEFT:
					{
						if(input_mouse.value==1)
							DBG_PRINTF("the left is press!\n");
					}
					break;
					case BTN_RIGHT:
					{
						if(input_mouse.value==1)
							DBG_PRINTF("the right is press!\n");	
					}
					break;
					case BTN_MIDDLE:
					{
						if(input_mouse.value==1)
							DBG_PRINTF("the middle is press!\n");
					}
					break;
				
				}
			}
            break;
			case EV_REL://相对位移事件,
			{
				switch(input_mouse.code)
				{
					case REL_X:
					{
						if(input_mouse.value>0)
							DBG_PRINTF("X slip is right!\n");
                        else if(input_mouse.value<0)
                            DBG_PRINTF("X slip is left!\n");
					}
					break;
					case REL_Y:
					{
						if(input_mouse.value<0)
							DBG_PRINTF("Y slip is up!\n");
                        else if(input_mouse.value>0)
                            DBG_PRINTF("Y slip is down!\n");
					}
					break;
				}
			
			}
			break;
		}
	}	
}
close(fd);
return 0;
}
 