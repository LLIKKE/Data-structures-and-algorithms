#include<stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define  OK  1
#define  ERROR  -1
#define  OVERFLOW -2
typedef int Status;

typedef struct
{ //项的表示,多项式的项作为LinkList的数据元素
    int    coef;                                 // 系数COEFFICIENT
    int       expn;                               // 指数EXPONENT
}term, ElemType;

typedef struct LNode                             //结点类型
{ ElemType         data;
    struct LNode    *next;
} *Link, *Position;
typedef  struct                                                //链表类型
{Link  head, tail;    //分别指向线性链表中的头结点和最后一个结点
    int   len;                       //指向线性链表中数据元素的个数
}LinkList;
typedef  LinkList  polynomial;   //用带表头结点的有序链表表示多项式

/* 请在这里填写答案 */
int cmp(term a,term b)
{

    if(a.expn > b.expn)
        return 1;
    else if(a.expn == b.expn)
        return 0;
    else
        return -1;
}
Status DelFirst(LinkList &L,Link h,Link &q)
{
    Link p;

    q = h->next;
    h->next = q->next;
    if(!h->next)
        L.tail = h;
    L.len--;
    return OK;
}
Status ListEmpty(LinkList L)
{
    return (L.len == 0);
}
Status Append(LinkList L,Link s)
{
    int i = 0;
    L.tail->next = s;
    while(s){
        s = s->next;
        i++;
    }
    L.tail = s;
    L.len += i;
}

Status InsFirst(LinkList L,Link h,Link s)
{
    s->next = h->next;
    h->next = s;
    L.len++;
    if(h == L.tail)
        L.tail = h->next;
    return OK;
}

Status SetCurElem(Link p,ElemType e)
{
    p->data = e;
    return OK;
}
void FreeNode(Link &p)
{
    p = NULL;
    free(p);
}
ElemType GetCurElem(Link p)
{
    return p->data;
}
Status CreatePolyn(polynomial& l,int m)
{
    l.len=m;
    l.head=NULL;
    l.tail=NULL;
    int coef,expn;
    Link pr,p;
    for(int i=0;i<m;i++) {
        p=(Link) malloc(sizeof(LNode));
        scanf("%d%d",&coef,&expn);
        p->data.coef = coef;
        p->data.expn = expn;
        p->next = NULL;
        if(l.head==NULL)
            l.head=p;
        else
            pr->next = p;
        pr=p;
    }
    l.tail=p;
    return OK;
}
Position GetHead(LinkList L)
{
    return L.head;
}

Position NextPos(LinkList L,Link p)
{
    return p->next;
}
void AddPolyn(polynomial &Pa,polynomial &Pb)
{
    Link ha,hb,qa,qb;
    term a,b;
    int sum;

    ha = GetHead(Pa);
    hb = GetHead(Pb);
    qa = NextPos(Pa,ha);
    qb = NextPos(Pb,hb);

    while(qa && qb){
        a = GetCurElem(qa);
        b = GetCurElem(qb);

        switch(cmp(a,b))
        {
            case -1:
                ha = qa;
                qa = NextPos(Pa,qa);
                break;
            case 0:
                sum = a.coef+b.coef;
                if(sum != 0.0){
                    qa->data.coef = sum;
                    SetCurElem(qa,qa->data);
                    ha = qa;
                }//if
                else{
                    DelFirst(Pa,ha,qa);
                    FreeNode(qa);
                }
                DelFirst(Pb,hb,qb);
                FreeNode(qb);
                qb = NextPos(Pb,hb);
                qa = NextPos(Pa,ha);
                break;
            case 1:
                DelFirst(Pb,hb,qb);
                InsFirst(Pa,ha,qb);
                qb = NextPos(Pb,hb);
                ha = NextPos(Pa,ha);
                break;
        }//switch
    }//while
    if(!ListEmpty(Pb))
        Append(Pa,qb);
    FreeNode(hb);
}
int main()
{  polynomial  Pa,Pb;
    int m,n;
    Position ha,hb,qa,qb;
    term a;
    scanf("%d",&m);
    CreatePolyn(Pa, m);
    scanf("%d",&n);
    CreatePolyn(Pb, n);
    AddPolyn (Pa, Pb);
    if(Pa.len==0) { printf("0\n"); return 0;}
    ha=GetHead(Pa);       //ha和hb分别指向Pa和Pb的头结点
    qa=NextPos(Pa,ha);
    while(qa)
    { printf("%d,%d\n",qa->data.coef,qa->data.expn);
        ha=qa;
        qa = NextPos(Pa,ha);
    }
    return 0;
}
