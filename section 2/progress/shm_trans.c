#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
void myfun(int signum)
{
    return ;                //进程处理函数，返回即唤醒进程，终止pause()阻塞，程序进行到下一句
}
int main()
{
    int shmid;
    int key;
    char *p;
    int pid;
    shmid=shmget(IPC_PRIVATE,128,IPC_CREAT | 0777);    //先创建共享内存
    if(shmid <0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat share memory sucess shmid=%d\n",shmid);
    pid=fork();                                        //创建子进程

    if(pid > 0)                                    //父进程
    {
        signal(SIGUSR2,myfun);
        p=(char *)shmat(shmid,NULL,0);             //共享内存映射到父进程中
        if(p == NULL)
        {
            printf("parent process:shmat function failure\n");
            return -3;
        }
        while(1)
        {
            //write share memory
            printf("parent process start write share memory:\n");
            fgets(p,128,stdin);                   //父进程键盘输入到共享内存
            kill(pid,SIGUSR1);                    // 进程信号发送SIGUSR1
            pause();// wait child process read
        }

    }
    if(pid == 0)                                    //child process
    {
        signal(SIGUSR1,myfun);                    //SIGUSR1（默认处理函数为终止进程）
         p=(char *)shmat(shmid,NULL,0);
        if(p == NULL)
        {
            printf("child process shmat function failure\n");
            return -3;
        }
        while(1)
        {
            pause();                            // wait parent process write
            //start read share memory
            printf("share memory data:%s",p);
            kill(getppid(),SIGUSR2);
        }
    }
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    system("ipcs -m ");
    return 0;
}