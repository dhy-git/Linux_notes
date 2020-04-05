#include "stdlib.h"
#include "stdio.h"
#include "List_Linear.h"

int main()
{
	SqList mylist;
	int i,select;
	int insertnum = 23;
	Status ret;
	ELemType deletenum,target=5;
	ret = InitList(&mylist);
	if(ret == OK)
	{
		printf("Init List Success!\n");
	}
	for(i=0;i<Maxsize;i++)
		printf("%5d",mylist.data[i]);
	printf("\n");

	ret = ListInsert(&mylist,3,&insertnum);
	if(ret == OK)
	{
		printf("insert Success\n");
	}
	for(i=0;i<Maxsize;i++)
		printf("%5d",mylist.data[i]);
	printf("\n");

	
	ret = GetElem(&mylist,2,&select);
	if(ret == OK)
	{
		printf("Get Element Success, target=%d\n",select);
	}
	else
		printf("Get Element false \n");

	ret = LocateElem(&mylist,target);
	if(ret == FALSE)
	{
		printf("Element doesn't exist\n");
	}
	else
		printf("the add is %d\n",ret);

	ret = ListDelete(&mylist,3,&deletenum);
		printf("the delete num is %d\n",deletenum);
	ret = ListLength(&mylist);
		
		printf("right now the length  is %d\n",ret);
		
	return 0;
	
}
