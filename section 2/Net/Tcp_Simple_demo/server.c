/*
 Tcp通讯服务器端程序
*/

#include "net.h"

int main(int argc, char *argv[])
{
    int fd = -1;
    struct sockaddr_in sin;
    int len, timep;
    /*1. 创建套接字*/
    if((fd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("create socket error");
        return -1;
    }

  /*2. 绑定 */
    /* 2.1 填充struct sockaddr_in 结构体变量 */
    bzero(&sin,sizeof(sin));       //较memset更为安全,头文件strings.h声明
    sin.sin_family = AF_INET;                     //设置ipv4协议簇
    sin.sin_port = htons(SERV_PORT);                   //设置服务器端口号
    #if 1
    sin.sin_addr.s_addr = htonl(INADDR_ANY);  //可以从不同网卡上获得IP
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
    /*4 阻塞等待客户端请求*/
    int newfd = -1;
    #if 0
    newfd = accept(fd,NULL,NULL);
    if(newfd < 0)
    {
        perror("accept");
        exit(1);
    }
    #else
    struct sockaddr_in cin;
    socklen_t addrlen = sizeof(cin);
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
    printf("Client(%s : %d) is connected!\n",ipv4_addr, ntops(cin.sin_port));
    
    #endif
    /*5 读写*/
    int ret = -1;
    char buf[BUFSIZE];

    while(1)
    {
        bzero(buf, BUFSIZE);
        do
        {
            ret = read(newfd, buf, BUFSIZE-1);
        }while(ret < 0 && EINTR == perror);
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
            printf("Client is exiting \n");
            break;
        }
    }
    close(newfd);

    return 0;


}