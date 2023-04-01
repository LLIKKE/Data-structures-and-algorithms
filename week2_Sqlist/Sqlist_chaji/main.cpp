#include "Sqlist_base.cpp"
int equal(ElemType x, ElemType  y) {
    return strcmp(x, y) == 0;
}
void chaji_Sq(SqList La,SqList Lb,SqList &Lc)
{
    char e,p;
    int index;
    Lc = La;
    for(int i=1;i<=Lb.length;i++)
    {
        GetElem_Sq(Lb, i, &e);
        index = LocateElem_Sq(Lc,&e,equal);
        if (index)
            ListDelete_Sq(Lc,index,&p);
    }

}

int main()
{int i,j,len;
    ElemType e;
    SqList La,Lb,Lc;
    int m,n;   //分别存放两个集合初始长度
    printf("input the length of two set:\n");
    scanf("%d%d",&m,&n);
    InitList_Sq(La); InitList_Sq(Lb);   //建立两个空集
    printf("input the first set:\n ");
    for(i=0; i<m; i++)  //建立第一个集合
    {scanf(" %s",e);  ListInsert_Sq(La,i+1,e);  }  //注意有空格
    printf("input the second set:\n ");
    for(i=1; i<=n; i++)  //建立第二个集合
    {scanf(" %s",e);   ListInsert_Sq(Lb,i,e);  }  //注意有空格
    chaji_Sq(La,Lb,Lc);  //计算集合La、Lb的差集Lc
    printf("the chaji set is:\n");
    len=ListLength_Sq(Lc);
    for(i=1; i<=len; i++)
    {GetElem_Sq(Lc,i,e); printf("%s\n",e);  }
    DestroyList_Sq(La); DestroyList_Sq(Lb); DestroyList_Sq(Lc); //销毁3个集合（顺序表）
    return 0;
}
