/*
变量一次性初始化：
    通过pthread_once_t once = PTHREAD_ONCE_INIT;
    以及pthread_once(&once, thread_init);函数 实现thread_init初始化函数的一次性调用
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

pthread_once_t once = PTHREAD_ONCE_INIT;
pthread_t tid;
void thread_init()                      //一次性初始化函数，互斥量、读写锁等变量可以通过这个函数实现一次性初始化
{
    printf("I'm in thread %0lx\n",tid);
}

void *thread_fun1(void *arg)
{
    tid = pthread_self();
    printf("once = %d\n",once);                 //检验once初始化为0
    printf("I'm thread %0lx\n",tid);
    pthread_once(&once, thread_init);
    printf("once = %d\n",once);                  //检验once在pthread_once函数中对thread_init一次性调用后，once值修改为2；
    return NULL;
}

void *thread_fun2(void *arg)
{
    sleep(2);                                   //人为让线程1先执行
    tid = pthread_self();
    printf("I'm thread %0lx\n",tid);
    pthread_once(&once, thread_init);           
    return NULL;
}

int main()
{
    pthread_t tid1,tid2;
    int err;
    err = pthread_create(&tid1, NULL, thread_fun1, NULL);
    if(err != 0)
    {
        printf("thread1 creat failed\n");
    }
    err = pthread_create(&tid2, NULL, thread_fun2, NULL);
    if(err != 0)
    {
        printf("thread2 creat failed\n");
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}