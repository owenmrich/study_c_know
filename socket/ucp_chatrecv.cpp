#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc,char **argv)
{
	if(argc < 3)
	{
		perror("param must >= 3");
		return -1;
	}

	int udp_socket = socket(AF_INET,SOCK_DGRAM,0);
	if(udp_socket < 0)
	{
		perror("socket error");
		return -1;
	}

	struct sockaddr_in addr;
    struct sockaddr_in sendaddr;
    memset((void *)&addr, 0, sizeof(addr));
    memset((void *)&sendaddr, 0, sizeof(sendaddr)); 
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[2]));
	addr.sin_addr.s_addr = inet_addr(argv[1]);

	int res = bind(udp_socket,(struct sockaddr *)&addr,sizeof(struct sockaddr));
	printf("bind res = %d\n",res);

	char read_buf[128] = {0};
	char write_buf[128] = {0};
	int size = sizeof(struct sockaddr);

	while(1)
	{
		bzero(read_buf,sizeof(read_buf));
		bzero(write_buf,sizeof(write_buf));
		recvfrom(udp_socket,read_buf,sizeof(read_buf) - 1,0,(struct sockaddr *)&sendaddr,(socklen_t *)&size);
		if(strcmp(read_buf,"quit\n") == 0)
		{
		   printf("send quit the communication!\n");
		   break;
		}
		char ipbuf[16] = {0};
		inet_ntop(AF_INET,&sendaddr.sin_addr.s_addr,ipbuf,sizeof(ipbuf));
		printf("send:%s",read_buf);
		printf("send addr: ip = %s,port = %d\n",ipbuf,ntohs(sendaddr.sin_port));
		printf("recv:");
		fgets(write_buf,sizeof(write_buf),stdin);
		sendto(udp_socket,write_buf,strlen(write_buf),0,(struct sockaddr *)&sendaddr,sizeof(struct sockaddr));
		if(strcmp(write_buf,"quit\n") == 0)
		{
		   printf("you quit the communication!\n");
		   break;
		}
		
	}
	close(udp_socket);
}
