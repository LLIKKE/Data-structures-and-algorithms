//已知二叉树的先序序列，判断结点u是否是结点v的子孙，是就输出v到u的路径长度，否则输出NO。假设结点个数少于50个。
//
//输入格式:
//输入共二行，第一行中给出先序序列，第二行给出两个顶点。*表示空树。
//
//输出格式:
//输出一个整数或NO。
//
//输入样例1:
//ABC**DE*G**F***
//BE
//输出样例1:
//2
//输入样例2:
//ABC**DE*G**F***
//CE
//输出样例1:
//NO
#include "stdio.h"
#include "cstdlib"
#include "bitree.cpp"
int main()
{
    BiTree T,t1,t2;
    TElemType c1,c2;
    int h;
    CreateBiTree(T);
    getchar();//注意取掉这个换行符
    c1=getchar();
    t1 = ziTree(T,c1);
    c2=getchar();
    t2= ziTree(t1,c2);

    if(t1&&t2)
    {
        h=TreeHight(t1)-TreeHight(t2);
        printf("%d",h);

    }
    else
        printf("NO\n");
    return 0;
}