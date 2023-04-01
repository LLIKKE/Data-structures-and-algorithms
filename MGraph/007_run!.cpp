#include<stdio.h>
#include <cstdlib>
#include <cmath>
struct mgraph{
    int vexnum;
    char vexs[102];
    int adjmatrix[102][102]={0};
}mgraph;
struct point{
    int x;
    int y;
};

int visited[102]={0};
struct point Point[102];
int flage=0;
float skip;
float distance(int x1,int y1,int x2,int y2)
{
    int x= pow(x1-x2,2),y= pow(y1-y2,2);
    return pow(x+y,0.5);
}
int saved_or_not(int i)
{
    if(abs(abs(Point[i].x)- 50)<=skip||abs(abs(Point[i].y)- 50)<=skip)
        return 1;
    else
        return 0;
}
int FirstAdjvex(struct mgraph G,int v)
{
    int i;
    for (i = 0; i < G.vexnum; ++i) {
        if(G.adjmatrix[v][i]==1)
            return i;
    }
    return -1;
}
int Nextadjvex(struct mgraph G,int v,int w)
{
    for (int i = w+1; i < G.vexnum; ++i) {
        if(G.adjmatrix[v][i]==1)
            return i;
    }
    return -1;
}

void DFS(struct mgraph G,int i)
{
    int w;
    visited[i]=1;
    if(saved_or_not(i))
        flage = 1;
    for ( w = FirstAdjvex(G,i);w>=0;w = Nextadjvex(G,i,w))
    {
        if(!visited[w])
            DFS(G,w);
    }
}
//  ******此问题的关键*****
//void DFST(struct mgraph G)
//{
//    int v;
//    for(v=0;v<G.vexnum;++v)
//        if(!visited[v])
//            DFS(G,v);
//如果图不连续，像 a       这种的话，可能从d开始遍历能到达岸边，但是无法从中心岛（a位置）到达d，导致出错
//            /
//           b —— c
//           d —— e
void DFST(struct mgraph G)
{
    int v=0;
    DFS(G,v);
}

int main()
{
    struct mgraph G{};
    scanf("%d",&G.vexnum);

    scanf("%f",&skip);
    G.vexnum++;//s算上中心岛

    Point[0].x=0,Point[0].y=0;
    for (int i = 1; i < G.vexnum; ++i) {
        scanf("%d %d",&Point[i].x,&Point[i].y);
    }

    for (int i = 0; i < G.vexnum; ++i) {
        for (int j = i+1; j < G.vexnum; ++j) {
            if(i==0)
            {
                if((distance(0,0,Point[j].x,Point[j].y)-7.5)<=skip)
                {G.adjmatrix[i][j]=1;
                    G.adjmatrix[j][i]=1;}
            }
            else
            {
                if(distance(Point[i].x,Point[i].y,Point[j].x,Point[j].y)<=skip)
                {G.adjmatrix[i][j]=1;
                    G.adjmatrix[j][i]=1;}
            }

        }

    }
    DFST(G);
    if(flage)
        printf("Yes");
    else
        printf("No");
    return 0;
}