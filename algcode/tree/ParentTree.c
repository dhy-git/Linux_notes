#include "stdlib.h"
#include "stdio.h"

#define Maxsize_Tree 100
typedef int TElemType;

/************************1. parent tree expression method*************************/

typedef struct PTNode
{
	TElemType data;			//root's data is -1;
	int parent;
	int firstchild;
}PTNode;

typedef struct
{
	PTNode nodes[Maxsize_Tree];	// Initiating  the table of all nodes in tree
	int r,n;    //the address of root, and the number of the tree:T;
}PTree;

/**************************************************************************/


/************************2. child tree expression method*************************/

typedef struct CTNode		//Child Node Link-Structure
{
	int child;
	struct CTNode *next;
}*ChildPtr;

typedef struct 				// List for  Head of Child's Link 
{
	TElemType data;
	ChildPtr firschild;
}CTBox;

typedef struct				//Stucture of tree
{
	CTBox nodes[Maxsize_Tree];
	int r,n;
}CTree; 

/**************************************************************************/


/************************3. child-sib tree expression method*************************/

typedef struct CSNode		//Child Node Link-Structure
{
	TElemType data;
	struct CSNode *firstchild,*rightsib;
}CSNode, *CSTree;

/**************************************************************************/

