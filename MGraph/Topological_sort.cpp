#include<stdio.h>
#include <cstdlib>
#include "string.h"
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

void FindInDegree(struct mgraph G,int indegree[])
{
    ArcNode *p;
    for(int i=0;i<G.vexnum;i++)
    {
        p=G.vex[i].firstarc;
        for(;p;p=p->nextarc)
        {
            //printf("%d",LocateVex(G,p->adjvex));
            indegree[LocateVex(G,p->adjvex)]++;
        }
    }
}
int TopologicalSort(struct mgraph G)
{
    ArcNode *p;
    int indegree[31]={0};
    FindInDegree(G,indegree);

    int stack[31]={0};
    int top=0,base=0,count=0,Vindex=0;
    int line[31]={0},t=0;
    for(int i=0;i<G.vexnum;i++)
    {
        if(!indegree[i])
        {//入栈

            stack[top]=i;
            top++;
        }
    }

    while (top!=base)
    {

        {//打印并出栈
            Vindex = LocateVex(G,G.vex[stack[top-1]].vexchar);
            //printf("%s ",G.vex[stack[top-1]].vexchar);
            line[t++]=Vindex;
            top--;
            count++;//出栈点计数
        }

        for(p=G.vex[Vindex].firstarc;p;p=p->nextarc)
        {

            int k= LocateVex(G,p->adjvex);
            --indegree[k];
            if(!(indegree[k]))
            {//入栈
                stack[top++]=k;
            }
        }
    }

    if(count<G.vexnum)
    {
        printf("ERROR");
        return 0;
    } else{
        for (int i = 0; i < t; ++i) {
            printf("%s ",G.vex[line[i]].vexchar);
        }
        return 1;
    }


}
int main()
{
    struct mgraph G{};
    creatDG(G);
    TopologicalSort(G);

}