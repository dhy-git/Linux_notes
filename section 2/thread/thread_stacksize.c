/*
    设置栈的大小属性
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"      //栈最小值宏定义PTHREAD_STACK_MIN所在头文件

pthread_attr_t attr;
void *thread_fun(void *stu)
{
    size_t stacksize=0;
    #ifdef _POSIX_THREAD_ATTR_STACKSIZE                     //检查宏定义，允许修改栈的大小
        pthread_attr_getstacksize(&attr,&stacksize);
    #endif
    printf("new thread's stacksize = %ld \n",stacksize);
    return (void *)0;
}

int main()
{
    pthread_t tid;
    int err;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    #ifdef _POSIX_THREAD_ATTR_STACKSIZE                     //检查宏定义，允许修改栈的大小
        pthread_attr_setstacksize(&attr, PTHREAD_STACK_MIN);
    #endif

    err= pthread_create(&tid, NULL, thread_fun, NULL);
    if(err)
    {
        printf("creat new thread failed\n");
        return 0;
    }     
    pthread_join(tid, NULL);
    return 0;
}