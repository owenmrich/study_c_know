#include <sys/ioctl.h> 
#include <net/ifh>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/if etherh>
#include <linux/if packet.h>
#include <unistd.h>
#define RECEIVE DATA LENGTH 1518
int main()
{
    //创建监听链路层数据
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock< 0)
    {
        printf("create rawreceiver socket failed\n");
        exit(1);
    }
    //获取本地网卡地址
    struct sockaddr_ll sll;
    memset( &sll, 0, sizeof(sll) );
    sll.sll_family= AF_PACKET;
    //打开系统网卡设备
    struct ifreq ifstruct;
    strcpy(ifstruct.ifr_name, "eth0");
    ioctl(sock, SIOCGIFINDEX, &ifstruct);
    sll.sll_ifindex = ifstruct.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);
    //绑定监听数据的网卡
    if(bind(sock, (struct sockaddr *) &sll, sizef(sll)) ==-1 )
    {
        printf("bind rawreceiver socket failed\n");
        exit(1);
    }
    //设置接收等待的时间
    struct timeval timo;
    fd_set ifds;
    struct sockaddr_11 from;
    socklen_t fromlen;
    int iReceiveRet = 0;
    unsigned char receivebuff[RECEIVE_DATA_LENGTH]= {0};
    //开始监听网络数据
    while(1)
    {
        //清空接收缓冲区
        memset(receivebuff, 0, RECEIVE_DATA_LENGTH);
        //初始化等待时间
        memset(&from, 0, sizeof(from));
        FD_ZERO(&ifds);
        FD_SET(sock, &ifds);
        //设置超时时间，如果有数据可以立即接收。没有数据等待超时
        timo.tv_sec = 0;
        timo.tv_usec = 20000;
        iReceiveRet = select(sock + 1, &ifds, 0, 0, &timo);
        if (iReceiveRet == -1)
        {
            //接收数据异常,继续监听
            continue;
        }
        else if (iReceiveRet == 0)
        {
            //超时，继续监听
            continue;
        }
        else
        {
            //接收到数据
        }
        fromlen = sizeof(from);
        //接收链路层数据
        int n = recvfrom(sock, receivebuff, RECEIVE_DATA_LENGTH, 0, (struct sockaddr *)(&from), &fromlen);
        //如果n小于0表示接收数据失败
        if(n< 0)
        {
            printf("receive data failed\n");
            continue;
        }
        //接收到链路层数据包，可以进行相应的处理
        printf("receive data:");
        for(int i= 0;i< n; i++) 
        {
            print("%02X ", receivebuff[i]);
        }
        printf("\n");
        break;
    }
    close(sock);
}

