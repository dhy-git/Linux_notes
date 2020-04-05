/*
线程分离属性设置：程序运行结果
    >>join thread 1 failed
    >>I'm thread 7fee07469700
    >>I'm thread 7fee06c68700
    >>join thread 2 success
    线程1 设置为可分离，join函数无法等待线程结束，直接返回阻塞失败。
    线程2 非分离状态，主线程join函数等待子线程完成后执行
*/
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

void *thread_fun1(void *arg)
{
    sleep(2);
    pthread_t tid;
    tid = pthread_self();
    printf("I'm thread %0lx\n",tid);          
    return (void *)1;
}

void *thread_fun2(void *arg)
{
    sleep(4);
    pthread_t tid;
    tid = pthread_self();
    printf("I'm thread %0lx\n",tid);          
    return (void *)2;
}

int main()
{
    pthread_t tid1,tid2;
    pthread_attr_t attr;
    int err;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    err = pthread_create(&tid1, &attr, thread_fun1, NULL);     //线程创建，设置结束后分离
    if(err)
    {
        printf("thread1 creat failed\n");
    }

    err = pthread_create(&tid2, NULL, thread_fun2, NULL);   //线程创建，默认非分离属性
    if(err)
    {
        printf("thread2 creat failed\n");
    }

    err = pthread_join(tid1,NULL);
    if(!err)
        printf("join thread 1 success\n");
    else
        printf("join thread 1 failed\n");

    err = pthread_join(tid2,NULL);
    if(!err)
        printf("join thread 2 success\n");
    else
        printf("join thread 2 failed\n");
    return 0;
}