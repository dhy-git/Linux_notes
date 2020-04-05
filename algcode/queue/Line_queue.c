#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define Status int
#define Maxsize 20
#define OK 1
#define ERROR 0

typedef int Elemtype;
typedef struct 
{
	Elemtype data[Maxsize];
	int front;
	int rear;
}SqQueue;

void InitQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear= 0;
}
int QueueLength(SqQueue *Q)
{
	int len;
	len =(Q->rear-Q->front+Maxsize)%Maxsize;
	return len;
}
Status ClearQueue(SqQueue *Q)
{
	int i;
	for(i=0;i<QueueLength(Q);i++)
		Q->data[i] = 0;
	Q->front= 0 ;
	Q->rear = 0;
}

Status DeQueue(SqQueue *Q, Elemtype *e)
{
	if(Q->rear == Q->front)
	{
		printf("the queue is empty\n");
		return ERROR;
	}
	*e = Q->data[Q->front++];
	printf("%d is put out from queue, Length is %d\n",*e,QueueLength(Q));
	return OK;
}

Status EnQueue(SqQueue *Q,Elemtype e)
{
	if((Q->rear+1)%Maxsize==Q->front)
	{
		printf("the queue is full\n");
		return ERROR;
	}
	Q->data[Q->rear] = e;
	Q->rear++;
	printf("Element %d enter the Quene Success, queue's size is %d\n",Q->data[(Q->rear)-1],QueueLength(Q));
	return OK;
}

int main()
{
	int i;
	SqQueue myQueue;
	Elemtype del;
	srand(time(0));
	InitQueue(&myQueue);
	for(i=0;i<3;i++)
	{
		EnQueue(&myQueue, rand()%100+1);
	}
	for(i=0;i<2;i++)
	{
		DeQueue(&myQueue, &del);
	}
	return 0;
}
