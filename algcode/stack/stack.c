#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#define Status int
#define Maxsize 128
#define OK 1
#define ERROR 0

typedef int SElemtype;
typedef struct
{
	SElemtype data[Maxsize];
	int top;
}SqStack;


Status InitStack(SqStack *S)
{
	S-> top =0;
	return OK;
}

Status Push(SqStack*S, SElemtype e)
{
	if(S->top == Maxsize-1)
	{
		printf("Stack overflew\n");
		return ERROR;
	}
	S->data[++(S->top)] = e;
/*this is a test message*/
	printf("push %d into the stack success\n",e);
	return OK;
}

Status Pop(SqStack*S, SElemtype *e)
{
	if(S->top ==-1)
		return ERROR;
	*e = S->data[(S->top)--];
	/*this is a test message*/
	printf("pop %d from the stack success\n",*e);
	return OK;
}
Status GetPop(SqStack*S,SElemtype *e)
{
	*e = S->data[(S->top)];
	return OK;
}

int main()
{
	int i,ret, Len=10;	
	SqStack myStack;
	SElemtype p;
	srand(time(0));
	ret = InitStack(&myStack);
	if(ret)
		printf("Init Success\n");
	i=Len;
	while(i)
	{
		ret = Push(&myStack,rand()%100+1);
		if(!ret)
			break;
		i--;
	}
	Pop(&myStack,&p);
	return 0;
}
