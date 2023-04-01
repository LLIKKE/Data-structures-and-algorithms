//已知先序序列，建立一棵二叉树，输出后序遍历序列，并计算这棵二叉树的高度。
//
//输入格式:
//输入在一行中给出二叉树的先序序列。*表示空格
//
//输出格式:
//输出共二行，第一行是二叉树的后序遍历序列，第二行是二叉树的高度。
//
//输入样例:
//ABC**DE*G**F***
//输出样例:
//CGEFDBA
//5
#include "stdio.h"
#include "cstdlib"
#include "bitree.cpp"

int PrintElement(TElemType e)
{
    printf("%c",e);
    return OK;
};
int main()
{
    BiTree T;
    int h;
    CreateBiTree(T);
    PostOrderTraverse(T,PrintElement);
    h=TreeHight(T);
    printf("\n%d",h);
}