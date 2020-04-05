#include "stdlib.h"
#include "stdio.h"

#define OVERFLOW 0
#define Maxsize_Tree 100
typedef char BTElemType;

int pos;

typedef struct 
{
	BTElemType data;
	struct BTNode *lchild,*rchild;
}BTNode, *BTree;

int StringLength(char *str)
{
	int i=0;
	while(str[i] != '\0')
		i++;
	return i;
}

void CreateBTree(BTree T, char * strTree)
{
	BTElemType ch;
	if(pos< StringLength(strTree))
	{
		ch = strTree[pos];
		pos++;
	}
	if(ch == '#')
	{
		T = NULL;
	}
	else
	{
		T = (BTree) malloc (sizeof(BTNode));
		if(!T)
		{
			printf("creat ERROR!\n");
			return;
		}
		T->data = ch;
		printf("%c insert the Bitree success\n",T->data);
		CreateBTree((BTree) T->lchild,strTree);
		CreateBTree( (BTree) T->rchild,strTree);
	}
}

void PreOrderTraverse(BTree T)
{
	if(T == NULL)
		return;
	printf("%c\n",T->data);
	PreOrderTraverse((BTree)T->lchild);
	PreOrderTraverse((BTree)T->rchild);
}

int main(int argc , char *argv[])
{
	BTree myBtree;
	pos = 0;
	CreateBTree(myBtree,argv[1]);	
	printf("search the tree\n");
	PreOrderTraverse(myBtree);
	return 0;
}
