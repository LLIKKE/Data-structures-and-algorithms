#ifndef SQLIST_SQLIST_BASE_H
#define SQLIST_SQLIST_BASE_H

#include<cstdio>
#include<cstdlib>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW (-1)//返回代码-1，表示内存溢出
#define LIST_INIT_SIZE    30 //线性表存储空间的初始分配
#define LISTINCREMENT     10  //线性表存储空间的分配增量
#define Status int
typedef int ElemType;  // 给nt型重新命名为ElemType类型
//定义数据类型
typedef  struct
{
    ElemType*   elem;    //存储空间基址
    int        length;   //当前长度
    int        listsize; //当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;
Status InitList_Sq(SqList& L);
Status DestroyList_Sq(SqList& L);
Status ClearList_Sq(SqList& L);
Status ListEmpty_Sq(SqList& L);
Status ListLength_Sq(SqList L);
Status GetElem_Sq(SqList L,int i, ElemType &e);
Status PriorElem_Sq(SqList L,int cur_e,int &pre_e);
Status NextElem_Sq(SqList L,int cur_e,int &next_e);
Status ListInsert_Sq(SqList &L,int i,ElemType e);
Status LocateElem_Sq(SqList L,ElemType e, Status (*compare)(ElemType,ElemType));
Status ListDelet_Sq(SqList L,int i,ElemType& e);

//Status ListTraverse_Sq(SqList L,);
int equal(ElemType x,ElemType  y);   //比较x与y是否相等


#endif //SQLIST_SQLIST_BASE_H
