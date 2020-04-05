#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main()
{
    int shmid;
    key_t key;

    key = ftok("./a",1);  //创建文件存储key
    if(key <0 )
    {
        printf("creat key failure\n");
        return -2;
    }
    printf("creat key success key=%d\n",key);
    shmid=shmget(key,128,IPC_CREAT|0777);
    if(shmid <0)
    {
        printf("creat share memory failure\n");
        return -1;
    }
    printf("creat share memory success shmid=%d\n",shmid);
    system("ipcs -m");          //程序使用shell命令查看共享内存对象
    return 0;
}