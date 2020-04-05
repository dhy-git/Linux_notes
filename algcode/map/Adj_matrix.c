/*
图的邻接矩阵表示方法，以及对邻接矩阵表示下的无向图的遍历方法：
1. 深度优先遍历
2. 广度优先遍历
*/

#include "stdlib.h"
#include "stdio.h"
//1.图的邻接矩阵相关宏定义
typedef char VertexType;
typedef int EdgeType;
typedef bool Boolean;
#define MAXVEX 100          //最大顶点数
#define INFINITY 65535
#define TRUE 1
#define FALSE 0

//2. 队列使用的宏定义
#define Status int
#define Maxsize 20
#define OK 1
#define ERROR 0

//图数据结构定义
Boolean visited[MAXVEX]     //遍历时的访问标记数组（布尔值：True/False）
typedef struct
{
    VertexType vexs[MAXVEX];        //图节点
    EdgeType arc[MAXVEX][MAXVEX];   //边矩阵
    int numVertexes, numEdges;      //当前图中的顶点数和边数
}MGraph;


//队列数据结构
typedef int Elemtype;
typedef struct 
{
	Elemtype data[Maxsize];
	int front;
	int rear;
}SqQueue;

/*队列相关操作函数：
    1. InitQueue 初始化队列
    2. QueueLength 返回队列长度
    3. ClearQueue 清空队列
    4. DeQueue 出队
    5. EnQueue 入队
*/
void InitQueue(SqQueue *Q)
{
	Q->front = 0;
	Q->rear= 0;
}
int QueueLength(SqQueue *Q)
{
	int len;
	len =(Q->rear-Q->front+Maxsize)%Maxsize;
	return len;
}
Status ClearQueue(SqQueue *Q)
{
	int i;
	for(i=0;i<QueueLength(Q);i++)
		Q->data[i] = 0;
	Q->front= 0 ;
	Q->rear = 0;
}

Status DeQueue(SqQueue *Q, Elemtype *e)
{
	if(Q->rear == Q->front)
	{
		printf("the queue is empty\n");
		return ERROR;
	}
	*e = Q->data[Q->front++];
	printf("%d is put out from queue, Length is %d\n",*e,QueueLength(Q));
	return OK;
}

Status EnQueue(SqQueue *Q,Elemtype e)
{
	if((Q->rear+1)%Maxsize==Q->front)
	{
		printf("the queue is full\n");
		return ERROR;
	}
	Q->data[Q->rear] = e;
	Q->rear++;
	printf("Element %d enter the Quene Success, queue's size is %d\n",Q->data[(Q->rear)-1],QueueLength(Q));
	return OK;
}

/*
创建无向图的邻接阵，时间复杂度 O(n+n^2+e)
*/
void CreateMGraph( MGraph *G)
{
    int i,j,k,w;
    printf("输入顶点数和边数：\n");
    scanf("%d,%d",&G->numVertexes,&G->numEdges);
    for(i=0;i<G->numVertexes,i++)
        scanf(&G->vexs[i]);
    for(i=0;i<G->numVertexes,i++)
        for(j=0;j<G->numVertexes,j++)
            G->arc[i][j] = INFINITY;
    for(k=0;k<G->numEdges;k++)
    {
        printf("输入边[vi,vj]的下标i,j 以及权w：\n");
        scanf("%d,%d,%d",&i,&j,&w);
        G->arc[i][j]=w;
        G->arc[j][i]=G->arc[i][j];      //无向图，邻接矩阵对称
    }
}

/*
1. 深度优先递归算法DFS
*/
void DFS(MGraph G, int i)
{
    int j;
    visited[i] =TRUE;
    printf("%c", G.vexs[i]);        //打印顶点或者其他操作
    for(j=0;j<G.numVertexes;j++)
    {
        if(G.arc[i][j]==1 && !visited[j])
            DFS(G, j);              //对未访问的邻接顶点递归调用
    }
}

/*
邻接矩阵的深度遍历操作，时间复杂度O(n^2)
*/
void DFSTraverse(MGraph G)
{
    int i;
    for(i=0;i<G.numVertexes;i++)
        visited[i] = FALSE;        //初始化所有顶点状态都是未访问
    for(i=0;i<G.numVertexes;i++)
        if(!visited[i])            //未访问的顶点调用DFS，若是连通图只会调用一次
            DFS(G,i);
}


