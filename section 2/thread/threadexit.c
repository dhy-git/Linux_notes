/*
创建线程，输入参数1/2/3使用不同的方法实现线程退出
exit()退出进程！
*/
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
void *thread_fun(void *arg)
{
	if(strcmp("1",(char *)arg)==0)
	{
		printf("new  thread return!\n");
		return (void *)1;
	}
	if(strcmp("2",(char *)arg)==0)
	{
		printf("new  thread pthread_exit!\n");
		pthread_exit((void *)2);
	}
		if(strcmp("3",(char *)arg)==0)
	{
		printf("new  thread exit!\n");
		exit(3);
	}	
}

int main( int argc, char * argv[])
{
	pthread_t tid;
	int err;
	void * rval;
	err= pthread_create(&tid, NULL, thread_fun, (void *)(argv[1]));
	if(err != 0)
	{
		printf("creat new thread failed\n");
		return 0;
	}     
	sleep(1);
	pthread_join(tid,&rval);
	printf("main thread\n");
	return 0;
}
