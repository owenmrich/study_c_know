//ip 电脑的地址
//端口 计算机上程序绑定的编号
//协议 socket通讯有tcp udp两种。udp:只负责发送不保证接收,tcp:不仅发送还要保证对方收到

struct sockaddr_in hostaddr;
hostaddr.sin_family = AF_INET;
hostaddr.sin_port = htons(LISTEN_PORT);
hostaddr.sin_addr.s_addr = htonl(INADDR_ANY);
sockaddr_in是socket通讯协议中常用的通讯地址。这个地址结构的定义如下:
struct sockaddr_in{
    sa_family_t sin_family; /* address family: AF INET */
    in_port_t sin_port; /* port in network byte order */
    struct in_addr sin_addr; /*internet address*/
};
struct in_addr{
    uint32_t s_addr; /*address in network byte order*/
}

int socket(int domain, int type, int protoco);
socket函数用于创建一个socket,类似于普通文件的打开操作。创建socket的时候.也可以指定不同的参数创建不同的socket描述符,
socket 函数的三个参数分别为:
domain:即协议域,又称为协议族(amily),比较常用的是AF_INET, AF_INET 决定了要用ipv4地址(32位的)与端口号(16位的)的组合。
type:指定socket类型。常用的socket类型有,SOCK_STREAM (TCP通讯)、SOCK_DGRAM (UDP通讯)、SOCK_RAW (链路层数据通讯)。
protoco:就是指定协议。常用的协议有,IPPROTO_TCP (TCP通讯协议)。IPPTOTO_UDP (UDP通讯协议)。
/*例:listen_sock = socket(AF_INET, SOCK_STREAM, 0);*/

bind()函数把-个地址族中的特 定地址赋给socket,函数的三个参数分别为:
sockfd:即socket描述字,它是通过 socket()函数创建了,唯以标识一个socket. bind()函数就是将给这个描述字绑定一一个名字。
addr:个 const struct sockaddr*指针,指向要绑定给sockfd的协议地址。
通常服务器在启动的时候都会绑定一个众所周知的地址 (如ip地址+端口号), 用于提供服务, 客户就可以通过它来接连服务器:而客
户端就不用指定,有系统自动分配个端口号 和自身的ip地址组合。这就是为什么通常服务 器端在listen之前会调用 bind(),而客户端就不会
调用,而是在 connect()时由系统随机生成一个。
/*例： bind(listen_sock, (struct sockaddr*)&hostaddr, sizeof(hostaddr))*/

服务器端调用 listen()来监听这个socket,如果客户端这时调用 connect()发出连接请求,服务器端就会接收到这个请求。listen函数的第
一个参数即为要监听的socket描述字,第二个参数为相应socket可以排队的最大连接个数。socket()函数创建的socket默认是个主动
类型的, listen() 函数将socket变为被动类型的,等待客户的连接请求。
/*例: listen(listen_sock, MAX_LISTEN_NUM)*/

TCP服务器端依次调用 socket()、bind()  listen()之后, 就会监听指定的socket地址了。TCP客户端依次调用 socket() connect()之
后就想TCP服务器发送了一个连接请求。TCP服务器监听到这个请求之后,就会调用 accept()函数取接收请求,这样连接就建立好了。
之后就可以开始网络I/O操作了,即类同于普通文件的读写I/O操作。
accept函数的第一个参数为服务器的socket描述字,第二个参数为指向struct sockaddr *的指针,用于返回客户端的协议地址,第三
个参数为协议地址的长度。如果accpet成功,那么其返回值是由内核自动生成的一个全新的描述字,代表与返回客户的TCP连接。
注意: accept 的第一个参数为服务器的socket描述字,是服务器开始调用socket()函数生成的,称为监听socket描述字:而accept
函数返回的是已连接的socket描述字。一个服务器通常通常仅仅只创建个一监听socket描述字,它在该服务器的生命周期内一直存在。
内核为每个由服务器进程接受的客户连接创建了一个已连接socket描述字,当服务器完成了对某个客户的服务,相应的已连接socket关闭
描述字就被关闭
/*例: app_sock = accept(listen_sock, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen)*/

客户端这时调用 connect()发出连接请求，服务器端就会接收到这个请求。
connect函数的第一个参数即为客户端的socket描述字,第二参数为服务器的socket地址,第三个参数为socket
地址的长度。客户端通过调用connect函数来建立与TCP服务器的连接。
/*connect(sock_fd, (struct sockaddr *)&ser_addr, sizeof(ser_addr)*/
