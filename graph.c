#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
// assuming that the user is not dumb (i.e. she is not entering redundant values)
// undirected graph
// zero based indexing nodes

typedef struct Chains
{
    int Data;
    int chainCount;
} CH;

typedef struct GRAPH
{
    CH **adjList;
    int countVertex;
} G;

void ADDVERTEX(G *, int);
void ADDEDGE(G *, int, int);
void DISPLAY(G);
void BFS(G);
void DFS(G);
void dfsUtil(G,int,bool*);


int main()
{

    // int **ADJLIST=NULL;
    // int *arr=NULL;

    // ADDVERTEX(&ADJLIST,65);
    // ADDVERTEX(&ADJLIST,54);
    // printf("%p",ADJLIST);
    // printf("%d",*(ADJLIST[0]+1)); //gives 0 because we try to access unallocated single pointer
    // printf("%d",ADJLIST[1]); //gives segfault because we try to access unallocated double pointer
    /*int rows=0;

    int **p=calloc(2,sizeof(int*));

    *p=calloc(1,sizeof(int));
    **p=5;

    *p=realloc(*p,2*sizeof(int));
    *(*p+1)=66;
    printf("%d",);*/

    G *g1 = calloc(1, sizeof(G));

    ADDVERTEX(g1, 0);
    ADDVERTEX(g1, 1);
    ADDVERTEX(g1, 2);
    ADDVERTEX(g1, 3);
    ADDVERTEX(g1, 4);

    ADDEDGE(g1, 0, 1);
    ADDEDGE(g1, 2, 3);
    ADDEDGE(g1, 2, 4);
    ADDEDGE(g1, 0, 3);

    DISPLAY(*g1);

    BFS(*g1);

    // printf("%d",(*(*(g1->adjList+2))).chainCount); //accessing chain count
    // printf("%d", (**(g1->adjList + 7)).Data);  //accessing nodes
    // printf("%d", (*(*(g1->adjList+1)+1)).Data);  //accessing list members
    return 0;
}

void ADDVERTEX(G *graph, int vertex)
{
    if (graph->adjList == NULL)
    {
        graph->adjList = calloc(1, sizeof(CH *)); // allocate memory for single pointers to integers
        graph->countVertex = 0;
        *(graph->adjList) = calloc(1, sizeof(CH)); // allocate memory for integers
        (**(graph->adjList)).Data = vertex;
        (**(graph->adjList + graph->countVertex)).chainCount = 1;
        graph->countVertex++;
    }
    else
    {
        graph->adjList = realloc(graph->adjList, (graph->countVertex + 1) * sizeof(CH *));
        *(graph->adjList + graph->countVertex) = calloc(1, sizeof(CH));
        (**(graph->adjList + graph->countVertex)).Data = vertex;
        (**(graph->adjList + graph->countVertex)).chainCount = 1;
        graph->countVertex++;
    }
    // count stored in first element of the array
}

void ADDEDGE(G *graph, int a, int b)
{
    *(graph->adjList + a) = realloc(*(graph->adjList + a), ((*(graph->adjList + a))->chainCount + 1) * sizeof(CH));
    *(graph->adjList + b) = realloc(*(graph->adjList + b), ((*(graph->adjList + b))->chainCount + 1) * sizeof(CH));

    (*(*(graph->adjList + a) + (*(graph->adjList + a))->chainCount)).Data = b;
    (*(*(graph->adjList + b) + (*(graph->adjList + b))->chainCount)).Data = a;

    (*(graph->adjList + a))->chainCount++;
    (*(graph->adjList + b))->chainCount++;
}

void DISPLAY(G graph)
{
    for (int i = 0; i < graph.countVertex; i++)
    {
        printf("%d ", (**(graph.adjList + i)).Data);
        for (int j = 1; j < (**(graph.adjList + i)).chainCount; j++)
        {
            printf("->%d", (*(*(graph.adjList + i) + j)).Data);
        }
        printf("\n");
    }
}

void BFS(G graph)
{
    int starting_node;
    printf("Enter the starting node for BFS traversal\n");
    scanf("%d", &starting_node);

    bool visited[graph.countVertex];

    for (int i = 0; i < graph.countVertex; i++)
    {
        if (i == starting_node)
        {
            visited[i] = true;
        }
        else
        {
            visited[i] = false;
        }
    }
    int queue[graph.countVertex];
    int front = -1;
    int rear = -1;

    queue[++front] = starting_node;

    rear++;

    while (front <= rear)
    {
        printf("%d ", queue[front]);
        for (int i = 1; i < (*(graph.adjList + queue[front]))->chainCount; i++)
        {
            if (!visited[(*(graph.adjList + queue[front]) + i)->Data])
            {
                queue[++rear] = (*(graph.adjList + queue[front]) + i)->Data; // enqueue
                visited[(*(graph.adjList + queue[front]) + i)->Data] = true;
            }
        }
        front++; // dequeue
    }
}

void DFS(G graph)
{
    int starting_node;
    printf("Enter the starting node for DFS traversal\n");
    scanf("%d", &starting_node);

    bool visited[graph.countVertex];

    for (int i = 0; i < graph.countVertex; i++)
    {
          visited[i] = false;
    }

    dfsUtil(graph, starting_node,visited);

}

void dfsUtil(G gg,int start, bool* vis)
{
    vis[start]=1;
    printf("%d\n",start);

    for(int i=1; i<(*(gg.adjList+start))->chainCount; i++)
    {
        if(!vis[(*(gg.adjList+start)+i)->Data])
        {
            dfsUtil(gg,(*(gg.adjList+start)+i)->Data,vis);
        }
    }
}
