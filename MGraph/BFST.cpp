#include<stdio.h>
#include <cstdlib>
#include "string.h"
#define FLASE 0
#define TRUE 1
typedef struct ArcNode{
    char adjvex[4];
    struct ArcNode *nextarc;
}ArcNode;
typedef struct VNode{
    char vexchar[4];
    ArcNode *firstarc=NULL;
}node[31];
struct mgraph{
    node vex;
    int vexnum;
    int arcnum;
}mgraph;

int LocateVex(struct mgraph G,char v1[])
{
    for (int j = 0; j < G.vexnum; ++j) {
        if(strcmp(v1,G.vex[j].vexchar)==0)
            return j;
    }
    return -1;
}
void creatDG(struct mgraph &G)
{
    ArcNode *p;
    char v1[4],v2[4];
    scanf("%d%d",&G.vexnum,&G.arcnum); //输入顶点数和弧数

    for (int i = 0; i < G.vexnum; ++i) {
        scanf("%s",G.vex[i].vexchar);
    }                                         //输入顶点数组
    int i,j;
    for(int k=0;k<G.arcnum;++k){//输入各边，构造邻接表
        scanf("%s%s",v1,v2);
        i=LocateVex(G,v1);
        //j=LocateVex(G,v2);

        if(G.vex[i].firstarc==NULL)
        {
            p=(ArcNode*) malloc(sizeof (ArcNode));
            strcpy(p->adjvex,v2);
            p->nextarc=G.vex[i].firstarc;
            G.vex[i].firstarc=p;
        }
        else
        {
            p=(ArcNode*) malloc(sizeof (ArcNode));
            strcpy(p->adjvex,v2);
            //p->nextarc=pr->nextarc;
            //pr->nextarc=p;
            p->nextarc=G.vex[i].firstarc;
            G.vex[i].firstarc=p;

        }

    }//for

}
int visited[31]={0};

void visitFunc(char v[4])
{
    printf("%s ",v);
}

void BFSTraverse(struct mgraph G,void(*visit)(char v[4]))
{
    ArcNode *p;
    for(int i=0;i<G.vexnum;i++)
        visited[i]=FLASE;
    char queue[31][4];
    int front,rear,v;
    front=rear=0;
    char u[4];
    for(v=0;v<G.vexnum;v++)
    {

        if(!visited[v])
        {
            visited[v]=TRUE;
            visit(G.vex[v].vexchar);
            {//入队
                strcpy(queue[rear],G.vex[v].vexchar);
                rear++;
            }

            while (rear!=front)
            {

                {//队头出队,赋值给u
                    strcpy(u, queue[front]);
                    front++;
                }

                for(p=G.vex[LocateVex(G,u)].firstarc;p!=NULL;p=p->nextarc)
                {

                    if(!visited[LocateVex(G,p->adjvex)])
                    {

                        visited[LocateVex(G,p->adjvex)]=TRUE;
                        visit(G.vex[LocateVex(G,p->adjvex)].vexchar);
                        {//入队
                            strcpy(queue[rear],p->adjvex);
                            rear++;
                        }

                    }
                }
            }
        }
    }

}

int main()
{

    struct mgraph G{};
    creatDG(G);

    BFSTraverse(G,visitFunc);

}