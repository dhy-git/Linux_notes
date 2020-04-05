#ifndef __DHY_NET_H__
#define __DHY_NET_H__

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "strings.h"         
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码 宏定义 
#include <netinet/in.h>             //sockaddr_in 结构体定义位置，将port 和 addr分开定义
#include <netinet/ip.h>             //sockaddr_in 结构体定义位置，将port 和 addr分开定义
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>

#define SERV_PORT 5001

#define SERV_IP_ADDR "192.168.134.128"
#define MAX_LISTEN_QUE 5
#define BUFSIZE 100
#define QUIT_STR "quit"

#endif