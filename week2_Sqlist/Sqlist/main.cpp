#include "Sqlist_base.h"
int equal(ElemType x,ElemType y)
{
    if(x==y) return TRUE;
    else return FALSE;
}
void union_Sq(SqList La,SqList Lb,SqList &Lc)//线性表La、Lb分别表示集合A、B，C=A∪B
{
int la_len = La.length;
int lb_len = Lb.length;
Lc = La;
int e;
for(int i=1;i<=lb_len;i++)
{
    GetElem_Sq(Lb,i,e);
    if(!LocateElem_Sq(La,e,equal))
    {
//printf("%d",LocateElem_Sq(La,e,equal));
        ListInsert_Sq(Lc,++la_len,e);
}}

}

int dayv(ElemType a, ElemType b)
{
    if(a>=b) return 1;
    else return 0;
}
int youxvcharu(SqList &L, ElemType e)
{
    int locate;
    int value = -1;
    locate = LocateElem_Sq(L, e, dayv);
    if(locate)
    {
        ListInsert_Sq(L,locate-1,value);
        return 1;
    }
    else return 0;

}
typedef struct LNode
{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
void reverse(LinkList &L)
{
    if(L->next != NULL)
    {
        LinkList p = L->next;
        LinkList q;
        L->next = NULL;
        while(p != NULL)
        {
            q = p->next;
            p->next = L->next;
            L->next = p;
            p = q;
        }
    }
}


int main()
{
    SqList La,Lb,Lc;
    InitList_Sq(La);
    InitList_Sq(Lb);
    InitList_Sq(Lc);
    int n,m,e;
    scanf("%d",&n);
    scanf("%d",&m);
    for(int i=1;i<=n;i++)
    {scanf("%d",&e);
        ListInsert_Sq(La,i,e);}
    for(int i=1;i<=m;i++)
    {scanf("%d",&e);
        ListInsert_Sq(Lb,i,e);}
    union_Sq(La,Lb,Lc);
    for(int i=0;i<Lc.length;i++)
        printf("%4d",Lc.elem[i]);
    return 0;
}


