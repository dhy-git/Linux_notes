/*
信号处理函数：
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
    参数:   signum 宏定义操作：例 SIGQUIT
            struct sigaction {
               void     (*sa_handler)(int);        //信号集处理程序
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;                //信号屏蔽字
               int        sa_flags;               
               void     (*sa_restorer)(void);
           };
对信号集的处理函数有以下几个：
int sigemptyset(sigset_t *set);                //清空信号集
int sigfillset(sigset_t *set);                //将所有信号加入信号集
int sigaddset(sigset_t *set, int signum);       //增加一个信号到信号集
int sigdelset(sigset_t *set, int signum);        //删除一个信号到信号集
int sigismember(const sigset_t *set, int signum);    //检查signum是否为信号集

int pthread_sigmask(int how, const sigset_t *set, sigset_t *oldset);   主要对sigaction函数中的sig_mask操作，使信号处理函数被屏蔽；可以用于多线程信号屏蔽处理



注： 该实例中，sigaction 函数定义了SIGQUIT的回调函数，无论哪里的SIGQUIT都会调用哪个函数
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "signal.h"

void sig_handler1(int arg)
{
	printf("thread1 get signal\n");
	return ;
}
void sig_handler2(int arg)
{
	printf("thread2 get signal\n");
	return;
}

void *thread_fun1(void *arg)
{
	printf("this is  the new thread1\n");
	struct sigaction act;
	memset(&act,0, sizeof(act));
	sigaddset(&act.sa_mask, SIGQUIT);					//SIGQUIT加入信号集
	act.sa_handler = sig_handler1;
	sigaction(SIGQUIT, &act, NULL);						//注册信号处理函数 

	pthread_sigmask(SIG_BLOCK,&act.sa_mask,NULL);		//信号屏蔽掩码，将当前信号进行屏蔽
	sleep(2);
	
}
void *thread_fun2(void *arg)
{
	printf("this is  the new thread2\n");
	struct sigaction act;
	memset(&act,0, sizeof(act));
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_handler = sig_handler2;
	sigaction(SIGQUIT, &act, NULL);

	//pthread_sigmask(SIG_BLOCK,&act.sa_mask,NULL);		
	sleep(2);
	
}

int main()
{
	pthread_t tid1,tid2;
	int err;
	int s;
	void * rval;
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
	s = pthread_kill(tid1,SIGQUIT);
	if(s != 0)
	{
		 printf("send signal to thread1 failed\n");
	}     
	s = pthread_kill(tid2,SIGQUIT);
	if(s != 0)
	{
		printf("send signal to thread2 failed\n");
	}
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);				//主线程中等待子线程运行结束
	printf("main thread \n");
	return 0;
}
