/*
程序 shm_usr1、shm_usr2 创建共享内存实现 usr1到 usr2的信息发送 
运行时需要先启动usr1的生成程序，确保进程号的正确发送
*/

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
    key=ftok("./a.c",'a');                        //创建共享内存的指定key
    if(key < 0)
    {
        printf("creat key failure\n");
        return -1;
    }
    printf("creat key success\n");
    shmid=shmget(key,128,IPC_CREAT | 0777);            //使用指定key创建共享内存
    if(shmid <0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat share memory success shmid=%d\n",shmid);
   
    signal(SIGUSR2,myfun);                            //server非阻塞信号接收处理函数
    p=(struct mybuf *)shmat(shmid,NULL,0);            //创建用户层内存映射->结构体mybuf
    if(p == NULL)
    {
        printf("parent process:shmat function failure\n");
        return -3;
    }
    //get client pid
    p->pid=getpid();                        //第一次建立，server进程pid号写入shmem
    pause();//wait client read server pid;  //休眠等待client读取
   
    pid=p->pid;                            //获得client进程pid，
    //write
     while(1)
    {
        printf("parent process start write share memory:\n");    //write share memory
        fgets(p->buf,128,stdin);
        kill(pid,SIGUSR1);                    // 读取完毕，发送进程信号SIGUSR1到client进程
        pause();                                // wait client process read
    }
 
    shmdt(p);                        //断开映射
    shmctl(shmid,IPC_RMID,NULL);        //删除共享内存
    system("ipcs -m ");
    return 0;
}
