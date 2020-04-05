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
  if(pid > 0)        //父进程写
    {
        sendbuf.type=100;     //父进程发送消息类型标识
        while(1)
        {     
          memset(sendbuf.voltage,0,124);          //清空缓存
          printf("please input message:\n");
          fgets(sendbuf.voltage,124,stdin);
          msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);  //写入消息队列 结构体强制类型转换
        }
   }
  if(pid == 0)        //子进程
  {
    while(1)
    {    
      memset(recvbuf.voltage,0,124);
      msgrcv(msgid,(void *)&recvbuf,124,200,0);    ////阻塞方式，读消息队列里的内容
      printf("recv:%s",recvbuf.voltage);
    }
  }
  msgctl(msgid,IPC_RMID,NULL);                    //delete message queue
  system("ipcs -q");
  return 0;
}