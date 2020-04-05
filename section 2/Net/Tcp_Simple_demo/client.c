/*
 Tcp通讯客户端程序
*/

#include "net.h"

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

  /*2. 连接服务器 */
    /* 2.1 填充struct sockaddr_in 结构体变量 */
    bzero(&sin,sizeof(sin));       //较memset更为安全,头文件strings.h声明
    sin.sin_family = AF_INET;                     //设置ipv4协议簇
    sin.sin_port = htons(SERV_PORT);                   //设置服务器端口号
    #if 0
    sin.sin_addr.s_addr = inet_addr(SERV_IP_ADDR);  
    #else
    if(inet_pton(AF_INET, SERV_IP_ADDR. (void *)&sin.sin_addr.s_addr) != 1)
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

