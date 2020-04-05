#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#define Maxsize 20
#define Status int
#define Elemtype int

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct
{
	Elemtype data;
	int cur;
}component, StaticLinkList[Maxsize];


Status InitList(StaticLinkList space)
{
	int i;
	for(i=0;i<Maxsize;i++)
		space[i].cur = i+1;
	space[Maxsize-1].cur = 0;
	return OK;
}

int Malloc_SLL(StaticLinkList space)
{
	int i;
	i = space[0].cur;
	space[0].cur = space[i].cur;
	return i;
}

int ListLength(StaticLinkList space )
{
	int Length=0;
	int k;
	k = space[Maxsize-1].cur;
	while(k)
	{
		k = space[k].cur;
		Length++;
	}
	return Length;
}

Status ListInsert(StaticLinkList space,int i, Elemtype e)
{
	int add,j,k;
	if(i<1 || i>ListLength(space)+1)
		return ERROR;
	add=Malloc_SLL(space);
	if(add)
	{
		if(space[Maxsize-1].cur == 0)
		{
			space[Maxsize-1].cur = 1;
			k = space[Maxsize-1],cur;
			space[k].data = e;
			
		}
		for(j=1;j<i-1;j++)
			k = space[k].cur;
		space[add].cur = space[k].cur;
		space[k].cur = add;
		return OK;
	}

}

void ShowList(StaticLinkList space)
{
	int i,k;
	k =space[Maxsize-1];
	while(k)
	{
		
	}
}

int main()
{
	int i,ret;
	StaticLinkList mySlink;
	InitList(mySlink);
	ret = ListInsert(mySlink, 3, 40);
	printf("this is the test part:\n");
	for(i=0;i<Maxsize;i++)
		printf("%4d",mySlink[i].data);
	return 0;
}
