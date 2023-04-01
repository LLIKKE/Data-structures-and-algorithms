#include <stdio.h>
#define MAXSIZE 1000
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

int LocationElem_SL(SLinkList S,ElemType e)
{
    int i;
    i=S[MAXSIZE-1].cur;
    while (i&&S[i].data!=e)
        i=S[i].cur;
    return i;
}//返回第一个值为e的下标


void difference(SLinkList &space , int &S)
{
    int m,n,b,r,k,i,j,p;
    r = S ;// 指向头结点
    scanf("%d%d",&m,&n);
    for (j = 1 ; j <= m ; j ++)
    {
        i = Malloc_Sl(space) ;
        scanf("%d",&space[i].data);
        space[r].cur  = i ;
        r = i ;
    }
    space[r].cur  = 0 ;

    for (j = 1 ; j <= n ; j ++)
    {
        scanf("%d",&b);
        p = S ;
        k = space[S].cur ;
        while (k != space[r].cur && space[k].data != b)
        {
            p = k ;
            k = space[k].cur ;//指向下一个节点
        }
        if (k == space[r].cur)
        {//集合 A 中不存在的集合 B 中的元素插入到集合 A 中
            i = Malloc_Sl(space) ;
            space[i].data = b ;
            space[i].cur  = space[r].cur ;
            space[r].cur  = i ;
        }
        else//B元素存在于A
        {
            space[p].cur = space[k].cur ;
            Free_SL(space , k) ;
            if(r == k)
            {
                r = p ;
                space[r].cur  = 0 ;
            }
        }
    }
}

int main()
{
    component space[MAXSIZE] ;
    InitSpace_SL(space) ;
    int S = Malloc_Sl(space) ;
    difference(space, S);


}
