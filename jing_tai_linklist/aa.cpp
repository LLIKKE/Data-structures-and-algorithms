// 链栈的数据结构及方法的定义
typedef struct NodeType{
    ElemType data;
    NodeType *next;
}NodeType,*LinkType;
typedef struct{
    LinkType top;
    int size;
}Stack;
void InitStack(Stack &s)
{
    s.top=NULL;
    s.size=0;
}
void DestroyStack(Stack &s)
{
    LinkType p;
    while(s.top){
        p=s.top;
        s.top=p->next;
        delete p;
        s.size--;
    }
}
void ClearStack(Stack &s)
{
    LinkType p;
    while(s.top){
        p=s.top;
        s.top=p->next;
        delete p;
        s.size--;
    }
}
int StackLength(Stack s)
{
    return s.size;
}
Status StackEmpty(Stack s) {
    if (s.size == 0) return TRUE;
    else return FALSE;
}

Status GetTop(Stack s,ElemType &e)
{
    if(!s.top) return ERROR;
    else{
        e=s.top->data;
        return OK;
    }
}
Status Push(Stack &s,ElemType e)
{
    LinkType p;
    p=new NodeType;
    if(!p) exit(OVERFLOW);
    p->next=s.top;
    s.top=p;
    p->data=e;
    s.size++;
    return OK;
}
Status Pop(Stack &s,ElemType &e)
{
    LinkType p;
    if(s.top){
        e=s.top->data;
        p=s.top;
        s.top=p->next;
        delete p;
        s.size--;
    }
    return OK;
}
// 从栈顶到栈底用 Visit()函数遍历栈中每个数据元素
void StackTraverse(Stack s,Status (*Visit)(ElemType e))
{
    LinkType p;
    p=s.top;
    while(p) Visit(p->data);
}
