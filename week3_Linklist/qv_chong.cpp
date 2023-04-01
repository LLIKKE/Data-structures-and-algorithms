#include <stdio.h>
#define MAXSIZE 10000
typedef int ElemType;
typedef struct
{
    ElemType data;
    int cur;
}component,SLinkList[MAXSIZE];

void InitSpace_SL(SLinkList &space)
{
    int i;
    for(i=0;i<MAXSIZE-1;++i)
        space[i].cur=i+1;
    space[MAXSIZE-1].cur=0;
}
// 初始化 全为空，下标0的cur指向第一个空元素即下标1，尾端指向第一个有数据的下标(空链表是0)
// cur      1   2   3   4   5      0
//data   kong   k   k   k   k   ...k
//xia_biao  0   1   2   3   4     999
int Malloc_Sl(SLinkList &space)
{
    int i;
    i=space[0].cur;
    if(space[0].cur)
        space[0].cur=space[i].cur;
    return i;
}//返回第一个空结点的下标，并且让下标0的cur往前进一位
void Free_SL(SLinkList &space,int k)
{
    space[k].cur = space[0].cur;
    space[0].cur = k;
}
// 先让下标k指向头结点指向的cur，让头结点的cur指向下标k，这样就释放了一个新结点
int main()
{
    SLinkList a;
    InitSpace_SL(a) ;
    int n,ip_head;
    scanf("%d",ip_head);
    scanf("%d",n);
}
