//二叉树
#include <ntdef.h>
#include "stdio.h"
#include "cstdlib"


#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef char TElemType;
typedef int Status;
typedef struct BiTNode{
    TElemType data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
Status CreateBiTree(BiTree &T);//按次序输入二叉树中结点的值（字符），空字符表示空树
Status PreOrderTraverse(BiTree T,Status(*visit)(TElemType e));//  先序遍历  二叉树，对每个结点调用visit函数
Status InOrderTraverse(BiTree T,Status (*visit)(TElemType e));//  中序遍历  二叉树，
Status PostOrderTraverse(BiTree T,Status (*visit)(TElemType e));//  后序遍历  二叉树
Status LevelOrderTraverse(BiTree T,Status(*visit)(TElemType e));//层序遍历  二叉树
Status TreeHight(BiTree T);//遍历计算树的高度
BiTNode * ziTree(BiTree T, TElemType e);
#include "SqStack.cpp"
Status CreateBiTree(BiTree &T)
{
    //按***先序次序***输入树的值
    //        if(!(T=(BiTree)malloc(sizeof (BiTNode))))
    //            exit(OVERFLOW);//分配失败
    //        T->data=ch;//根节点
    //        CreateBiTree(T->lchild);//生成左子树
    //        CreateBiTree(T->rchild);//生成右子树
    //关键是这几行的顺序
    //按***中序次序***输入树的值
    //        if(!(T=(BiTree)malloc(sizeof (BiTNode))))
    //            exit(OVERFLOW);//分配失败
    //        CreateBiTree(T->lchild);//生成左子树
    //        T->data=ch;//根节点
    //        CreateBiTree(T->rchild);//生成右子树
    //按***后序次序***输入树的值
    //        if(!(T=(BiTree)malloc(sizeof (BiTNode))))
    //            exit(OVERFLOW);//分配失败
    //        CreateBiTree(T->lchild);//生成左子树
    //        CreateBiTree(T->rchild);//生成右子树
    //        T->data=ch;//根节点
    char ch;
    scanf("%c",&ch);
    if(ch=='*') T=NULL;//输入空格则表示，这是一棵空树
    else
    {
        if(!(T=(BiTree)malloc(sizeof (BiTNode))))
            exit(OVERFLOW);//分配失败
        T->data=ch;//根节点
        CreateBiTree(T->lchild);//生成左子树
        CreateBiTree(T->rchild);//生成右子树
    }
    return OK;
}

Status PreOrderTraverse(BiTree T,Status(*visit)(TElemType e))
{
    //遍历树的方法：递归遍历
    //分三种方式
    //*******先序遍历：根-左-右
    //        if(visit(T->data))//用visit操作这个结点的数据
    //              if(PreOrderTraverse(T->rchild,visit))//左节点结束后，换到右节点遍历
    //                  if(PreOrderTraverse(T->lchild,visit))//然后以右节点为根节点，继续左结点的遍历

    //*******中序遍历：左-根-右
    //        if(PreOrderTraverse(T->lchild,visit))//然后以右节点为根节点，继续左结点的遍历
    //              if(visit(T->data))//用visit操作这个结点的数据
    //                  if(PreOrderTraverse(T->rchild,visit))//左节点结束后，换到右节点遍历

    //*******后续遍历：根-左-右
    //        if(PreOrderTraverse(T->lchild,visit))//然后以右节点为根节点，继续左结点的遍历
    //              if(PreOrderTraverse(T->rchild,visit))//左节点结束后，换到右节点遍历
    //                  if(visit(T->data))//用visit操作这个结点的数据
    if(T){//以当前节点为根节点判断，如果当前节点为空，则结束这一分支的继续遍历
        if(visit(T->data))//用visit操作这个结点的数据
            if(PreOrderTraverse(T->lchild,visit))//然后以右节点为根节点，继续左结点的遍历
                if(PreOrderTraverse(T->rchild,visit))//左节点结束后，换到右节点遍历
                    return OK;
        return ERROR;
    } else return OK;
}

Status InOrderTraverse(BiTree T,Status(*visit)(TElemType e))
{
    SqStack S;
    BiTree p;
    InitStack(S);
    Push(S,T);
    while (!StackEmpty(S))
    {
        while (GetTop(S,p)&&p)
            Push(S,p->lchild);
        Pop(S,p);
        if(!StackEmpty(S))
        {
            Pop(S,p);
            if(!visit(p->data))
                return ERROR;
            Push(S,p->rchild);
        }
    }
    return OK;
}
Status PostOrderTraverse(BiTree T,Status (*visit)(TElemType e))
{
    if(T) {
        if (PostOrderTraverse(T->lchild, visit))
            if (PostOrderTraverse(T->rchild, visit))
                if (visit(T->data))
                    return OK;
        return ERROR;
    } else
        return OK;
}
//          a
//        /   \
//      b       c
//     / \     / \
//   d    e  f    g
Status LevelOrderTraverse(BiTree T,Status(*visit)(TElemType e))
{
    // rear ------------ front
    BiTree queue[100];
    BiTree p;
    int rear=0,front=0;
    if(T)
    {
        queue[front++]=T;
    }
    while (rear!=front)
    {
        p=queue[rear++];
        visit(p->data);
        if(p->lchild)
            queue[front++]=p->lchild;
        if(p->rchild)
            queue[front++] =p->rchild;
    }
}


Status TreeHight(BiTree T)
{
    //计算树的深度
    //按照左边和右边遍历到子叶，每次得到最深的那边的深度
    int HL,HR,MaxH;
    if(T){
        HL= TreeHight(T->lchild);
        HR= TreeHight(T->rchild);
        MaxH=HL>HR?HL:HR;
        return (MaxH+1);//每次递归都会加一，也就是深度加一
    } else
        return 0;
}
BiTree ziTree(BiTree T, TElemType e)
{
    //
    BiTree t;
    if(T==NULL)
        return ERROR;
    else
    {
        if(T->data==e)//可能正是这个节点是e
            return T;//用作递归的结束条件
        else{
            t= ziTree(T->lchild,e);//T的左子树，先看子树是不是这个e，不是的话再递推
            if(t)//如果t找到子叶结点了还没找到，就找右子树
                return t;
            else
                return ziTree(T->rchild,e);
        }
    }
}