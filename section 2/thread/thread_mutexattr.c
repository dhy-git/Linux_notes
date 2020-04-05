/*
    线程同步属性之：互斥量属性的设置  pthread_mutexattr_t attr
    互斥锁存入共享内存，同样可以作为进程同步变量使用 
*/
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "limits.h"
#include "sys/mman.h"
#include "sys/types.h"
#include "sys/shm.h"

int main()
{
    char *shm = "myshm";        //共享内存buf存储区
    char *shm1 = "myshm1";      //共享内存 进程同步——互斥量存放区
    int shm_id, shm_id1;
    char *buf;
    pid_t pid;
    int key,key1;
    pthread_mutex_t *mutex;
    pthread_mutexattr_t mutexattr;
    key=ftok("./a.c",'a');                        //创建共享内存buf的指定key
    key1=ftok("./b.c",'b');                        //创建共享内存互斥量的指定key


    //打开共享内存，，设置进程同步互斥量
    shm_id1 = shmget(key1,128,IPC_CREAT | 0777);
    //调整共享内存大小
    ftruncate(shm_id1, 100);
    //互斥量映射到共享内存shm1，MAP_SHARED属性表明 对共享内存的任何修改都会影响其他进程
    mutex = (pthread_mutex_t *) shmat(shm_id1, NULL, 0);
    pthread_mutexattr_init(&mutexattr);
    #ifdef _POSIX_THREAD_PROCESS_SHARED
        pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_SHARED);
    #endif
    pthread_mutex_init(mutex,&mutexattr);


    //打开共享内存，buf映射
    shm_id = shmget(key, 128, IPC_CREAT | 0777);
    buf = (char *) shmat(shm_id, NULL, 0);

    pid = fork();
    if(pid == 0);
    {
        //休眠，父进程先运行
        sleep(1);
        printf("this is child progress\n");

        pthread_mutex_lock(mutex);          //使用互斥量 加锁同步
        //共享内存修改为hello
        memcpy(buf, "hello", 6);
        printf("child buf is: %s\n",buf);
        pthread_mutex_unlock(mutex);
    }
    if(pid > 0)
    {
        printf("I'm parent progress\n");
        
        pthread_mutex_lock(mutex);
        //修改共享内存到内容，
        memcpy(buf, "world", 6);
        sleep(3);
        printf("parent buf is: %s\n",buf);
        pthread_mutex_unlock(mutex);
    }

    pthread_mutexattr_destroy(&mutexattr);
    pthread_mutex_destroy(mutex);

    //解除映射
    shmdt(buf);                        //断开映射
    shmdt(shm1);
    shmctl(shm_id,IPC_RMID,NULL);        //删除共享内存
    shmctl(shm_id1,IPC_RMID,NULL);        //删除共享内存



}