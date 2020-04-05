#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct mybuf
{
    int pid;
    char buf[124];
};
void myfun(int signum)
{
    return ;
}
int main()
{
    int shmid;
    int key;
    struct mybuf  *p;
    int pid;
    key=ftok("./a.c",'a');
    if(key < 0)
    {
        printf("creat key failure\n");
        return -1;
    }
    printf("creat key sucess\n");
    shmid=shmget(key,128,IPC_CREAT | 0777);
    if(shmid <0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat share memory sucess shmid=%d\n",shmid);
   
    signal(SIGUSR1,myfun);                           //非租塞接收server发出的进程信号
    p=(struct mybuf *)shmat(shmid,NULL,0);            //共享内存映射到用户空间
    if(p == NULL)
    {
        printf("parent process:shmat function failure\n");
        return -3;
    }
    pid=p->pid;                                    //首次，先从shmem获取server进程pid
    p->pid=getpid();                                //把client的pid覆写入共享内存
    //kill signal
    kill(pid,SIGUSR2);                            //发送进程信号，
 
    //client start read data from share memory
    while(1)
    {
        pause();                //wait server write data to share memory;
        printf("client process receve data from share memory:%s",p->buf);    //read data
        kill(pid,SIGUSR2);                    //server may write share memory
    }
 
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    system("ipcs -m ");
    return 0;
}