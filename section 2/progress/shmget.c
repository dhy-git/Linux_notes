#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
    int shmid;
    char rmcm[30];
    shmid=shmget(IPC_PRIVATE,128,0777);
    if(shmid <0)
    {
         printf("creat share memory failure\n");
         return -1;
    }
    printf("creat share memory success shmid=%d\n",shmid);
    system("ipcs -m");          //程序使用shell命令查看共享内存对象
    sprintf(rmcm,"%s%d","ipcrm -m ",shmid);
    system(rmcm);
    system("ipcs -m");  
    return 0;
}