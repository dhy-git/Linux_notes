/*
    在线程中安全的使用fork：
        互斥量已被锁住，创建的子进程无法加锁解锁操作，进程阻塞
        >> ps 查看运行中的进程
        >> kill 杀死阻塞进程
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码errno宏定义 


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;          //全局互斥量

void *thread_fun(void *arg)
{
    sleep(1);                                   //子线程休眠1秒，主线程锁住互斥量后创建子进程
    pid_t pid; 
    pid = fork();
    if(pid == 0)    //子线程
    {
        pthread_mutex_lock(&mutex);                  //互斥量已被锁住，因此子线程创建的子进程无法加锁解锁操作，进程阻塞
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
    sleep(2);                           //主线程加锁休眠
    pthread_mutex_unlock(&mutex);
	pthread_join(tid,NULL);				//主线程中等待子线程运行结束
	printf("main thread \n");
	return 0;
}
