/*
多线程操作下互斥量的使用
*/
#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"

struct student{
    int id;
    int age;
    int name;
}stu;
int i;
pthread_mutex_t mutex;          //全局设定互斥量

void *thread_fun1(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);         //线程操作前对互斥量加锁，如果已被其他线程锁住，则阻塞 
        stu.id = i;
        stu.age = i;
        stu.name = i;
        i++;
        if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name)
        {
            printf("%d,%d,%d\n",stu.id,stu.age,stu.name);
            break;
        }
        pthread_mutex_unlock(&mutex);      //线程操作后对互斥量解锁锁
    }
    return (void *)0;
}
void *thread_fun2(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex);  
        stu.id = i;
        stu.age = i;
        stu.name = i;
        i++;
        if(stu.id != stu.age || stu.id != stu.name || stu.age != stu.name)
        {
            printf("%d,%d,%d\n",stu.id,stu.age,stu.name);
            break;
        }
    }
    pthread_mutex_unlock(&mutex); 
    return (void *)0;
}

int main()
{
    pthread_t tid1,tid2;
    int err;
    err = pthread_mutex_init(&mutex, NULL);     //主线程对互斥量初始化
    if(err != 0)
    {
        printf("mutex creat failed\n");
    }
    err = pthread_create(&tid1, NULL, thread_fun1, NULL);
    if(err != 0)
    {
        printf("thread1 creat\n");
    }
    err = pthread_create(&tid2, NULL, thread_fun2, NULL);
    if(err != 0)
    {
        printf("thread2 creat\n");
    }
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;
}