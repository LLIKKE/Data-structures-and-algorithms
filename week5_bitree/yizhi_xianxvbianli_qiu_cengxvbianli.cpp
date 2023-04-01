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
    LevelOrderTraverse(T,PrintElement);
}