#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <pthread.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
pthread_t tid = 0;//线程唯一ID号
#define MAX_URL_LEN (200)
#define MAX_PATH_LEN (100)
#define URL_KEY 60000
#define PATH_KEY 60001
typedef struct _DOWNLOAD_url
{
    char url[MAX_URL_LEN];
}__download_url;
typedef struct _DOWNLOAD_path
{
    char save_path[MAX_PATH_LEN];
}__download_path;
int qid_url, qid_path;
char url[2048] = "127.0.0.1";
char domain[64] = {0};
char ip_addr[16] = {0};
int port = 80;
char file_name[256] = {0};
int length = 0;
int mem_size = 4096;//mem_size might be enlarge, so reset it
int buf_len = mem_size;//read 4k each time
int len;
struct _DOWNLOAD_url send_url;
struct _DOWNLOAD_path send_path;
struct _DOWNLOAD_url read_url;
struct _DOWNLOAD_path read_path;
struct resp_header//保持相应头信息
{
    int status_code;//HTTP/1.1 '200' OK
    char content_type[128];//Content-Type: application/gzip
    long content_length;//Content-Length: 11683079
    char file_name[256];
};

struct resp_header resp;//全剧变量以便在多个进程中使用

void parse_url(const char *url, char *domain, int *port, char *file_name)
{
    /*通过url解析出域名, 端口, 以及文件名*/
    int j = 0;
    int start = 0;
    *port = 80;
    char *patterns[] = {"http://", "https://", NULL};

    for (int i = 0; patterns[i]; i++)
        if (strncmp(url, patterns[i], strlen(patterns[i])) == 0)
            start = strlen(patterns[i]);

    //解析域名, 这里处理时域名后面的端口号会保留
    for (int i = start; url[i] != '/' && url[i] != '\0'; i++, j++)
        domain[j] = url[i];
    domain[j] = '\0';

    //解析端口号, 如果没有, 那么设置端口为80
    char *pos = strstr(domain, ":");
    if (pos)
        sscanf(pos, ":%d", port);

    //删除域名端口号

    for (int i = 0; i < (int)strlen(domain); i++)
    {
        if (domain[i] == ':')
        {
            domain[i] = '\0';
            break;
        }
    }

    //获取下载文件名
    j = 0;
    for (int i = start; url[i] != '\0'; i++)
    {
        if (url[i] == '/')
        {
            if (i !=  strlen(url) - 1)
                j = 0;
            continue;
        }
        else
            file_name[j++] = url[i];
    }
    file_name[j] = '\0';
}

struct resp_header get_resp_header(const char *response)
{
    /*获取响应头的信息*/
    struct resp_header resp;

    const char *pos = strstr(response, "HTTP/");
    if (pos)
        sscanf(pos, "%*s %d", &resp.status_code);//返回状态码

    pos = strstr(response, "Content-Type:");//返回内容类型
    if (pos)
        sscanf(pos, "%*s %s", resp.content_type);

    pos = strstr(response, "Content-Length:");//内容的长度(字节)
    if (pos)
        sscanf(pos, "%*s %ld", &resp.content_length);

    return resp;
}

void get_ip_addr(char *domain, char *ip_addr)
{
    /*通过域名得到相应的ip地址*/
    struct hostent *host = gethostbyname(domain);
    if (!host)
    {
        ip_addr = NULL;
        return;
    }

    for (int i = 0; host->h_addr_list[i]; i++)
    {
        strcpy(ip_addr, inet_ntoa( * (struct in_addr*) host->h_addr_list[i]));
        break;
    }
}


void progressBar(long cur_size, long total_size)
{
    /*用于显示下载进度条*/
    float percent = (float) cur_size / total_size;
    const int numTotal = 50;
    int numShow = (int)(numTotal * percent);

    if (numShow == 0)
        numShow = 1;

    if (numShow > numTotal)
        numShow = numTotal;

    char sign[51] = {0};
    memset(sign, '=', numTotal);

    printf("\r%.5f%%\t[%-*.*s] %.5f/%.5fMB", percent * 100, numTotal, numShow, sign, cur_size / 1024.0 / 1024.0, total_size / 1024.0 / 1024.0);
    fflush(stdout);

    if (numShow == numTotal)
        printf("\n");
}

