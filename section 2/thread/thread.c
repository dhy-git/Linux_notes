#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
struct student{
    int age;
    char name[];
};
void *thread_fun(void *stu)
{
    printf("student age is %d, name is %s", (struct student *)stu->age, (struct student *)studenrt-> name);
    return (void *)0;
}

int main( int argc, char * argv[])
{
    pthread_t tid;
    int err;

    struct student stu;
    stu age = 20;
    memcpy(stu.name, "zhangsan",20);

    err= pthread_creat(&tid, NULL, thread_fun, (void *)(&stu));
    if(err != 0)
    {
        printf("creat new thread failed\n");
        return 0;
    }     

    int i;
    printf("main thread has %d args\n",argc);
    for(i=0; i<argc; i++)
    {
        printf("main thread args is %s\n",argv[i]);
    }
    sleep(1)
    return 0;
}