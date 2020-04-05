#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
    int msgid;
    msgid=msgget(IPC_PRIVATE,0777);
    if(msgid <0)
    {
        printf("creat message queue failure\n");
        return -1;
    }
    printf("creat message queue success msgid=%d\n",msgid);
    system("ipcs -q");
    //delete message queue
    msgctl(msgid,IPC_RMID,NULL);
    system("ipcs -q");       //查看已有的消息队列
    return 0;
}