
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#define V 5
#include<stdio.h>
#define MAX 30

int minKey(int key[], bool mstSet[])
{

    int min = INT_MAX, min_index;
    int v;
    for ( v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v], min_index = v;
        }
    return min_index;
}

int printMST(int parent[], int graph[V][V])
{
    printf("Edge \tWeight\n");
    int i;
    for ( i = 1; i < V; i++)
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}
int printMST2(int parent[],int p[])
{

    int i;
    for ( i = 0; i < V; i++)
        printf("%d\t", parent[i]);
    printf("\n");
    for ( i = 0; i < V; i++)
    {
        if(p[i]==true)
            printf("\ttrue ");
        else
            printf("\tfalse");
    }
}

void primMST(int graph[V][V])
{

    int parent[V];
    int key[V];
    bool mstSet[V];
    int i,count,v;

    for ( i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    key[0] = 0;
    parent[0] = -1;

    printf("prim Algo:\n\n");
    for ( count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet);

        mstSet[u] = true;

        for ( v = 0; v < V; v++)

            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }


    printMST(parent, graph);
}


typedef struct edge
{
    int u,v,w;
} edge;

typedef struct edgelist
{
    edge data[MAX];
    int n;
} edgelist;

edgelist elist;

int G[MAX][MAX],n;
edgelist spanlist;

void kruskal()
{
    int belongs[MAX],i,j,cno1,cno2;
    elist.n=0;

    for(i=1; i<n; i++)
        for(j=0; j<i; j++)
        {
            if(G[i][j]!=0)
            {
                elist.data[elist.n].u=j;
                elist.data[elist.n].v=i;
                elist.data[elist.n].w=G[j][i];
                elist.n++;
            }
        }

    sort();
    printf("\nkruskal Algo:\n");
    for(i=0; i<n; i++)
        belongs[i]=i;

    spanlist.n=0;

    for(i=0; i<elist.n; i++)
    {
        cno1=find(belongs,elist.data[i].u);
        cno2=find(belongs,elist.data[i].v);

        if(cno1!=cno2)
        {
            spanlist.data[spanlist.n]=elist.data[i];
            spanlist.n=spanlist.n+1;
            union1(belongs,cno1,cno2);

        }
    }
}

int find(int belongs[],int vertexno)
{
    return(belongs[vertexno]);
}

void union1(int belongs[],int c1,int c2)
{
    int i;

    for(i=0; i<n; i++)
        if(belongs[i]==c2)
            belongs[i]=c1;
}

void sort()
{
    int i,j;
    edge temp;

    for(i=1; i<elist.n; i++)
        for(j=0; j<elist.n-1; j++)
            if(elist.data[j].w>elist.data[j+1].w)
            {
                temp=elist.data[j];
                elist.data[j]=elist.data[j+1];
                elist.data[j+1]=temp;
            }
}

void print()
{
    int i,cost=0;
printf("\nEdge \tWeight\n");
    for(i=0; i<spanlist.n; i++)
    {
        printf("\n%d - %d   %d",spanlist.data[i].u,spanlist.data[i].v,spanlist.data[i].w);
        cost=cost+spanlist.data[i].w;
    }

    printf("\n\nCost of the spanning tree=%d",cost);
}

int pri(int parent[])
{

    int i;
    for ( i = 0; i < V; i++)
        printf("%d\t", parent[i]);
    printf("\n");

}
int prin()
{

    int i;
    for ( i = 0; i < elist.n; i++)
        printf("%d-%d--%d\t", elist.data[i].u,elist.data[i].v,elist.data[i].w);
    printf("\n");

}

int main()
{
    int graph[V][V] = { { 0, 2, 0, 0, 0 },
        { 2, 0, 5, 4, 0 },
        { 0, 5, 0, 0, 0 },
        { 0, 4, 0, 0, 3 },
        { 0, 0, 0, 3, 0 }
    };

    // Print the solution
    primMST(graph);


    int i,j,total_cost;

    n=5;



    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            G[i][j]=graph[i][j];

    kruskal();
    print();

    return 0;
}
