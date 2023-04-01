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
Status MakeNode(Link *p, ElemType e)
{ /* 分配由p指向的值为e的结点，并返回OK；若分配失败。则返回ERROR */
    *p = (Link)malloc(sizeof(LNode));
    if (!*p)
        return ERROR;
    (*p)->data = e;
    return OK;
}

void FreeNode(Link *p)
{ /* 释放p所指结点 */
    free(*p);
    *p = NULL;
}

Status InitList(LinkList *L)
{ /* 构造一个空的线性链表 */
    Link p;
    p = (Link)malloc(sizeof(LNode)); /* 生成头结点 */
    if (p)
    {
        p->next = NULL;
        (*L).head = (*L).tail = p;
        (*L).len = 0;
        return OK;
    }
    else
        return ERROR;
}

Status ClearList(LinkList *L)
{ /* 将线性链表L重置为空表，并释放原链表的结点空间 */
    Link p, q;
    if ((*L).head != (*L).tail)/* 不是空表 */
    {
        p = q = (*L).head->next;
        (*L).head->next = NULL;
        while (p != (*L).tail)
        {
            p = q->next;
            free(q);
            q = p;
        }
        free(q);
        (*L).tail = (*L).head;
        (*L).len = 0;
    }
    return OK;
}

Status InsFirst(LinkList *L, Link h, Link s) /* 形参增加L,因为需修改L */
{ /* h指向L的一个结点，把h当做头结点，将s所指结点插入在第一个结点之前 */
    s->next = h->next;
    h->next = s;
    if (h == (*L).tail) /* h指向尾结点 */
        (*L).tail = h->next; /* 修改尾指针 */
    (*L).len++;
    return OK;
}

Status DelFirst(LinkList *L, Link h, Link *q) /* 形参增加L,因为需修改L */
{ /* h指向L的一个结点，把h当做头结点，删除链表中的第一个结点并以q返回。 */
    /* 若链表为空(h指向尾结点)，q=NULL，返回FALSE */
    *q = h->next;
    if (*q) /* 链表非空 */
    {
        h->next = (*q)->next;
        if (!h->next) /* 删除尾结点 */
            (*L).tail = h; /* 修改尾指针 */
        (*L).len--;
        return OK;
    }
    else
        return FALSE; /* 链表空 */
}

Status Append(LinkList *L, Link s)
{ /* 将指针s(s->data为第一个数据元素)所指(彼此以指针相链,以NULL结尾)的 */
    /* 一串结点链接在线性链表L的最后一个结点之后,并改变链表L的尾指针指向新 */
    /* 的尾结点 */
    int i = 1;
    (*L).tail->next = s;
    while (s->next)
    {
        s = s->next;
        i++;
    }
    (*L).tail = s;
    (*L).len += i;
    return OK;
}

Position PriorPos(LinkList L, Link p)
{ /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接前驱的位置 */
    /* 若无前驱，则返回NULL */
    Link q;
    q = L.head->next;
    if (q == p) /* 无前驱 */
        return NULL;
    else
    {
        while (q->next != p) /* q不是p的直接前驱 */
            q = q->next;
        return q;
    }
}

ElemType GetCurElem(Link p)
{ /* 已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值 */
    return p->data;
}

Status ListEmpty(LinkList L)
{ /* 若线性链表L为空表，则返回TRUE，否则返回FALSE */
    if (L.len)
        return FALSE;
    else
        return TRUE;
}
int cmp(term a, term b)
{
    if(a.expn > b.expn)
        return 1;
    else if(a.expn == b.expn)
        return 0;
    else
        return -1;
}
Position GetHead(LinkList L)
{ /* 返回线性链表L中头结点的位置 */
    return L.head;
}

Position NextPos(polynomial l,Link p)
{ /* 已知p指向线性链表L中的一个结点，返回p所指结点的直接后继的位置 */
    /* 若无后继，则返回NULL */
    return p->next;
}

Status LocateElemP(LinkList L, ElemType e, Position *q, int(*compare)(ElemType, ElemType))
{ /* 若升序链表L中存在与e满足判定函数compare()取值为0的元素，则q指示L中 */
    /* 第一个值为e的结点的位置，并返回TRUE；否则q指示第一个与e满足判定函数 */
    /* compare()取值>0的元素的前驱的位置。并返回FALSE。（用于一元多项式） */
    Link p = L.head, pp;
    do
    {
        pp = p;
        p = p->next;
    } while (p && (compare(p->data, e) < 0)); /* 没到表尾且p->data.expn<e.expn */
    if (!p || compare(p->data, e) > 0) /* 到表尾或compare(p->data,e)>0 */
    {
        *q = pp;
        return FALSE;
    }
    else /* 找到 */
    {
        *q = p;
        return TRUE;
    }
}
void CreatPolyn(polynomial *P, int m) /* 算法2.22 */
{ /* 输入m项的系数和指数，建立表示一元多项式的有序链表P */
    Position q, s;
    term e;
    int i;
    InitList(P);
    for (i = 1; i <= m; ++i)
    { /* 依次输入m个非零项（可按任意顺序） */
        scanf_s("%f,%d", &e.coef, &e.expn);
        if (!LocateElemP(*P, e, &q, cmp)) /* 当前链表中不存在该指数项,cmp是实参 */
            if (MakeNode(&s, e)) /* 生成结点并插入链表 */
                InsFirst(P, q, s);
    }
}

Status DestroyPolyn(polynomial *P)
{ /* 销毁线性链表L，L不再存在 */
    ClearList(P); /* 清空链表 */
    FreeNode(&(*P).head);
    (*P).tail = NULL;
    (*P).len = 0;
    return OK;
}

void AddPolyn(polynomial &Pa, polynomial &Pb) /* 算法2.23 */
{ /* 多项式加法:Pa=Pa+Pb,并销毁一元多项式Pb */
    Position ha, hb, qa, qb;
    term a, b;
    ha = GetHead(Pa);
    hb = GetHead(Pb); /* ha和hb分别指向Pa和Pb的头结点 */
    qa = NextPos(Pa,ha);
    qb = NextPos(Pb,hb); /* qa和qb分别指向Pa和Pb中当前结点（现为第一个结点） */
    while (qa && qb)
    { /* qa 和 qb 均为非空 */
        a = GetCurElem(qa);
        b = GetCurElem(qb); /* a和b为两表中当前比较元素 */
        switch (cmp(a, b))
        {
            case -1:ha = qa; /* 多项式Pa中当前结点的指数值小 */
                qa = NextPos(pa,ha); /* ha和qa均向后移一个结点 */
                break;
            case 0: qa->data.coef += qb->data.coef;
                /* 两者的指数值相等,修改Pa当前结点的系数值 */
                if (qa->data.coef == 0) /* 删除多项式Pa中当前结点 */
                {
                    DelFirst(Pa, ha, &qa);
                    FreeNode(&qa);
                }
                else
                    ha = qa;
                DelFirst(Pb, hb, &qb);
                FreeNode(&qb);
                qb = NextPos(hb);
                qa = NextPos(ha);
                break;
            case 1: DelFirst(Pb, hb, &qb); /* 多项式Pb中当前结点的指数值小 */
                InsFirst(Pa, ha, qb);
                ha = ha->next;
                qb = NextPos(hb);
        }
    }
    if (!ListEmpty(*Pb))
    {
        Append(Pa, qb); /* 链接Pb中剩余结点 */
    }
    DestroyPolyn(Pb); /* 销毁Pb */
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
