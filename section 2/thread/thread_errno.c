/*
	线程私有数据————errno 错误提示量的线程私有属性， 
        test.c文件存在，open函数返回错误码errno=0;
        1.c不存在，返回errno=2;   且线程间默认为私有数据
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"  
#include "unistd.h"
#include "fcntl.h"                  //文件IO操作头文件
#include "errno.h"                  //错误码errno宏定义 

void *thread_fun1(void *arg)
{
    printf("thread 1 start\n");
    open("1.c",O_RDWR);
    sleep(2);                     
    printf("thread 1 errno is %d\n",errno);
    return (void *)1;
}

void *thread_fun2(void *arg)
{
    sleep(1);
    printf("thread 2 start\n");
    open("test.c",O_RDWR);
    printf("thread 2 errno is %d\n",errno);
    return (void *)2;
}

int main()
{
	pthread_t tid1,tid2;
	int err;
	err= pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err)
	{
		printf("creat new thread 1 failed\n");
		return 0;
	}    
	err= pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err)
	{
		printf("creat new thread 2 failed\n");
		return 0;
	} 

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);				//主线程中等待子线程运行结束
	printf("main thread \n");
	return 0;
}
