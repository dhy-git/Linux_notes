/*
无亲缘关系进程间使用消息队列进行双向通信:
得益于消息队列每次读完后就被清除，且消息队列的读取可设置为阻塞方式
因此可以分别对server/client进程创建父子进程，仅设置不同进程的消息队列type不同，就可以实现使用同一个消息队列进行双向同时收发
*/

#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct msgbuf
{
    long type;
    char voltage[124];
    char ID[4];
};
int main()
{
    int msgid;
    int key;
    int pid;
    struct msgbuf sendbuf,recvbuf;
    key=ftok("./b.c",'a');                          //创建key
    if(key<0)
    {
        printf("creat key failure\n");
        return -2;
    }
    msgid=msgget(key,IPC_CREAT|0777);               //创建key标识的消息队列
    if(msgid <0)
    {
        printf("creat message queue failure\n");
        return -1;
    }
    printf("creat message queue success msgid=%d\n",msgid);
    system("ipcs -q");
    pid= fork();                                    //创建进程
    if(pid == 0)        //子进程写
    {
        sendbuf.type=200;
        while(1)
        {     
            memset(sendbuf.voltage,0,124);          //清空缓存
            printf("please input message:\n");
            fgets(sendbuf.voltage,124,stdin);
            msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);  //写入消息队列 结构体强制类型转换
        }
   }
    if(pid > 0)        //子进程
    {
        while(1)
        {    
            memset(recvbuf.voltage,0,124);
            msgrcv(msgid,(void *)&recvbuf,124,100,0);    ////阻塞方式，读消息队列里的内容
            printf("recv:%s",recvbuf.voltage);
        }
    }
    msgctl(msgid,IPC_RMID,NULL);                    //delete message queue
    system("ipcs -q");
    return 0;
}