#include<stdio.h>
#include <stdlib.h>
#define OK 1;
#define ERROR 0;
typedef int Status;
typedef  char ElemType;
typedef  struct  LNode
{  ElemType       data;
    struct  LNode  *next;
}LNode, *LinkList;

Status InitList(LinkList &L)
{
    L = (LinkList) malloc(sizeof(LNode));
    L->data=' ';
    L->next=NULL;
    return OK;
}
Status ListInsert(LinkList &L,int i,ElemType e)
{
    LinkList p=L,s;

    int j=0;
    while (p&&j<i-1)
    {
        p=p->next;
        j++;
    }//p指i-1个节点
    if(!p||j>i-1)
        return ERROR;
    s=(LinkList) malloc(sizeof (LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return OK;
}
Status ListLength(LinkList L)
{
    int j=0;
    LinkList q=L->next;
    while (q)
    {
        q=q->next;
        j++;
    }
    return j;
}
Status GetElem(LinkList L,int i,ElemType &e)
{
    int j=1;
    LinkList p=L->next;
    while (p&&j<i)
    {
        p = p->next;
        j++;
    }
    if(!p||j>i)
        return ERROR;
    e = p->data;
    return OK;
}//get函数可以写j=1,因为获得直接获得第一个元素，不用得到第i-1个元素
Status DestroyList(LinkList &L)
{
    LinkList q;
    while (L)
    {
        q=L->next;
        free(L);
        L=q;
    }
    return OK;
}
Status ListDelete_L(LinkList &L,int i,ElemType &e)
{
    LinkList p,q;
    int j=0;
    p=L;
    while (p&&j<i-1)
    {
        p=p->next;
        ++j;
    }
    if(!(p->next)||j>i-1)
        return ERROR;
    q=p->next;
    p->next = q->next;
    e = q->data;
    free(q);
    return OK;
}//Delete要写成j=0,因为你要获得第i-1个元素
