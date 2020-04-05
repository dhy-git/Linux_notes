#include "stdlib.h"
#include "stdio.h"
#include "List_Linear.h"

Status InitList(SqList *L)
{
	int i;
	for(i=0;i<Maxsize;i++)
		L->data[i]=0;
	L->length=5;
	for(i=0;i<(L->length);i++)
		L->data[i]=i+1;
	return OK;
}

Status ListEmpty(SqList *L)
{
	if(L->length==0)
		return TRUE;
	return FALSE;
}

Status ClearList(SqList *L)
{
	int i;
	for(i=0;i<Maxsize;i++)
		L->data[i]=0;
	L->length=0;
	return OK;
}

Status GetElem(SqList *L, int i, ELemType *e)
{
	if(L->length==0 || i<1 || i>L->length)
		return ERROR;
	*e = L->data[i-1];
	return OK;
}
Status LocateElem(SqList *L, ELemType e)
{
	int i,add;
	for(i=0;i<(L->length);i++)
		if(e == (L->data[i]))
			return (i+1);
	return FALSE;
}

Status ListInsert(SqList *L, int i, ELemType *e)
{
	ELemType temp; 
	int j;
	if(L->length ==Maxsize||i<1 || i>L->length)
		return ERROR;
	temp = L->data[i-1];
	L->data[i-1]=*e;
	for(j=i;j<(L->length) ;j++)
	{
		temp = temp ^ (L->data[j]);	
		L->data[j] = temp ^ (L->data[j]);
		temp = temp ^ (L->data[j]);
	}
	L->data[j]=temp;
	(L->length)++;
	return OK;
	
}


Status ListDelete(SqList *L, int i, ELemType *e)
{
	int j=i-1;
	if(i<1||i>(L->length))
		return FALSE;
	
	*e = L->data[j];
	for(;j<(L->length);j++)
		L->data[j]=L->data[j+1];
	L->data[j] = 88;
	return OK;
}

Status ListLength(SqList *L)
{
	return (L->length);
}


