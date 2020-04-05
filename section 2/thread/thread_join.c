#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
void *thread_fun1(void *arg)
{

	printf("new  thread 1\n");
	return (void *)1;

}

void *thread_fun2(void *arg)
{

	printf("new  thread 2\n");
	pthread_detach(pthread_self());
	//pthread_exit((void *)2);
	return (void *)2;
}


int main( int argc, char * argv[])
{
	int err1,err2;
	pthread_t tid1;
	pthread_t tid2;
	void * rval1, * rval2;
	err1= pthread_create(&tid1, NULL, thread_fun1,NULL);
	err2= pthread_create(&tid2, NULL, thread_fun2,NULL);
	if(err1 || err2)
	{
		printf("creat new thread failed\n");
		return 0;
	}     
	printf("main thread\n");
	printf("join1 rval is %d\n",pthread_join(tid1,&rval1));
	printf("join2 rval is %d\n",pthread_join(tid2,&rval2));
	printf("thread1 exit code is %d\n",(int *)rval1);
	printf("thread2 exit code is %d\n",(int *)rval2);		
	return 0;
}
