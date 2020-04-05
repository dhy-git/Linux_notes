#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define Status int
#define Maxsize 128
#define OK 1
#define ERROR 0

typedef int SElemtype;
typedef struct Stacknode
{
	SElemtype data;
	struct Stacknode *next;
}Stacknode, *LinkStackPtr;

typedef struct LinkStack
{
	LinkStackPtr top;
	int count;
}LinkStack;

void InitLinkStack(LinkStack *S)
{
	S->count=0;
}
Status Push(LinkStack *S, SElemtype e)
{
	LinkStackPtr p = (LinkStackPtr ) malloc (sizeof(Stacknode));
	p->data = e;
	p->next = S->top;
	S->top = p;
	S->count++;
	printf("push %d success,Stack size:%d\n",S->top->data,S->count);
	return OK;
}

Status Pop(LinkStack *S, SElemtype *e)
{
	LinkStackPtr q;
	q = S->top;
	*e = q->data;
	S->top = q->next;
	S->count--;
	printf("pop %d success,Stack size:%d \n",*e,S->count);
	free(q); 
	return OK;
}
int main()
{
	LinkStack myLS;
	InitLinkStack(&myLS);
	int ret,popnum,deepth = 10;
	while(deepth--)
	{
		ret = Push(&myLS, deepth);
		if(!ret)
			break;
	}
	ret = Pop(&myLS, &popnum);
	return 0;
}