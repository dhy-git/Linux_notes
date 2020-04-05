#ifndef _LIST_LINEAR_H
#define _LIST_LINEAR_H


typedef int Status;
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define Maxsize  10
typedef int ELemType;
typedef struct
{
	ELemType data[Maxsize];
	int length;
}SqList;

Status InitList(SqList *L);
Status ListEmpty(SqList *L);

Status ClearList(SqList *L);

Status GetElem(SqList *L, int i, ELemType *e);
Status LocateElem(SqList *L, ELemType e);

Status ListInsert(SqList *L, int i, ELemType *e);


Status ListDelete(SqList *L, int i, ELemType *e);

Status ListLength(SqList *L);

#endif

