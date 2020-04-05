/*
读写锁的应用：
    多线程对同一共享内存读操作时，可以同时占用读写锁，两个线程都在读到内存数据后，睡眠五秒后继续执行
    如果某一线程使用写模式加锁，则其他线程无法占用读写锁，加锁会被阻塞直到写加锁线程完成并解锁。
    多个线程进行写加锁会出现抢占
*/

#include "stdio.h"
#include "unistd.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"

int num;
pthread_rwlock_t rwlock;        //读写锁

void *thread_fun1(void *arg)
{
    int err;
    pthread_rwlock_wrlock(&rwlock);         //读状态枷锁
    printf("thread1 print num %d\n",num);
    sleep(5);
    printf("thread1 over\n");
    pthread_rwlock_unlock(&rwlock);         //解锁
    return (void *)1;
}

void *thread_fun2(void *arg)
{
    int err;
    pthread_rwlock_rdlock(&rwlock);  
    printf("thread2 print num %d\n",num);
    sleep(5);
    printf("thread2 over\n");
    pthread_rwlock_unlock(&rwlock); 
    return (void *)2;
}

int main()
{
    pthread_t tid1,tid2;
    int err;
    err = pthread_rwlock_init(&rwlock,NULL);        //读写锁初始化
    if(err!= 0)
    {
        printf("creat relock failed\n");
        return 0;
    }
    err = pthread_create(&tid1, NULL, thread_fun1, NULL);
    if(err)
    {
        printf("thread1 creat failed\n");
         return 0;
    }
    err = pthread_create(&tid2, NULL, thread_fun2, NULL);
    if(err)
    {
        printf("thread2 creat failed\n");
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_rwlock_destroy(&rwlock);        //销毁读写锁
    return 0;
}