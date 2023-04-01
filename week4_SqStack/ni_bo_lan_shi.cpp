//输入一行字符表示后缀表达式，表达式中运算对象是个位数字，运算符有+、-、*、/、%，都是双目运算符，表达式结果用浮点数记录。
//
//输入格式:
//输入在一行中给出一个后缀表达式。
//
//输出格式:
//输出后缀表达式的值，保留小数点后2位。
//
//输入样例:
//62/3*
//输出样例:
//9.00
#include <stdio.h>
#include <cstdlib>

//定义状态变量
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW -1
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef float ElemType;
typedef int Status;
typedef struct {
    ElemType *top;
    ElemType *base;
    int stacksize;
}SqStack;
Status InitStack(SqStack &s);
Status DestroyStack(SqStack &s);
Status ClearStack(SqStack &s);
Status StackEmpty(SqStack s);
Status StackLength(SqStack s);
Status GetTop(SqStack s,ElemType &e);
Status Push(SqStack &s,ElemType e);
Status Pop(SqStack &s,ElemType &e);
Status StackTraverse(SqStack s,Status(*visit)());

Status InitStack(SqStack &s)
{
    s.base = (ElemType * )malloc(STACK_INIT_SIZE*sizeof (ElemType));
    if(!s.base) exit(OVERFLOW);
    s.top=s.base;
    s.stacksize = STACK_INIT_SIZE;
    return OK;
}
Status DestroyStack(SqStack &s)
{
    free(s.base);
    s.top=NULL;
    s.stacksize=0;
    return OK;
}
Status ClearStack(SqStack &s)
{
    if(s.base==NULL) exit(ERROR);
    s.top=s.base;
    return OK;
}
Status StackEmpty(SqStack s)
{
    if(s.base==s.top)
        return TRUE;
    else
        return ERROR;
}
Status StackLength(SqStack s)
{
    return s.top-s.base;
}
Status GetTop(SqStack s,ElemType &e)
{
    if(s.top==s.base) exit(ERROR);
    e=*(s.top-1);
    return OK;
}
Status Push(SqStack &s,ElemType e)
{
    if(s.top-s.base+1>=s.stacksize){//有点小改动。。。
        s.base = (ElemType*)realloc(s.base,s.stacksize+STACK_INCREMENT*sizeof (ElemType));
        s.stacksize+=STACK_INCREMENT;
    }
    if(!s.base)
        exit(ERROR);
    *s.top++=e;
    return OK;
}
Status Pop(SqStack &s,ElemType &e)
{
    if(StackEmpty(s)) exit(ERROR);
    e=*(s.top-1);
    s.top--;
    return OK;
}
int main()
{
    ElemType a = 0,b=0,p;
    int num3,num4;
    char ch;
    SqStack S;
    InitStack(S);
    while ((ch=getchar())!='\n')
    {

        if(ch>='0'&&ch<='9')
        {
            p=ElemType (ch-'0');
            Push(S,p);
        }

        else if(ch=='+')
        {
            Pop(S,a);
            Pop(S,b);

            Push(S,(b+a));
        }
        else if(ch=='-')
        {
            Pop(S,a);
            Pop(S,b);

            Push(S,(b-a));
        }
        else if(ch=='*')
        {
            Pop(S,a);
            Pop(S,b);

            Push(S,(b*a));
        }
        else if(ch=='/')
        {
            Pop(S,a);
            Pop(S,b);

            Push(S,(b/a));
        }
        else if(ch=='%')
        {
            Pop(S,a);
            Pop(S,b);
            num3 = int(a);
            num4 = int(b);
            Push(S,(num4%num3));
        }

    }
    printf("%.2f",*S.base);

}

