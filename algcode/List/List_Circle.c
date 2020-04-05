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
	struct Node *prior;
	struct Node *next;
	int Len;
}DuNode;
typedef struct Node *DuLinkList;

DuLinkList CreatListHead()
{
	DuLinkList L;
	DuLinkList p;
	int i;
	srand(time(0));
	L = (DuLinkList)malloc(sizeof(DuNode));
	L->prior = L;
	L->next = L;
	L->Len = 0;
//	for(i=0; i<L->Len; i++)
//	{
//		p = (DuLinkList)malloc(sizeof(DuNode));
//		//p->data = rand()%100+1;
//		p->data = i+1;
//		
//		p->prior = L;
//		p->next =L->next;
//		L->next->prior = p;
//		L->next =p;
//	}
	return L;
}

void DuLinkListShow(DuLinkList L)
{
	int i=L->Len;
	DuLinkList p;
	p =  L->next;
	printf("the DuLink list's length is %2d\n",i);
	while(i)
	{
		printf("%4d",p->data);
		i--;
		p = p->next;
	}
	printf("\n");
}

Status DuLinkListInsert(DuLinkList L, int i , Elemtype e)
{
	DuLinkList p, s;
	int j=1;
	if(i<1 || i> Length)
		return ERROR;
	s = (DuLinkList)malloc(sizeof(DuNode));
	s->data = e;
	p = L->next;
	for(; j<i-1;j++)
	{
		p= p->next;
	}
	s->prior = p;
	s->next = p->next;
	p->next->prior = s->next;
	p->next = s;
	(L->Len)++;
	return OK;
}


Status DuLinkListDelete(DuLinkList L, int i , Elemtype *e)
{
	DuLinkList p, q;
	int j=1;
	if(i<1 || i> Length)
		return ERROR;
	p = L->next;
	for(; j<i-1;j++)
	{
		p= p->next;
	}
	q = p->next;
	*e = q->data;
	printf("delete the data: %2d\n",*e);
	p->next = p->next->next;
	p->next->prior = p;
	free(q);
	(L->Len)--;
	return OK;
}

DuLinkList DuLinkListJoint(DuLinkList La,DuLinkList Lb)
{
	int j;
	DuLinkList p,q,target;
	p = La;
	target = p;
	q = Lb;
	for(j=1; j<(La->Len);j++)
	{
		p= p->next;
	}
	p->next = q;
	p->next->prior = p;
	for(j=1; j<(Lb->Len);j++)
	{
		q= q->next;
	}
	q->next = target;
	q->next->prior = q;
	return target;
}

int main()
{
	Status ret;
	int i,del;
	DuLinkList myDL1,myDL2,myJoint;
	int Len1=5;
	int Len2=3;
	srand(time(0));
	myDL1 = CreatListHead();
	for(i=0;i<Len1;i++)
	{
		ret = DuLinkListInsert( myDL1,1,rand()%100+1);
		if(ret == ERROR)
		printf("Insert Error\n");
	}
//	ret = DuLinkListInsert( myDL,4,99);
//	if(ret == ERROR)
//		printf("Insert Error\n");
	DuLinkListShow(myDL1);
	
//	ret = DuLinkListDelete(myDL,4,&del);
	
	myDL2 = CreatListHead();
	for(i=0;i<Len2;i++)
	{
		ret = DuLinkListInsert( myDL2,1,rand()%100+1);
		if(ret == ERROR)
		printf("Insert Error\n");
	}

	DuLinkListShow(myDL2);
	myJoint = DuLinkListJoint(myDL1,myDL2);
	
	DuLinkListShow(myJoint);
	return 0;
}