void * download(void* arg)
{
    memset(&read_path,0,sizeof(read_path));
    memset(&read_url,0,sizeof(read_url));

    if(msgrcv(qid_url,&read_url,MAX_URL_LEN,0,IPC_NOWAIT) >= 0)
    {
        printf("New download task:\n");
        printf("Downloading... url=%s\n",read_url.url);     
        sleep(1);
    }
    


    strcpy(url, read_url.url);

    puts("1: Parsing url...");
    parse_url(url, domain, &port, file_name);

    puts("2: Get ip address...");
    get_ip_addr(domain, ip_addr);
    if (strlen(ip_addr) == 0)
    {
        printf("can not get ip address\n");
        return 0;
    }

    puts("\n>>>>Detail<<<<");
    printf("URL: %s\n", url);
    printf("DOMAIN: %s\n", domain);
    printf("IP: %s\n", ip_addr);
    printf("PORT: %d\n", port);
    printf("FILENAME: %s\n\n", file_name);
    //设置http请求头信息
    char header[2048] = {0};
    sprintf(header, \
            "GET %s HTTP/1.1\r\n"\
            "Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
            "User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"\
            "Host:%s\r\n"\
            "Connection:close\r\n"\
            "\r\n"\
        ,url, domain);

    //printf("%s\n%d", header, (int) strlen(header));

    //创建套接字
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0)
    {
        printf("invalid socket descriptor: %d\n", client_socket);
        exit(-1);
    }

    //创建地址结构体
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip_addr);
    addr.sin_port = htons(port);

    //连接服务器
    puts("3: Connect server...");
    int res = connect(client_socket, (struct sockaddr *) &addr, sizeof(addr));
    if (res == -1)
    {
        printf("connect failed, return: %d\n", res);
        exit(-1);
    }

    puts("4: Send request...");//向服务器发送下载请求
    write(client_socket, header, strlen(header));
    int mem_size = 4096;
    int length = 0;
    int len;
    char *buf = (char *) malloc(mem_size * sizeof(char));
    char *response = (char *) malloc(mem_size * sizeof(char));
    //每次单个字符读取响应头信息, 仅仅读取的是响应部分的头部, 后面单独开线程下载
    while ((len = read(client_socket, buf, 1)) != 0)
    {
        if (length + len > mem_size)
        {
            //动态内存申请, 因为无法确定响应头内容长度
            mem_size *= 2;
            char * temp = (char *) realloc(response, sizeof(char) * mem_size);
            if (temp == NULL)
            {
                printf("realloc failed\n");
                exit(-1);
            }
            response = temp;
        }
        buf[len] = '\0';
        strcat(response, buf);
        //找到响应头的头部信息, 两个"\n\r"为分割点
        int flag = 0;
        for (int i = strlen(response) - 1; response[i] == '\n' || response[i] == '\r'; i--, flag++);
        if (flag == 4)
            break;

        length += len;
    }

    //printf("\n>>>>Response header:<<<<\n%s", response);

    resp = get_resp_header(response);
    strcpy(resp.file_name, file_name);

    printf("5: Start thread to download...\n");
  

    //创建文件描述符
    int fd = open(resp.file_name, O_CREAT | O_WRONLY, S_IRWXG | S_IRWXO | S_IRWXU);
    if (fd < 0)
    {
        printf("Create file failed\n");
        exit(0);
    }
    length = 0;
    char *buf1 = (char *) malloc(mem_size * sizeof(char));
    printf("length is %d,resp length is %d",length,resp.content_length);
    //从套接字中读取文件流
    while ((len = read(client_socket, buf1, buf_len)) != 0 && length < resp.content_length)
    {
        printf("*");
        write(fd, buf1, len);
        length += len;
        progressBar(length, resp.content_length);
    }

    if (length == resp.content_length)
        printf("Download successful ^_^\n\n");
    if(msgrcv(qid_path,&read_path,MAX_PATH_LEN,0,IPC_NOWAIT) >= 0)
    {
        printf("Finish! save_path=%s\n\n",read_path.save_path);
        sleep(1);
    }
}

int task_add(struct _DOWNLOAD_url url,struct _DOWNLOAD_path path)
{
    strncpy(send_url.url,url.url,MAX_URL_LEN);
    strncpy(send_path.save_path,path.save_path,MAX_PATH_LEN);
    msgsnd(qid_url,&send_url,MAX_URL_LEN,0);
    msgsnd(qid_path,&send_path,MAX_PATH_LEN,0);
}
int init_service(void)
{
    qid_url = msgget(URL_KEY,0666 | IPC_CREAT);
    qid_path = msgget(PATH_KEY,0666 | IPC_CREAT);
    pthread_create(&tid, NULL, download, NULL); //创建下载线程
    return tid;
}
int deinit_service()
{
    int ret = -1;
    ret = pthread_cancel(tid);//发送终止信号给tid线程:
    if (0 == ret)
    {
        pthread_join(tid, NULL);
    }//等待tid线程退出: 
    return ret;
}
int main()
{


    char url_[1024];
    char path_[1024];
    strcpy(url_,"http://img.ivsky.com/img/tupian/pre/201312/04/nelumbo_nucifera-009.jpg");
    strcpy(path_,"/sdcard/video");
    strncpy(send_url.url,url_,MAX_URL_LEN);
    strncpy(send_path.save_path,path_,MAX_PATH_LEN);
    init_service();
    task_add(send_url,send_path);
    sleep(5);
    return 0;
}