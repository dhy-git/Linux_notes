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
    int readret;
    struct msgbuf sendbuf,recvbuf;
    msgid=msgget(IPC_PRIVATE,0777);
   if(msgid <0)
    {
        printf("creat message queue failure\n");
        return -1;
    }
    printf("creat message queue  success msgid=%d\n",msgid);
    system("ipcs -q");
    sendbuf.type=100;                     //init sendbuf
    printf("please input message:\n");
    fgets(sendbuf.voltage,124,stdin);
    msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);  //写入消息队列 结构体强制类型转换
    memset(recvbuf.voltage,0,124);
    readret=msgrcv(msgid,(void *)&recvbuf,124,100,0);    ////读消息队列里的内容
    printf("recv:%s",recvbuf.voltage);
    printf("readret=%d\n",readret);                        //读取消息的长度

    //msgrcv(msgid,(void *)&recvbuf,124,100,0);         //再读，出现阻塞
    printf("second read after\n");
    //delete message queue
    msgctl(msgid,IPC_RMID,NULL);
    system("ipcs -q");
    return 0;
}