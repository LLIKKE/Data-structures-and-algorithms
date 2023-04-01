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
    int    expn;                               // 指数EXPONENT
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
/*******************************声明部分****************************************/


//构造一个空的线性链表L
Status InsFirst(LinkList &L,Link h,Link &s);
//已知h指向线性链表的头结点，将s所指结点插入在第一个结点之前
Status DelFirst(LinkList &L,Link h,Link &q);
//已知h指向线性链表的头结点，删除链表中第一个结点并以q返回
Status Append(LinkList *L,Link *s);
//将指针s所指（彼此以指针相连）的一串结点链接在线性链表L的最后一个结点
//之后，并改变链表L的尾指针指向新的尾结点
Status SetCurElem(Link p,ElemType e);
//已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
ElemType GetCurElem(Position p);
//已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
Position GetHead(polynomial &p);
//返回线性链表L中头结点的位置
Position NextPos(polynomial l,Position &p);
//直接返回p后面的结点，可能返回NULL
//Position LocateElem(LinkList L,ElemType e,Status(*compare)(ElemType,ElemType));
//返回线性链表L中第一个与e满足函数compare（）判定关系的元素的位置
Status LocateElem(LinkList L,ElemType e,Position *q,int (*cmp)(ElemType,ElemType));
//若有序链表L中存在与e满足判定函数cmp取值为0的元素，则q指示L中第一个值为e的结点的位置
//并返回TRUE，否则q指示第一个与e满足判定函数cmp取值>0的元素的前驱位置，并返回FALSE
int cmp(term a,term b);
//依a的指数值>或=或<b的指数值，分别返回-1,0，+1
Status CreatPolyn(polynomial &L,int m);
//创建一个m项的一元多项式
/*******************************函数部分****************************************/
/* 请在这里填写答案 */
Position GetHead(polynomial &p)
{return p.head;}
Position NextPos(polynomial l,Position &p)
{return p->next;}
ElemType GetCurElem(Position p)
{return p->data;}
Status cmp(term a,term b)
{
    if(a.expn > b.expn)
        return 1;
    else if(a.expn == b.expn)
        return 0;
    else
        return -1;
}
Status DelFirst(polynomial &L,Position h,Link &q)
{
    q = h->next;
    if(q) {
        h->next = q->next;
        if (!h->next)
            L.tail = h;
        L.len--;
        return OK;
    }
    return FALSE;
}
Status InsFirst(LinkList &L,Link h,Link &s)
{
//    s->next = h->next;
//    h->next = s;
//    L.len++;
//    if(h == L.tail)
//        L.tail = h->next; 似乎有点问题。。。
    //假如是空表
    //head=tail
    //head  Null        然后添加一个s head   s  Null
    //->                            ->    ->

    s->next = h->next;
    L.len++;
    if(h == L.tail)
        L.tail = s;
    h->next = s;
    return OK;
}
Status FreeNode(Link &q)
{
    free(q);
}
Status CreatePolyn(polynomial &l,int m)
{
    l.len=m;
    l.head->data.expn=0;
    l.head->data.coef=0;
    l.head->next=NULL;
    l.tail=NULL;
    int coef,expn;
    Link pr,p;
    printf("----%d----",m);
    for(int i=0;i<m;i++) {
        printf("%d",i);
        p=(Link) malloc(sizeof(LNode));
        scanf("%d%d",&coef,&expn);
        p->data.coef = coef;
        p->data.expn = expn;
        p->next = NULL;
        if(l.head->next==NULL)
            l.head->next=p;
        else
            pr->next = p;
        pr=p;
    }
    l.tail=p;
    return OK;
}
Status DestroyPolyn(polynomial &l)
{
    Position pr,p=l.head->next;
    pr=p;
    while (p) {
        free(pr);
        p = p->next;
        pr = p;
    }
    l.tail=NULL;
    l.len=0;
    return OK;
}
Status PrintPolyn(polynomial &l)
{
    Position q;
    q = l.head->next;
    printf("coef   expn\n");
    while (q)
    {
        printf("%d   %d\n",q->data.coef,q->data.expn);
        q=q->next;
    }
}
Status PolynLength(polynomial &l)
{
    return l.len;
}
Status AddPolyn(polynomial &pa,polynomial &pb)
{
    Position ha,hb,qa,qb;
    term a,b;
    ha= GetHead(pa);
    hb= GetHead(pb);
    qa= NextPos(pa,ha);
    qb= NextPos(pb,hb);

    while (qa&&qb)
    {
        a = GetCurElem(qa);
        b = GetCurElem(qb);
        switch (cmp(a,b)) {
            case -1:
                ha=qa;qa= NextPos(pa,ha);
                break;
            case 0:
                qa->data.expn+=qb->data.expn;
                printf("%d,%d",qa->data.expn,qb->data.expn);
                if(qa->data.expn==0)
                {
                    DelFirst(pa,ha,qa);
                    FreeNode(qa);
                } else
                    ha=qa;
                DelFirst(pb,hb,qb);
                FreeNode(qb);
                break;
            case 1:
                DelFirst(pb,hb,qb);
                InsFirst(pa,ha,qb);
                ha=ha->next;
                qb= NextPos(pb,hb);
        }
    }

}
//Status AddPolyn(polynomial &pa,polynomial pb)
//{
//    Link p=pa.head,q=pb.head,pr;
//    while (p)
//    {
//        while (q)
//        {
//
//            if(p->data.expn==q->data.expn)
//            {
//                p->data.coef+=q->data.coef;
//                if(p->data.coef==0) {
//                    if (p == pa.head)
//                        pa.head = p->next;
//                    else
//                        pr->next=p->next;
//                }
//
//                break;
//            }
//            q=q->next;
//        }
//        pr=p;
//        q=pb.head;
//        p=p->next;
//    }
//}

int main()
{   polynomial  Pa,Pb;
    int m,n;
    Position ha,hb,qa,qb;
    term a;
    scanf("%d",&m);
    CreatePolyn(Pa, m);

    scanf("%d",&n);
    CreatePolyn(Pb, n);
//
//    AddPolyn(Pa, Pb);
//    if(Pa.len==0) { printf("0\n"); return 0;}
//    ha=GetHead(Pa);       //ha和hb分别指向Pa和Pb的头结点
//    qa=NextPos(Pa,ha);
//    while(qa)
//    { printf("%d,%d\n",qa->data.coef,qa->data.expn);
//        ha=qa;
//        qa = NextPos(Pa,ha);
//    }
    return 0;
}

