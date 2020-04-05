/*
    线程同步性测试文件：
    各个线程分别对结构体成员变量统一赋值，理论上各个成员值应该相同；实际受多线程操作影响会出现问题，因此在成员变量值不同时进行报错
    ————
    多线程对同一内存变量进行操作时，容易出现对变量整体的操作不一致
    需要同步机制，保证线程对内存操作时，其余线程无法进行干扰
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

void *thread_fun1(void *arg)
{
    while(1)
    {
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
    return (void *)0;
}
void *thread_fun2(void *arg)
{
    while(1)
    {
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
    return (void *)0;
}

int main()
{
    pthread_t tid1,tid2;
    int err;
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