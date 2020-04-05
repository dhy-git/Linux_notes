/*
 Tcp通讯客户端程序
    ./client sever_ip server_port
*/

#include "net.h"


void usage(char *s)
{
    printf("\n%s serv_ip serv_port",s);
    printf("\n\t serv_ip: server ip address");
    printf("\n\t serv_port: server port(>5000) \n\n");
}


int main(int argc, char *argv[])
{
    int fd = -1;
    struct sockaddr_in sin;
    char buf[100];
    int len，timep;

    short port;
    if(argc != 3)
    {
        usage(argv[0]);         //封装函数打印说明信息
        exit(1);
    }
    /*1. 创建套接字*/
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("create socket error");
        return -1;
    }

    port = atoi(argv[2]);       //获得端口号
    if(port <5000)
    {
        usage(argv[0]);
        exit(1);
    }
  /*2. 连接服务器 */
    /* 2.1 填充struct sockaddr_in 结构体变量 */
    bzero(&sin,sizeof(sin));       //较memset更为安全,头文件strings.h声明
    sin.sin_family = AF_INET;                     //设置ipv4协议簇
    sin.sin_port = htons(port);                   //设置服务器端口号
    #if 0
    sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);  
    #else
    if(inet_pton(AF_INET, argv[1], (void *)&sin.sin_addr.s_addr) != 1)
    {
        perror("inet_pton");
        exit(1);
    }
    #endif
    /*2.2 绑定*/
    if( connect(fd, (struct sockaddr *)&sin, sizeof(sin)) < 0 )
    {
        perror("connect");
        exit(1);
    } 

    /*3 读写数据*/
    int ret = -1;
    char buf[BUFSIZE];

    while(1)
    {
        bzero(buf, BUFSIZE);
        if( fgets(buf, BUFSIZE-1, stdin) == NULL)
        {
            continue;
        }
        write(fd, buf, strlen(buf));
        if(! strncasecmp(buf, QUIT_STR, strlen(QUIT_STR)) )
        {
            printf("Client is exiting \n");
            break;
        }
    }
    /* 4. 关闭套接字*/
    close(newfd);
    return 0;
}

