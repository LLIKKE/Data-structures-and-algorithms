//无向图(网)采用邻接矩阵结构。假设总是从第一个顶点出发遍历。顶点个数不超过30个。
//
//输入格式:
//输入共3部分，依次给出图中顶点的个数、顶点信息和邻接矩阵。
//
//输出格式:
//输出是遍历序列，用“%s ”输出一个顶点（包含一个空格）。
//
//输入样例:
//8
//v1
//v2
//v3
//v4
//v5
//v6
//v7
//v8
//0 1 1 0 0 0 0 0
//1 0 0 1 1 0 0 0
//1 0 0 0 0 1 1 0
//0 1 0 0 0 0 0 1
//0 1 0 0 0 0 0 1
//0 0 1 0 0 0 1 0
//0 0 1 0 0 1 0 0
//0 0 0 1 1 0 0 0
//输出样例:
//v1 v2 v4 v8 v5 v3 v6 v7
//
#include<stdio.h>
#include <cstdlib>
struct mgraph{
    int vexnum;
    char vexs[31][4];
    int adjmatrix[31][31];
}mgraph;

int visited[31]={0};
int FirstAdjvex(struct mgraph G,int v)
{
    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if(G.adjmatrix[v][i]!=0)
            return i;
    }
    return -1;
}
int Nextadjvex(struct mgraph G,int v,int w)
{
    for (int i = w+1; i < G.vexnum; ++i) {
        if(G.adjmatrix[v][i]!=0)
            return i;
    }
    return -1;
}
void visitFunc(int i,char v[4])
{
    printf("%s ",v);
}
void DFS(struct mgraph G,int i)
{
    int w;
    visited[i]=1;
    visitFunc(i,G.vexs[i]);
    for ( w = FirstAdjvex(G,i);w>=0;w = Nextadjvex(G,i,w))
    {
        if(!visited[w])
            DFS(G,w);
    }
}
void DFST(struct mgraph G)
{
    int v;
    for(v=0;v<G.vexnum;++v)
        if(!visited[v])
            DFS(G,v);
}

int main()
{
    struct mgraph G{};
    scanf("%d",&G.vexnum);
    for (int i = 0; i < G.vexnum; ++i) {
        scanf("%s", G.vexs[i]);
    }
    for (int i = 0; i < G.vexnum; ++i)
        for (int j = 0; j < G.vexnum; ++j) {
            scanf("%d",&G.adjmatrix[i][j]);
        }
    DFST(G);
}