/*
    多线程操作实例————简单TCP服务器的搭建;
        1. 创造一个套接字：socket() 函数
        2. 绑定IP地址和端口信息到socket，  bind()
        3. 设置允许的最大连接数， listen();
        4. 等待来自客户端的连接请求， 阻塞函数accept()
        5. 收发数据，使用函数recv(), send()/sendto(), 或者read()/write()
        6. 关闭网络连接,close();
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码errno宏定义 
#include <netinet/in.h>             //sockaddr_in 结构体定义位置，将port 和 addr分开定义

#define MAX_LISTEN 100
char buf[100];
int main()
{
    struct sockaddr_in server_ip, remote_ip;
    int server_len, remote_len;

    int err, sd, ad;        //错误码和socket返回文件描述符
    /*创建socket*/
    sd = socket(AF_INET, SOCK_STREAM, 0);           //ipv4
    if(sd == -1)
    {
        printf("create socket failed, errno is %d\n",errno);
        return 0;
    }
    server_ip.sin_family = AF_INET;                     //设置ipv4协议簇
    server_ip.sin_port = htons(5678);                   //设置服务器IP地址
    server_ip.sin_addr.s_addr = htonl(INADDR_ANY);      //使用INADDR_ANY自动读取网卡中的主机地址
    memset(server_ip.sin_zero, 0, 8);
    /*绑定服务器地址和端口到socket*/
    err = bind(sd, (struct sockaddr *)(&server_ip), sizeof(struct sockaddr));       //绑定服务器地址和端口
    if(err == -1)
    {
        printf("bind failure, errno is %d\n",errno);
        close(sd);
        return 0;
    }
    /*设置服务器最大允许连接数 */
    err = listen(sd, MAX_LISTEN);      
    if(err == -1)
    {
        printf("listen failure, errno is %d\n",errno);
        close(sd);
        return 0;
    }

    /*等待客户端连接请求*/
    remote_len = sizeof(struct sockaddr);

    while(1)            //多个客户端——ad  数据交换
    {
        ad = accept(sd,  (struct sockaddr *)(&server_ip), &remote_len);
        if(ad == -1)
        {
            printf("accept error, errno is %d\n",errno);
            close(sd);
            return 0;
        }
        /*客户端与服务器连接成功，则读取数据*/
        read(ad, buf, 100);
        printf("buf is %s\n",buf);

        close(ad);  
    }

    close(sd);
    return 0;
}