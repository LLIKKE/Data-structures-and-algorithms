#include<stdio.h>
#include <cstdlib>
#include "limits.h"// 这个头文件包含无穷大的int型：INT_MAX 这个常量
#define OK 1
#define FLASE 0
#define TRUE 1
#define ERROR 0
#define OVERFLOW -2
#define NOT_FIND -1
typedef int status;
#define INFINITY INT_MAX // c语言中的无穷大常量
#define MAX_VERTEX_NUM 20
typedef char VertexType;
typedef int VRType;
typedef int InfoType;
typedef enum {UDG=1,UDN,DN,DG} GraphKind;
typedef struct ArcCell{//邻接矩阵中每一个位置的点信息
    VRType adj; // 无权图：0,1表示是否相邻；带权图：为权值大小
    InfoType *info;// 表示这条弧的信息，这个信息是什么还挺灵活的。。。
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //
typedef struct {
    VertexType vexs[MAX_VERTEX_NUM];    //顶点向量（一维数组）
    AdjMatrix arcs;     //邻接矩阵 （二维数组）
    int vexnum,arcnum;  //当前定点数和弧数
    GraphKind kind;     //图的种类
} MGraph;
status CreatGraph(MGraph &G);
status createUDN(MGraph &G);  //创建无向网（带权值的无向图）UDN
status createUDG(MGraph &G); //c创建无向图
status createDN(MGraph &G);
status createDG(MGraph &G);
status Locatevex(MGraph G,VertexType v);//返回顶点v的位置，若没找到返回-1
status DestroyGraph(MGraph &G);
status FirstAdjVex(MGraph G,VertexType v);
status NextAdjVex(MGraph G,VertexType v,VertexType w);
status DeleteVex(MGraph &G,VertexType v);
status InsertVex(MGraph &G,VertexType v);
status InsertArc(MGraph &G,VertexType v,VertexType w);
status InsertArc(MGraph &G,VertexType v,VertexType w);

status Locatevex(MGraph G,VertexType v) //查找顶点向量中的**同名**顶点，仅同名
{
    int i;
    for(i=0;i<G.vexnum&&G.vexs[i]!=v;i++)
        return i;
    return NOT_FIND;
}
status CreatGraph(MGraph &G)
{
    GraphKind Kind;
    scanf("%d",&Kind);
    switch(Kind)
    {
        case 1:
            createUDG(G);
            break;
        case 2:
            createUDN(G);
            break;
        case 3:
            createDG(G);
            break;
        case 4:
            createDN(G);
            break;
    }
    return OK;
}
status createUDN(MGraph &G) // 带权值的无向图
{
    // 输入
    //第一行: 顶点个数 边的数量 每个顶点是否包含其他信息（0或1）
    //第二行：顶点v1 顶点v2 弧的权值
    int IncInfo;
    scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);//IncInfo表示有无弧上信息，为0时没有任何信息？？？？
    int i,j;
    for(i=0;i<G.vexnum;i++)
        scanf("%c",&G.vexs[i]);// 输入顶点数组
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j]={INFINITY,NULL};//邻接矩阵初始化
        }
    for(i=0;i<G.vexnum;i++)
    {
        VertexType v1,v2;
        InfoType w;// 代表输入的权值信息
        scanf("%c %c %d",&v1,&v2,&w);
        int l1=Locatevex(G,v1);
        int l2=Locatevex(G,v2);
        if(l1==-1||l2==-1)
            exit(OVERFLOW);
        G.arcs[l1][l2].adj = w; //表示可以从l1到l2且两点间距离为w
        if(IncInfo)
        {
            *(G.arcs[l1][l2].info)=IncInfo; // ？？怪怪的?，为什么不能用"->"???
        }
        G.arcs[l2][l1]=G.arcs[l1][l2];// 双向图是对称矩阵
    }
    G.kind = UDN;
    return OK;
}
status createUDG(MGraph &G) // 不带权值的无向图
{
    int IncInfo;
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
    int i, j;
    for (i = 0; i < G.vexnum; i++)
        scanf("%c", &G.vexs[i]);
    for (j = 0; j < G.vexnum; j++)
        for (i = 0; i < G.vexnum; i++)
            G.arcs[i][j] = {0, NULL};// 初始化为不相同
    for(i=0;i<G.vexnum;i++) {
        VertexType v1, v2;
        scanf("%c %c",&v1,&v2);
        int l1 = Locatevex(G,v1);
        int l2 = Locatevex(G,v2);
        if(l1==-1||l2==-1)
            exit(OVERFLOW);
        G.arcs[l1][l2].adj = 1;// 表示链接，0表示不连接
        if(IncInfo)
        {
            *(G.arcs[l1][l2].info)=IncInfo; // ？？怪怪的?，为什么不能用"->"???
        }
        G.arcs[l2][l1]=G.arcs[l1][l2];// 双向图是对称矩阵
    }
    G.kind = UDG;
    return OK;
}
status createDN(MGraph &G)
{
    int IncInfo;
    scanf("%d %d %d",&G.vexnum,&G.arcnum,&IncInfo);//IncInfo表示有无弧上信息，为0时没有任何信息？？？？
    int i,j;
    for(i=0;i<G.vexnum;i++)
        scanf("%c",&G.vexs[i]);// 输入顶点数组
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j]={INFINITY,NULL};//邻接矩阵初始化
        }
    for(i=0;i<G.vexnum;i++)
    {
        VertexType v1,v2;
        InfoType w;// 代表输入的权值信息
        scanf("%c %c %d",&v1,&v2,&w);
        int l1=Locatevex(G,v1);
        int l2=Locatevex(G,v2);
        if(l1==-1||l2==-1)
            exit(OVERFLOW);
        G.arcs[l1][l2].adj = w; //表示可以从l1到l2且两点间距离为w
        if(IncInfo)
        {
            *(G.arcs[l1][l2].info)=IncInfo; // ？？怪怪的?，为什么不能用"->"???
        }
    }
    G.kind = DN;
    return OK;
}
status createDG(MGraph &G)
{
    int IncInfo;
    scanf("%d %d %d", &G.vexnum, &G.arcnum, &IncInfo);
    int i, j;
    for (i = 0; i < G.vexnum; i++)
        scanf("%c", &G.vexs[i]);
    for (j = 0; j < G.vexnum; j++)
        for (i = 0; i < G.vexnum; i++)
            G.arcs[i][j] = {0, NULL};// 初始化为不相同
    for(i=0;i<G.vexnum;i++) {
        VertexType v1, v2;
        scanf("%c %c",&v1,&v2);
        int l1 = Locatevex(G,v1);
        int l2 = Locatevex(G,v2);
        if(l1==-1||l2==-1)
            exit(OVERFLOW);
        G.arcs[l1][l2].adj = 1;// 表示链接，0表示不连接
        if(IncInfo)
        {
            *(G.arcs[l1][l2].info)=IncInfo; // ？？怪怪的?，为什么不能用"->"???
        }
    }
    G.kind = DG;
    return OK;
}
status DestroyGraph(MGraph &G)
{ // 初始条件: 图G存在。操作结果: 销毁无向图G
    int i,j;
    for(i=0;i<G.vexnum;i++)
        for(j=0;j<G.vexnum;j++)
        {
            G.arcs[i][j] = {INFINITY,NULL};
        }
    G.vexnum=0;
    G.arcnum=0;// ??? 怎么感觉像clear？？？
    return OK;
}
status PutVex(MGraph &G,VertexType v,VertexType value)
{ // 初始条件: 图G存在，v是G中某个顶点。操作结果: 对v赋新值value(仅是给顶点新起一个名)
    int k;
    k= Locatevex(G,v);
    if(k<0)
        return ERROR;
    G.vexs[k]=value;
    return OK;
}
status FirstAdjVex(MGraph G,VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点
    // 操作结果: 返回v的第一个邻接顶点的序号。若顶点在G中没有邻接顶点,则返回-1(顶点v的第一个出度)
    int i,j=0,index;
    index= Locatevex(G,v);
    for(i=0;i<G.vexnum;i++)
        if(G.arcs[index][i].adj==1)
            break;
    if(i==G.vexnum)
        return NOT_FIND;
    else
        return i;   //emmm... 应该从1开始数的。。不然没法返回ERROR了。。。
}

