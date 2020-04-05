#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define Status int
#define Maxsize 20
#define OK 1
#define ERROR 0

typedef int QElemtype;
typedef struct QNode
{
	QElemtype data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct
{
	QueuePtr front,rear;
}LinkQueue;

void InitLinkQueue(LinkQueue *LQ)
{
	QueuePtr Qn;
	Qn = (QueuePtr) malloc (sizeof(QNode));
	Qn->data = 0;
	Qn->next = NULL;		//creat header , header->next = NULL;
	
	LQ->front = Qn;		//creat pointer
	LQ->rear =Qn;
}
int LinkQueueLength(LinkQueue *LQ)
{
	QueuePtr q;
	int Len=0;
	q = LQ->front;
	while((q->next)!=NULL)
	{
		q = q->next;
		Len++;
	}
	return Len;
}

Status EnLinkQueue(LinkQueue *LQ, QElemtype e)
{
	QueuePtr s;
	s = (QueuePtr) malloc (sizeof(QNode));
	s->data = e;
	if(!s)
		return ERROR;
	s->next = NULL;
	LQ->rear->next = s;
	LQ->rear = s;
	printf("enter  %d into the queue success,length is %d\n", LQ->rear->data, LinkQueueLength(LQ));
	return OK;
}

Status DeLinkQueue(LinkQueue *LQ, QElemtype *e)
{
	QueuePtr q;
	if(LQ->front->next ==NULL)
	{
		printf("queue is empty\n");
		return ERROR;
	}
	*e = LQ->front->next->data;
	q= LQ->front;
	LQ->front = LQ->front->next;
	printf("delete %d form the queue success,length is %d\n", *e, LinkQueueLength(LQ));
	free(q);
	return OK;
}
int main()
{
	int ret,del,len=3;
	LinkQueue myLQ;
	srand(time(0));
	InitLinkQueue(&myLQ);
	printf("Length = %d\n",LinkQueueLength(&myLQ));
	while(len--)
	{
		ret = EnLinkQueue(&myLQ, rand()%100+1);
		if(ret == ERROR)
			break;
	}
	DeLinkQueue(&myLQ,&del);
	DeLinkQueue(&myLQ,&del);
	DeLinkQueue(&myLQ,&del);
	DeLinkQueue(&myLQ,&del);
	return 0;
}
