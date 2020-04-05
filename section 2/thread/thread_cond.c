/*
    条件变量的应用：
        生产者消费者对产品库存的操作：使用结构体模拟库存
        1. put操作：空间非满，存储数据，存储位置+1 ，通知其他线程空间有数据已经非空；
        2. get操作：空间非空，读取数据，读取位置+1，通知其他线程已经取出数据，线程非满；
        3. 生产者线程每隔1秒调用put，产够30个停止生产
        4. 消费者线程每隔2秒调用get，区够30个就停止
        5. 库存最大为五个，库存满则生产阻塞，库存空则消费阻塞
*/

#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"

#define BUFFER_SIZE 5   //产品库存的大小
#define PRODUCT_CNT 30  //生产总数

/*库存数据结构*/
struct product_cons
{
    int buffer[BUFFER_SIZE];      //缓冲区，存放产品值
    int readpos,writepos;   //读写位置
    pthread_mutex_t lock;   //互斥量
    pthread_cond_t notempty;    //非空条件
    pthread_cond_t notfull;     //非满条件
}buffer;

/*初始化互斥量以及条件变量*/
void init(struct product_cons *p)          
{
    pthread_mutex_init(&p->lock, NULL);
    pthread_cond_init(&p->notempty, NULL);
    pthread_cond_init(&p->notfull, NULL);
    p->readpos = 0;
    p->writepos = 0;
}

/*完成后销毁互斥量以及条件变量*/
void finish(struct product_cons *p)
{
    pthread_mutex_destroy(&p->lock );
    pthread_cond_destroy(&p->notempty );
    pthread_cond_destroy(&p->notfull );
    p->readpos = 0;
    p->writepos = 0;
}

/*生产操作*/
void put(struct product_cons *p,int data)
{
    pthread_mutex_lock(&p->lock );              
    if((p->writepos+1)%BUFFER_SIZE == p->readpos)
    {
        printf("producer wait for not full\n");
        pthread_cond_wait(&p->notfull, &p->lock);           //库存已满则所在线程阻塞，将互斥量加入条件变量，让消费线程使用互斥量进行其他操作
    }
    p->buffer[p->writepos] = data;
    p->writepos++;
    if(p->writepos>=BUFFER_SIZE)
        p->writepos=0;                                     //缓冲区循环位移，动态存储
    pthread_cond_signal(&p->notempty);                     //每次生产完成后发出信号，唤醒一个等待条件的线程
    pthread_mutex_unlock(&p->lock);                        //当前互斥量解锁
}

int get(struct product_cons *p)
{   
    int data;
    pthread_mutex_lock(&p->lock);
    if(p->readpos == p->writepos)
    {
        printf("consumer wait for not empty\n");
        pthread_cond_wait(&p->notempty, &p->lock);
    }
    data = p->buffer[p->readpos];
    p->readpos++;
    if(p->readpos >= BUFFER_SIZE)
        p->readpos=0;
    pthread_cond_signal(&p->notfull);
    pthread_mutex_unlock(&p->lock);
    return data;
}
void *producer(void *data)
{
    int n;
    for(n=1; n<=30; ++n)
    {
        sleep(1);
        printf("put the %d product...\n",n);
        put(&buffer,n);
        printf("put the %d product success.\n",n);
    }
    printf("producer stopped\n");
    return NULL;
}
void *consumer(void *data)
{
   static int cnt = 0;
    int num;
    while(1)
    {
        sleep(2);
        printf("get product...\n");
        num = get(&buffer);
        printf("get product %d success.\n",num);
        if(++cnt == PRODUCT_CNT)
            break;
    }
    printf("consumer stopped\n");
    return NULL;
}

int main()
{
    pthread_t th_a,th_b;
    void *retval;
    int err;
    init(&buffer);          //初始化互斥朗以及条件变量

    err = pthread_create(&th_a, NULL, producer, NULL);
    if(err)
    {
        printf("producer creat failed\n");
         return 0;
    }
    err = pthread_create(&th_b, NULL, consumer, NULL);
    if(err)
    {
        printf("consumer creat failed\n");
        return 0;
    }
    pthread_join(th_a, &retval);
    pthread_join(th_b, &retval);
    finish(&buffer);      //销毁互斥量以及条件变量等操作
    return 0;
}