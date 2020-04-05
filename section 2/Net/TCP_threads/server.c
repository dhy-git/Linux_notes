/*
 Tcp通讯服务器端程序
*/

#include "net.h"


void cli_data_handle(void * arg);       //服务器响应客户端读写操作 线程声明

int main(int argc, char *argv[])
{
    int fd = -1;
    struct sockaddr_in sin;
    char buf[100];
    int len，timep;
    /*1. 创建套接字*/
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("create socket error");
        return -1;
    }
    
    /*优化4 ： 允许服务器重启后 绑定地址快速重用 */
    int b_reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &b_reuse, sizeof(int));
    
  /*2. 绑定 */
    /* 2.1 填充struct sockaddr_in 结构体变量 */
    bzero(&sin,sizeof(sin));       //较memset更为安全,头文件strings.h声明
    sin.sin_family = AF_INET;                     //设置ipv4协议簇
    sin.sin_port = htons(SERV_PORT);                   //设置服务器端口号
    #if 1
    sin.sin_addr.s_addr = htonl(INADDR_ANY);  //优化：服务器绑定任意IP 
    #else
    if(inet_pton(AF_INET, SERV_IP_ADDR. (void *)&sin.sin_addr.s_addr) != 1)
    {
        perror("inet_pton");
        exit(1);
    }
    #endif
    /*2.2 绑定*/
    if( bind(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0 )
    {
        perror("bind");
        exit(1);
    } 

    /*3  listen() 主动套接字转换为被动套接字*/
    if(listen(fd,MAX_LISTEN_QUE) <0 )  //监听阻塞
    {
        perror("bind");
        exit(1);
    }   
    printf("server starting....Ready!\n");


    /*4 阻塞等待客户端请求*/
/* 并发优化： 多线程/进程处理已经建立好的客户端数据*/
    int newfd = -1;
    /*多线程优化——*/
    pthread_t tid;
    struct sockaddr_in cin;
    socklen_t addrlen = sizeof(cin);
    while(1)
    {/*accept 不断循环阻塞读客户端 */
        if((newfd = accept(fd, (struct sockaddr *)&cin, &addrlen)) < 0)
        {
            perror("accept");
            exit(1);
        }

        char ipv4_addr[16];         //Ipv4 点分形式（字符串）地址存储
        if(!( inet_ntop(AF_INET, (void *)&cin.sin_addr.s_addr, ipv4_addr,sizeof(cin)) ) )
        {
            perror("inet_ntop");
            exit(1);  
        }
        printf("Client(%s : %d) is connected!\n",ipv4_addr, htons(cin.sin_port));
    
        pthread_create(&tid, NULL, (void *)cli_data_handle, (void *)&newfd);
     
    }
    close(fd);
    return 0;
}

void cli_data_handle(void * arg)
{
    int newfd_t = *(int *) arg;
    printf("handle thread : newfd = %d\n",newfd_t);
    /*读写*/
    int ret = -1;
    char buf[BUFSIZE];
    while(1)
    {
        bzero(buf, BUFSIZE);
        do
        {
            ret = read(newfd, buf, BUFSIZE-1);
        }while(ret < 0 && EINTR == erron);
        if(ret < 0)
        {
            perror("read");
            exit(1);
        }
        if(!ret){
            break;
        }
        printf("Recive data : %s\n",buf);
        if(! strncasecmp(buf, QUIT_STR, strlen(QUIT_STR)) )
        {
            printf("Client（fd = %d） is exiting \n",newfd_t);
            break;
        }
    }
    close(newfd_t);
}