/*
邻接矩阵的广度优先遍历操作
*/
void BFSTraverse(MGraph G)
{
    int i,j;
    SqQueue Q;
    for(i=0;i<G.numVertexes;i++)
        visited[i]=FALSE;
    InitQueue(&Q);
    for(i=0;i<G.numVertexes;i++)
    {
        if(!visited[i])                 //未访问->处理
        {
            visited[i]=TRUE;
            printf("%c",G.vexs[i]);
            EnQueue(&Q,i);              //顶点标号入队
            while(!QueueEmpty(Q))
            {
                DeQueue(&Q,&i);
                for(j=0;j<G.numVertexes;j++)
                {
                    if(G.arc[i][j]==1 && !visited[j])
                    {
                        visited[j] = TRUE;
                        printf("%c",G.vexs[j]);
                        EnQueue(&Q,j);
                    }
                }
            }
        }
    }
}


/*
最小生成树算法——Prim算法:

*/
void MiniSpanTree_Prim(MGraph G)
{
    int min, i, j, k;
    int adjvex[MAXVEX];     //保存相关顶点的下标
    int lowcost[MAXVEX];    //保存相关顶点间的边权值
    lowcost[0] = 0;         //初始化第一个权值为0，Vo加入生成树
    adjvex[0] = 0;          //初始化第一个顶点下标为0；
    for(i=1;i<G.numVertexes;i++)
    {
        lowcost[i] = G.arc[0][i];   //V0顶点相邻且有边的权值存入数组
        adjvex[i] = 0;      //初始化为V0的下标
    }
    for(i=1;i<G.numVertexes;i++)
    {
        min = INFINITY;     //初始化最小值为无穷
        j =i; k = 0;
        while (j<G.numVertexes)
        {
            if(lowcost[j]!=0 && lowcost[j]<min)
            {   /* 若权值不为0，且小于最小值，取当前权值为最小值，并将最小值对应下标存到k*/
                min = lowcost[j];
                k = j;
            }
            j++;
        }
        printf("(%d,%d)",adjvex[k],k);  //打印当前顶点最小权值边
        lowcost[k] = 0;            //设置当前权值为0,顶点加入生成树
        for(j=1;i<G.numVertexes;i++)
        {
            if(lowcost[j]!=0 && G.arc[k][j]<lowcost[j])
            {
                lowcost[j] = G.arc[k][j];   //将较小的权值存入lowcost
                adjvex[j] = k;      //将下标为k的节点存入adjvex;
            }
        }
    }
}

/*
最短路径算法————Dijkstra算法：
    求有向网G的V0顶点到其余顶点V的最短 路径P[v]以及带权长度D[V]
*/
typedef int Pathmatrix[MAXVEX];         //最短路径下标存储数组
typedef int ShortPathtable[MAXVEX];     //到各点最短路径的权值和

void ShortestPath_Dijkstra(MGraph G,  int v0, Pathmatrix *P, ShortPathtable *D)
{
    int v,w,k,min;
    int final[MAXVEX];  //标志位数组，final[w]=1表示求得顶点v0到v的最短路径
    for(v=0;v<G.numVertexes;v++)
    {/*初始化，各个结点最短路径未知，v0有连线的节点加上权值，路径数组初始化为0*/
        final[v] = 0;
        (*D)[v] = G.arc[v0][v];
        (*P)[v] = 0;
    }
    (*D)[v0] = 0;       //特别的，初始化v0到v0路径为0
    final[v0] = 1;      //v0到v0不需要求解最短路径
    //主循环：求解最短路径
    for(v=1; v<G.numVertexes; v++)
    {
        min = INFINITY;
        for(w=0; w<G.numVertexes; w++)
        {
            if(!final[w] && (&D)[w]<min)
            {
                k=w;
                min =(*D)[w];
            }
        }
        final[k] = 1;       //当前找到最近的顶点置为1
        for(w=0; w<G.numVertexes; w++)
        {
            /*如果经过v顶点的路径比现在的路径长度短的话*/
            if(!final[w] && (min+G.arc[k][w]<(*D)[w]))
            {
                /*说明找到了更短的路径, 修改D[w]和P[w]*/
                (*D)[w] = min + G.arc[k][w];
                (*P)[w] = k;
            }
        }
    }
}
