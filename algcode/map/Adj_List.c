#include "stdlib.h"
#include "stdio.h"

typedef char VertexType;
typedef int EdgeType;
typedef bool Boolean;
#define MAXVEX 100
#define TRUE 1
#define FALSE 0

Boolean visited[MAXVEX]     //遍历时的访问标记数组（布尔值：True/False）

/*边表节点定义*/
typedef struct EdgeNode
{
    int adjvex;                 //邻接点域，存储该顶点对应下标
    EdgeType weight;            //存储权值，非网图可以忽略
    struct EdgeNode *Next;      //链域，指针指向下一个邻接点 
}EdgeNode;

/*顶点表节点*/
typedef struct VertexNode
{
    VertexType data;            //顶点域，存储顶点信息
    EdgeNode *firstedge;        //边表头指针
}VertexNode, AdjList[MAXVEX];

/*邻接表数据结构*/
typedef struct 
{
    AdjList adjList;
    int numVertexes,numEdges;
}GraphAdjList;


void CreatALGraph(GraphAdjList *G)
{
    int i,j,k;
    EdgeNode *e;
    printf("输入顶点数和边数：\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes;i++)
    {
        scanf(&G->adjList[i].data);         //输入顶点信息
        G->adjList[i].firstedge=NULL;       //边表置为空
    }
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边[vi,vj]上的顶点序号:\n");
        scanf("%d,%d",&i,&j);
        e = (EdgeNode *)malloc(sizeof(EdgeNode));   //内存中申请空间，存储边表节点
        e->adjvex = j;
        e->Next = G->adjList[i].firstedge;          //e指针指向当前顶点指向节点
        G->adjList[j].firstedge = e;
    }
}

/*邻接表深度优先递归算法*/
void DFS(GraphAdjList GL, int i)
{
    EdgeNode *p;
    visited[i] = TRUE;
    printf("%c",GL->adjList[i].data);   /*打印顶点，可以是其他操作*/
    p = GL->adjList[i].firstedge;
    while(p)
    {
        if(!visited[p->adjvex])
            DFS(GL, p->adjvex);         //未访问邻接顶点递归调用
        p = p->next;
    }
}

/*邻接表深度优先遍历操作，时间复杂度O(n+e)*/
void DFSTraverse(GraphAdjList GL)
{
    int i;
    for(i=0;i<GL->numVertexes;i++)
        visited[i] = FALSE;
    for(i=0;i<GL->numVertexes;i++)
        if(!visited[i])
            DFS(GL, i); 
}