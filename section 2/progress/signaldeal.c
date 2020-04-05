/*
程序说明： 父进程循环打印进程运行时间，子进程睡眠10秒，发送10号信号到父进程中，父进程接受到10号信号后调用myfun()，
输出五条语句后返回主函数； 同时子进程发送kill信号睡眠10秒后终止，exit函数发送信号到父进程调用myfunc1，回收子进程资源。
*/

#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#include "signal.h"  //内核信号宏定义头

void myfun(int signum)
{
    int i=0;
    while(i<5)
    {
       printf("recive signum = %d, i=%d\n",signum,i);
       sleep(1);
       i++;
   }
    return;
}

void myfun1(int signum)
{
    printf("recive signum = %d\n",signum);
    wait(NULL);   //回收子进程
    return;
}

int main()
{
    pid_t pid;
    pid = fork();        //再创建子进程
    if(pid >0)                    //父进程部分
    {
        int i=0;
        signal(10,myfun);
        signal(SIGCHLD,myfun1);
        while(1);
        {
            printf("parent process things, i=%d\n",i);
            sleep(1);
            i++;
        }
    }
   if(pid ==0 )                   //子进程部分，是父进程的拷贝
   {
       sleep(10);
       kill(getppid(),10);
       sleep(10);
       exit(0);  //发送kill(getppid(),SIGCHLD)
   }
   return 0;
}