#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#define Length 20
#define Status int
#define Elemtype int

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

typedef struct Node{
	Elemtype data;
	struct Node *next;
}Node;
typedef struct Node *LinkList;

LinkList CreatListHead(int n)
{
	LinkList L;
	LinkList p;
	int i;
	srand(time(0));
	L = (LinkList)malloc(sizeof(Node));		
	L->next =NULL;
	
	for(i=0; i<n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		p->data = rand()%100+1;
		//printf("%5d\n",p->data);
		p->next =L->next;
		L-> next = p;
	}
	return L;
}



Status GetElem(LinkList L, int i , Elemtype *e)
{
	int j;
	LinkList p;
	p = L->next;
	j =1;
	
	while((p!=NULL) && (j<i))
	{
		//printf("%5d",p->data);
		p =p->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	
	*e = p->data;
	return OK;
}

Status ListInsert(LinkList L, int i , Elemtype e)
{
	int j;
	LinkList p,temp;
	p = (LinkList)malloc(sizeof(Node));
	p ->data = e;
	temp = L;
	j =1;
	while(temp&& (j<i))
	{
		temp =temp->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	p->next = temp->next;
	temp->next =p;
	return OK;
}

Status ListDelete(LinkList L, int i , Elemtype *e)
{
	int j;
	LinkList p,q;
	j =1;
	p = L;
	
	while(p && (j<i))
	{
		p =p->next;
		++j;
	}
	if(!p || j>i)
		return ERROR;
	q = p-> next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;
}

void ListShow(LinkList L)
{
	LinkList p;
	p = L->next;
	while(p)
	{
		printf("%4d",p->data);
		p=p->next;
	}
	printf("\n");
}

Status ListClear(LinkList L)
{
	LinkList p,q;
	p = L;
	while(p)
	{
		q=p;
		p=p->next;
		free(q);
	}
	return OK;
}


int main()
{
	Elemtype tmp;
	LinkList p,mylink;
	int i,ret,del;
	mylink = CreatListHead(Length);
	
	printf("before insert the List is :\n");
	ListShow(mylink);
	
	ret = GetElem(mylink, 5 ,&tmp);
	if(ret == ERROR)
		printf("Element doesn't exist\n");
	printf("the result is %3d\n",tmp);

	ret = ListInsert(mylink,4,32);
	if(ret == ERROR)
		printf("Insert failure\n");

	printf("after insert the List is :\n");
	ListShow(mylink);


	ret = ListDelete(mylink,5,&del);
	printf("the num deleted is %d,after delete the List is : \n",del);
	ListShow(mylink);
	
	ListClear(mylink);
	return 0;
}
