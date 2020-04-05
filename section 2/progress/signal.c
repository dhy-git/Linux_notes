
/*
程序说明： 进程创建后 alarm函数让内核9秒以后发送信号，进程受到信号后跳转myfun打印语句，完成后跳转回main函数继续执行。
*/
#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"  
#include "stdlib.h"
#include "signal.h"  //内核信号宏定义头
void myfun(int signum)
{
    int i;
    i=0;
    while(i<20)
    {
        printf("process  signal signum=%d\n",signum);
        sleep(1);
        i++;
    }
    return;
}
int main(int argc,char* argv[])
{
    int i;
    i=0;
    signal(14,myfun);   //14 == SIGALARM;  9s后进程接收到SIGALARM信号，跳转执行函数myfun，执行完成后返回
    printf("alarm before");
    alarm(9);                 //定时9秒发送SIGALARM
    printf("alarm after \n");
    //signal(14,SIG_IGN) //忽略信号后不会跳转到函数myfun
    //signal(14,SIG_DFL) //初始情况下接收到信号就终止进程
    while(i<20)
    {
        printf("process  things,i=%d\n",i);
        sleep(1);
        i++;
    }
    return 0;
}