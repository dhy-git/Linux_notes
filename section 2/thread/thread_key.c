/*
	线程私有数据————键类型的使用:key与私有数据关联 
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"  
#include "unistd.h"

pthread_key_t  key;

void *thread_fun1(void *arg)
{
    printf("thread 1 start\n");
    int a = 1;
    pthread_setspecific(key,(void *)a);            //键关联到变量a a=1
    sleep(2);                                       //睡眠2秒时，线程thread_fun2同样关联键key到a，但这个a是私有数据，改变不影响线程1中a的值
    printf("thread 1 key->data is %d\n",pthread_getspecific(key));

    return (void *)1;
}

void *thread_fun2(void *arg)
{
    sleep(1);
    printf("thread 2 start\n");
    int a =2;
    pthread_setspecific(key, (void *)a);            //键关联到变量a
    printf("thread 2 key->data is %d\n",pthread_getspecific(key));

    return (void *)2;
}

int main()
{
	pthread_t tid1,tid2;
	int err;
    pthread_key_create(&key, NULL);
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
    pthread_key_delete(key);

	return 0;
}
