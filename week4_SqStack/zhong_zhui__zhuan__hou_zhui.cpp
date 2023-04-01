#include <stdio.h>
#include <cstdlib>

//定义状态变量
#define OK 1
#define TRUE 1
#define FALSE 0
#define ERROR 0
#define OVERFLOW (-1)
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
typedef char ElemType;
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

int priority(char c)
{
    if(c=='+'||c=='-')
        return 1;
    else if(c=='*'||c=='/'||c=='%')
        return 2;
    return ERROR;
}

int main() {
    char ch;
    char sign,now;
    SqStack S;
    InitStack(S);
    while ((ch = getchar()) != '\n')
    {
            if((ch>='0'&&ch<='9')||(ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))
            {
                printf("%c",ch);
            }
            else
            {
                if(StackEmpty(S))
                    Push(S,ch);
                else if(ch=='(')
                {
                    Push(S,ch);
                }
                else if(ch==')')
                {
                    while(*(S.top-1)!='(')
                    {
                        Pop(S,sign);
                        printf("%c",sign);
                    }
                    Pop(S,sign);
                }
                else
                {
                    while(priority(ch)<=priority(*(S.top-1)))
                    {
                        Pop(S,sign);
                        printf("%c",sign);
                        if(StackEmpty(S))
                            break;
                    }
                    Push(S,ch);
                }
            }

        while(!StackEmpty(S))
        {
            Pop(S,sign);
            if(sign!='('||sign!=')')
                printf("%c",sign);
        }
    }

    if(!StackEmpty(S))
        {
            Pop(S,sign);
            putchar(sign);
        }
}