//----------队列的链式存储结构----------
typedef struct
{ char stuno[13];
  char bookno[10];
  char stumobile[20];
}QElemType;
typedef  struct QNode
{QElemType     data;
 struct QNode   *next;
}QNode, *QueuePtr;
typedef struct             //链队列的定义
{  QueuePtr  front;        //队头指针
   QueuePtr  rear;         //队尾指针
}LinkQueue;

Status InitQueue(LinkQueue &Q)
{// 构造一个空队列Q
Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
if(!Q.front) exit(OVERFLOW);    //存储分配失败
Q.front->next = NULL;
return OK;
}
Status DestroyQueue(LinkQueue &Q)
{// 销毁队列Q
while(Q.front)
 { Q.rear = Q.front->next;
   free(Q.front);
   Q.front = Q.rear;
 }
return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{//若队列不空,则删除Q的队头元素,用e返回其值,
//并返回OK;  否则返回ERROR
QueuePtr p;
if(Q.front ==Q.rear) return ERROR;
p = Q.front->next;  e = p->data;
Q.front->next = p->next;
if(Q.rear==p)Q.rear = Q.front;
free(p);  return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{// 插入元素e为Q的新的队尾元素
QueuePtr p;
p = (QueuePtr)malloc(sizeof(QNode));
if(!p)  exit(OVERFLOW);        //存储分配失败
p->data = e;   p->next = NULL;
Q.rear->next = p;   Q.rear = p;
return OK;
}

Status QueueEmpty(LinkQueue Q)
{// 若队列Q为空队列,则返回TRUE,否则返回FALSE .
    if(Q.front ==Q.rear) return TRUE;
    return FALSE;
}

