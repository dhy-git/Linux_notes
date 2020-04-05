#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main()
{
    int shmid;
    int key;
    char *p;
    key=ftok("./a.c",'b');
    if(key <0 )
    {
        printf("creat key failure\n");
        return -2;
    }
    printf("creat key success key=%X\n",key);
    shmid=shmget(key,128,IPC_CREAT | 0777);
    if(shmid <0)
    {
        printf("creat share memory failure\n");
        return -1;
    }  
    printf("creat share memory success shmid=%d\n",shmid);
    system("ipcs -m");
    p=(char *)shmat(shmid,NULL,0);      //映射到用户空间，并用指针指向该内存地址
    if(p == NULL)
    {
        printf("shmat function failure\n");
        return -3;
    }
    //write share memory
    fgets(p,128,stdin);           //从键盘写入
    //start read share memory
    printf("share memory data:%s",p);   //读共享内存的内容
    //shmdt(p);
    memcpy(p,"abcd",4);    //删除内存映射后，再进行用户层读写操作会出现段错误【segment fault】

    printf("second read share memory data:%s",p);  //不同于管道，再次读内存依然可行.只有在内存删除后内容消除。
    shmctl(shmid,IPC_RMID,NULL);   //实现命令ipcrm -m
    system("ipcs -m");      //删除共享内存，shell查看不存在
    return 0;
}