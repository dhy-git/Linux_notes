/*
 Tcp通讯服务器端程序
    
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "strings.h"         
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码errno宏定义 
#include <netinet/in.h>             //sockaddr_in 结构体定义位置，将port 和 addr分开定义

#define MAX_LISTEN_QUE 5
int main(int argc, char *argv[])
{
    int listenfd, sockfd;
    struct sockaddr_in server,client;
    char buf[100];
    int len，timep;
    /*创建linstenfd ipv4字节流套接字*/
    if((listenfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("create socket error");
        return -1;
    }

  /*设置协议簇 IP地址和端口号*/
    bzero(&server,sizeof(server));       //较memset更为安全,头文件strings.h声明
    server_ip.sin_family = AF_INET;                     //设置ipv4协议簇
    server_ip.sin_port = htons(8888);                   //设置服务器端口号
    server.sin_addr.s_addr = btonl(INADDR_ANY);         //绑定主机所有网卡的ip地址

    len = sizeof(struct sockaddr);
    if(bind(listenfd, (struct sockaddr *)&server, len)<0)
    {
        perror("accept error\n");
        return -1;
    }

    listen(listenfd,MAX_LISTEN_QUE);        //监听阻塞

    while(1)        //迭代套接字实现
    {
        sockfd = accept(listenfd, (struct sockaddr *)&client, &len);    
        if(sockfd<0)
        {
            perror("accept error\n");
            return -1;
        }

        sleep(10);                      //通过延时 观察tcp建立连接时对网卡操作过程
        timep = time(NULL);
        snprintf(buf, sizeof(buf), "%s", ctime(&timep));
        write(sockfd, buf, strlen(buf)); 
        printf("send bytes:%d\n",strlen(buf));
        printf("sockfd: %d\n",sockfd);
        printf("IP：0x%x，Port:%d\n", ntohs(client.sin_addr.s_addr),ntohs(client.sin_port));
        close(sockfd);          //不关闭会导致套接字不断累积，造成枯竭
    }
  

    return 0;


}