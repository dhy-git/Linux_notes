/*
进程信号发送
*/
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "signal.h"
void *thread_fun(void *stu)
{
	sleep(1);
	printf("this is a new thread\n");
	return (void *)0;
}

int main(  )
{
	pthread_t tid;
	int err;
	int s;
	void * rval;
	err= pthread_create(&tid, NULL, thread_fun, NULL);
	if(err != 0)
	{
		 printf("creat new thread failed\n");
		return 0;
	}     
	sleep(1);
	s = pthread_kill(tid,SIGQUIT);
	if(s != 0)
	{
		 printf("thread tid is not found\n");
	}     
	pthread_join(tid,&rval);
	printf("main thread \n");
	return 0;
}