status NextAdjVex(MGraph G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v是G中某个顶点,w是v的邻接顶点
    // 操作结果: 返回v的(相对于w的)下一个邻接顶点的序号,
    //           若w是v的最后一个邻接顶点,则返回-1，返回v的w之后的出度
    int i,j=0,index1,index2;
    index1 = Locatevex(G,v);
    index2 = Locatevex(G,w);
    for(i=index2+1;i<G.vexnum;i++)
        if(G.arcs[index1][i].adj==1)
            return i;
    return -1;
}
status InsertVex(MGraph &G,VertexType v)
{ // 初始条件: 图G存在,v和图G中顶点有相同特征
    // 操作结果: 在图G中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做)
    int i;
    //strcpy(&G.vexs[G.vexnum],&v); // 构造新顶点向量
    G.vexs[G.vexnum] = v;
    G.vexs[G.vexnum+1] = '\0';
    if(G.kind==UDN||G.kind==DN)
        for(i=0;i<=G.vexnum;i++)
        {
            G.arcs[G.vexnum][i].adj=INFINITY; // 初始化该行邻接矩阵的值(无边或弧)
            G.arcs[i][G.vexnum].adj=INFINITY; // 初始化该列邻接矩阵的值(无边或弧)
        }
    else
        for(i=0;i<=G.vexnum;i++)
        {
            G.arcs[G.vexnum][i].adj=0; // 初始化该行邻接矩阵的值(无边或弧)
            G.arcs[i][G.vexnum].adj=0; // 初始化该列邻接矩阵的值(无边或弧)
        }
    G.vexnum++;//图G的顶点数加1
    return OK;
}
status DeleteVex(MGraph &G,VertexType v)
{ // 初始条件: 图G存在,v是G中某个顶点。操作结果: 删除G中顶点v及其相关的弧
    int i,j,k;
    k=Locatevex(G,v); // k为待删除顶点v的序号
    if(k<0) // v不是图G的顶点
        return ERROR;
    if(G.kind==UDG||G.kind==UDN) {// 如果是无向图和网，修改边数,只需要修改矩阵的一侧
        for (j = 0; j < G.vexnum; j++)
            if (G.arcs[j][k].adj != 0) // 有边
                G.arcnum--;// 修改边数
    }
    else{// 若有向图修改变数，需要修改矩阵的两侧（出度和入度）
        for (i = 0; i < G.vexnum; ++i)
        {
            if(G.arcs[i][k].adj!=0)
                G.arcnum--;
            if(G.arcs[k][i].adj!=0)
                G.arcnum--;
        }
    }
    for(j=k+1;j<G.vexnum;j++) // 序号k后面的顶点向量依次前移
        G.vexs[j-1]=G.vexs[j];
    for(i=0;i<G.vexnum;i++)
        for(j=k+1;j<G.vexnum;j++)
            G.arcs[i][j-1]=G.arcs[i][j]; // 移动待删除顶点之后的矩阵元素,移动列
    for(i=0;i<G.vexnum;i++)
        for(j=k+1;j<G.vexnum;j++)
            G.arcs[j-1][i]=G.arcs[j][i]; // 移动待删除顶点之下的矩阵元素，移动行

    G.vexnum--;// 更新图的顶点数
    return OK;
}
status InsertArc(MGraph &G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v和W是G中两个顶点
    // 操作结果: 在G中增添弧<v,w>,若G是无向的,则还增添对称弧<w,v>
    int i,l,v1,w1;
    v1= Locatevex(G,v);     // 尾
    w1= Locatevex(G,w);     // 头
    if(v1<0||w1<0)
        return ERROR;

    if(G.kind==UDG)
    {
        G.arcs[v1][w1].adj=1;
        G.arcs[w1][v1].adj=1;
        G.arcnum+=2;
    }
    else if(G.kind==UDN)
    {
        int w;
        scanf("%d",&w);
        G.arcs[v1][w1].adj=w;
        G.arcs[w1][v1].adj=w;
        G.arcnum+=2;
    } else if(G.kind==DG)
    {
        G.arcs[v1][w1].adj=1;
        G.arcnum++;
    } else if(G.kind==DN)
    {
        int w;
        scanf("%d",&w);
        G.arcs[v1][w1].adj=w;
        G.arcnum++;
    }
    return OK;
}
status DeleteArc(MGraph &G,VertexType v,VertexType w)
{ // 初始条件: 图G存在,v和w是G中两个顶点
    // 操作结果: 在G中删除弧<v,w>,若G是无向的,则还删除对称弧<w,v>
    int v1,w1;
    v1= Locatevex(G,v);     // 尾
    w1= Locatevex(G,w);     // 头
    if(v1<0||w1<0) // v1、w1的值不合法
        return ERROR;
    if(G.kind==UDG)
    {
        G.arcs[v1][w1].adj=0;
        G.arcs[w1][v1].adj=0;
        G.arcnum-=2;
    }
    else if(G.kind==UDN)
    {
        G.arcs[v1][w1].adj=INFINITY;
        G.arcs[w1][v1].adj=INFINITY;
        G.arcnum-=2;
    } else if(G.kind==DG)
    {
        G.arcs[v1][w1].adj=0;
        G.arcnum--;
    } else if(G.kind==DN)
    {
        G.arcs[v1][w1].adj=INFINITY;
        G.arcnum--;
    }
    return OK;
}