#include<cstdio>
#include<cstdlib>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW (-1)//返回代码-1，表示内存溢出
#define LIST_INIT_SIZE    30 //线性表存储空间的初始分配
#define LISTINCREMENT     10  //线性表存储空间的分配增量
#define Status int
typedef char ElemType[20];  // 给int型重新命名为ElemType类型
//定义数据类型
typedef  struct
{
    ElemType*   elem;    //存储空间基址
    int        length;   //当前长度
    int        listsize; //当前分配的存储容量(以sizeof(ElemType)为单位)
}SqList;
Status InitList_Sq(SqList& L);
char * GetElem_Sq(SqList L, int i, char *e);
Status ListInsert_Sq(SqList &L,int i,ElemType e);
Status LocateElem_Sq(SqList L,ElemType e, Status (*compare)(ElemType,ElemType));
Status ListDelete_Sq(SqList &L, int i, char *e);


Status InitList_Sq(SqList& L)
{
    //构造一个空的1线性表L
    L.elem = (ElemType * )malloc(LIST_INIT_SIZE * sizeof(ElemType));
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;//length是线性表的表长，属于这种数据类型的属性
    L.listsize = LIST_INIT_SIZE;//listsize表示线性表初始分配的内存空间大小
    return OK;
}//构造一个空的线性表，长度为0
char * GetElem_Sq(SqList L, int i, char *e)
{
    if(i>L.length || i<0) exit(OVERFLOW);
    strcpy(e, L.elem[i-1]);
    return e;
}//得到表中第i个元素，i是元素序号，不是下标

Status ListInsert_Sq(SqList &L,int i,ElemType e)
{
    if(i>L.length+1 || i<1) exit(ERROR); // 插入的位置不合法
    if(L.length>=L.listsize)
    {
        auto* newbase = (ElemType *) realloc(L.elem, (L.listsize + LISTINCREMENT) *
                                                     sizeof(ElemType));   //realloc返回值是新开辟内存的起始地址，若开辟失败返回null
        if(!newbase) exit(OVERFLOW);
        L.elem = newbase;
        L.listsize += LISTINCREMENT;   //当循环调用这个函数时，可以保证不会溢出
    }
    ElemType *q,*p;
    q = &(L.elem[i-1]);
    for(p = &(L.elem[L.length-1]);p>=q;--p)
        strcpy(*(p+1),*p);
    strcpy(*q,e);
    ++L.length; //长度+1，因为初始化后的长度为0；所以线性表里存放元素时要循环调用这个函数
    return OK;
}//表L中插入e，到位置i,i是序号，取值1到length+1
Status ListDelete_Sq(SqList &L, int i, char *e)
{
    if(i>L.length || i<1) exit(ERROR); // 插入的位置不合法
    ElemType *p;
    strcpy(e,L.elem[i-1]);
    for(p = &(L.elem[i-1]);p<&(L.elem[L.length-1]);++p)
        strcpy(*p,*(p+1));
    --L.length;
    return OK;
}//L中删除第i个元素，并用e返回其值
int ListLength_Sq(SqList L) {
    return L.length;
}
Status DestroyList_Sq(SqList &L) {
    if (L.elem) return ERROR;
    free(L.elem);
    L.length = 0;
    L.listsize = 0;
    return OK;
}
Status LocateElem_Sq(SqList L,ElemType e,Status (*compare)(ElemType, ElemType))
{
    int i=1;
    ElemType *p=L.elem;
    while (i<=L.length && !(*compare)(*p++,e))//在合适长度内检查每一个元素
        ++i;
    if(i<=L.length)
        return i;
    else
        return 0;
}//返回满足条件compara的第一个元素，返回序号，若没找到返回0
