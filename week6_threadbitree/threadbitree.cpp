//线索二叉树
// 创建有*****头结点*****的线索二叉树
#include <cstdio>
#include <cstdlib>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char TElemType;
typedef int Status;
typedef enum {link,thread} PointerTag;
typedef struct BiThrNode
{
    TElemType data;
    struct BiThrNode *lchild,*rchild;
    PointerTag ltag;
    PointerTag rtag;
} BiThrNode,*BiThrTree;
// 全局变量，始终指向前一个结点
BiThrTree pre=NULL;
Status CreatBiTheTree(BiThrTree T);//中序创建二叉树
Status InThreading(BiThrTree T);//二叉树线索化
Status InOrderThreading(BiThrTree p,BiThrTree T);//将二叉树创建一个头结点进行线索化
//   ***定义函数
Status CreatBiTheTree(BiThrTree T)
{
//先序创建二叉树，一开始创建的树尚未进行线索化，即tag均为link
    BiThrTree p;
    char c;
    scanf("%c",&c);
    if(c==' ')
    {
        T = NULL;
    } else
    {
        p = (BiThrTree)malloc(sizeof(BiThrTree));
        if(!p)
            exit(OVERFLOW);
        p->data=c;
        p->ltag=link;
        p->rtag=link;
        T=p;
        CreatBiTheTree(T->lchild);
        CreatBiTheTree(T->rchild);
    }
    return OK;
}
Status InThreading(BiThrTree T)
{
    //中序遍历线索化：左-根-右
    ////          a
    ////        /   \
    ////      b       c
    ////     /       / \
    ////   d       f    g
    //     中序遍历 db*afcg
    if(T)
    {
        InThreading(T->lchild);     //左孩子线索化
        if(!T->lchild)
        {
            T->ltag=thread;
            T->lchild=pre;  //pre初始化为T，没有前驱的结点左孩子指向头结点
        }
        if(!pre->rchild)
        {
            pre->rtag = thread;
            pre->rchild=T;
        }
        pre=T;
        InThreading(T->rchild);
    }
}
Status InOrderThreading(BiThrTree p,BiThrTree T)
{
    p = (BiThrTree) malloc(sizeof (BiThrTree));
    p->ltag = link;
    p->rtag = thread;
    p->rchild=p;
    if(!T)//如果是空树,头指针直接回指自己
    {
        p->lchild=p;
    } else//如果不是空树，则指向T;
    {
        p->lchild=T;
        pre = p;//pre 是头结点
        InThreading(T);//T作为根节点来进行中序线索化,全局变量pre在线索化中会改变，结束时pre是中序遍历的尾结点
        pre->rchild = p;    //that's all right  -^-
        pre->rtag = thread;
        p->rchild=pre;
    }

}
int main()
{
    BiThrTree T= NULL,p;
    CreatBiTheTree(T);

    InOrderThreading(p,T);

}