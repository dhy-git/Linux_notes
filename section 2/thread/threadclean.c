/*
信号清除操作函数：
    线程可以安排退出时的清理操作，这与进程的atexit函数安排退出时需要调用的函数类似。这样的函数称为线程清理处理函数。线程可以建立多个清理程序，处理程序记录在栈中，
    因此处理程序的执行顺序和注册的顺序相反。（栈入栈出）
pthread_cleanup_push(void(*rtn)(void*) , void *args)  //注册处理程序
pthread_cleanup_pop(int excute)  //清除处理程序
以上两个处理函数必须成对出现，否则编译出错
在执行以下操作时会调用清理函数，参数由args传入：
    1. 调用pthread_exit();
    2. 响应取消请求;
    3. 用非零参数调用pthread_cleanup_pop;
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

void *first_clean(void *arg)
{
	printf("%s first clean\n",arg);
	return (void *)0;
}
void *second_clean(void *arg)
{
	printf("%s second clean\n",arg);
	return (void *)0;
}
void *thread_fun1(void *arg)
{
	printf("this is  the new thread1\n");
    pthread_cleanup_push(first_clean, "thread1");
    pthread_cleanup_push(second_clean, "thread1");

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);

	return (void *)1;
}
void *thread_fun2(void *arg)
{
	printf("this is  the new thread2\n");
    pthread_cleanup_push(first_clean, "thread2");
    pthread_cleanup_push(second_clean, "thread2");
	//pthread_exit((void *)2);          //若执行该语句，在pop前响应了清理处理函数，清理函数first,second 都顺利执行
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
	pthread_exit((void *)2);
}

int main()
{
	pthread_t tid1,tid2;
	int err;
	err= pthread_create(&tid1, NULL, thread_fun1, NULL);
	if(err != 0)
	{
		printf("creat new thread 1 failed\n");
		return;
	}    
	err= pthread_create(&tid2, NULL, thread_fun2, NULL);
	if(err != 0)
	{
		printf("creat new thread 2 failed\n");
		return;
	} 
	sleep(1);
	return 0;
}
