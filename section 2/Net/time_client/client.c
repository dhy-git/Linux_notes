/*
    初步介绍 ：
        客户端从服务器127.0.0.1读取时间
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


int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in servaddr;
    char buf[100];

    /*创建socket ipv4字节流套接字*/
    if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket error");
        return -1;
    }
    /*设置协议簇 IP地址和端口号*/
    bzero(&servaddr,sizeof(servaddr));       //较memset更为安全,头文件strings.h声明
    server_ip.sin_family = AF_INET;                     //设置ipv4协议簇
    server_ip.sin_addr.s_addr = inet_addr("127.0.0.1");    //使用INADDR_ANY自动读取网卡中的服务器地址
    server_ip.sin_port = htons(8888);                   //设置服务器端口号

    /*客户端与服务器建立连接*/
    if(connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("socket error");
        return 0;
    }
    bytes = read(sockfd, buf, 100);
    if(bytes < 0 )
    {
        printf("Error, read failed\n");
        return -1;
    }
    if(bytes == 0 )
    {
        printf("Server close connection \n");
        return -1;
    }
    printf("Read bytes %d\n",bytes);
    printf("Time : %s\n", buf);

    close(sockfd);
    return 0;
}