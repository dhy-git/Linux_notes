/*
线程取消函数：
对应被取消的线程可以设置响应该取消信号的方式
pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);    
	PTHREAD_CANCEL_DISABLE 设置为线程不响应pthread_cancel发送的信号；
	PTHREAD_CANCEL_ENABLE  设置为线程响应取消信号
线程取消操作需要被操作线程的配合——即检查是否发来取消自身线程的请求，这种配合由线程中的取消点实现。
Linux中线程响应取消信号的取消点有很多：
pthread_join()、pthread_testcancel()、pthread_cond_wait()、pthread_cond_timewait()、sem_wait()、write、read、printf()等大多数系统阻塞调用都存在取消点。
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
void *thread_fun(void *arg)
{
	int stateval;
	int typeval;
	stateval= pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	if(stateval !=0)
	{
		printf("set cancel state failed\n");
	}
	printf("I'm new thread\n");
	sleep(4);

	printf("about to cancel\n");
	stateval= pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	if(stateval !=0)
	{
		printf("set cancel state failed\n");
	}
	//typeval = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	if(typeval !=0)
	{
		printf("set cancel type failed\n");
	}
	printf("first cancel point\n");
	printf("second cancel point\n");
	return (void *)20;
}


int main( int argc, char * argv[])
{
	pthread_t tid;
	void * rval;
	int err,cval,jval;
	err= pthread_create(&tid, NULL, thread_fun,NULL);
	if(err)
	{
		printf("creat new thread failed\n");
		return 0;
	}     
	sleep(2);
	cval = pthread_cancel(tid);
	if(cval != 0)
	{
		printf("cancel thread failed\n");
	}
	jval = pthread_join(tid,&rval);
	printf("new thread exit code is %d\n",(int *)rval);
	
	return 0;
}
