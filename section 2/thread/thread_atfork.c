/*
    在线程中安全的使用fork：
        int pthread_atfork( void(*prepare)(void), void(*parent)(void), void(*child)(void)); 进行函数句柄注册
        注册三个函数：
            prepare 在fork之前会被调用；
            parent 在fork返回父进程之前调用
            child 在返回子进程之前调用
        在prepare中加锁的互斥量，若果在parent 和 child中解锁，那么fork返回后互斥量为未加锁状态
        多个处理程序注册pthread_atfork，prepare 执行顺序与注册顺序相反，parent 和child则相同

    思考： 线程需要先锁A，再锁B  如何安全的在线程中使用fork创建子进程
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码errno宏定义 


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;          //初始化全局互斥量

void prepare()
{
    pthread_mutex_lock(&mutex);
    printf("I'm prepare function\n");    
}
void parent()
{
    pthread_mutex_unlock(&mutex);
    printf("I'm parent function\n");    
}
void child()
{
    pthread_mutex_unlock(&mutex);
    printf("I'm child function\n");    
}

void *thread_fun(void *arg)
{
    sleep(1);                                   //子线程休眠1秒，主线程锁住互斥量后创建子进程
    pid_t pid;
    pthread_atfork(prepare, parent, child);     //注册处理函数，
    pid = fork();
    if(pid == 0)    //子线程
    {
        pthread_mutex_lock(&mutex);                 //使用pthread_atfork函数，互斥量的锁状态已被释放
        printf("child in thread\n");                
        pthread_mutex_unlock(&mutex);
    }
    if(pid > 0)      //父线程
    {
        pthread_mutex_lock(&mutex);                 //互斥量已被锁住，等待主线程解锁
        printf("parent in thread\n");               //主线程解锁互斥量后执行打印
        pthread_mutex_unlock(&mutex);             
    }
}

int main()
{
	pthread_t tid;
	int err;
	err= pthread_create(&tid, NULL, thread_fun, NULL);
	if(err)
	{
		printf("creat new thread failed\n");
		return 0;
    }
    pthread_mutex_lock(&mutex);
    printf("main thread \n");                         //主线程加锁休眠
    sleep(2);  
    pthread_mutex_unlock(&mutex);
	pthread_join(tid,NULL);				//主线程中等待子线程运行结束
    pthread_mutex_destroy(&mutex);
	return 0;
}
