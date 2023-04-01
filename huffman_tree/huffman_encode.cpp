#include <cstdlib>
#include <cstring>
#include <stdio.h>
typedef struct {
    unsigned int weight;
    unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;
typedef char **HuffmanCode;
void select(HuffmanTree ht,int i,int &s1,int &s2)
{
    int j,p,min1=0,min2=0;
    unsigned int weight1=ht->weight,weight2=ht->weight;

    for(j=1,p=0;j<=i;++j,++p)   //因为0位作为头接头没有使用，故从1开始
    {
        if(ht->parent==0) {
            if ((ht + p)->weight < weight1) {
                weight2 = weight1;
                weight1 = (ht + p)->weight;
                min2 = min1;
                min1 = p + 1;
            } else if ((ht + p)->weight < weight2) {
                weight2 = (ht + p)->weight;
                min2 = p + 1;
            }
        }
    }
    s1=min1;s2=min2;
}
void HuffmanCoding(HuffmanTree &HT,HuffmanCode HC,unsigned int *w,int n)
{
    //w存放n个字符的权值（大于0），构造赫夫曼树HT,并求出n个字符的赫夫曼编码
    if(n<=1) return;
    int m = 2 * n - 1;  //一个具有n个子叶的赫夫曼树有2*n-1个结点
    HT = (HuffmanTree)malloc((m+1)*sizeof(HuffmanTree));//多申请1了一个内存的存储，0号单元没有使用，
    HuffmanTree p;
    int i,s1,s2;
    for(p=HT+1,i=1;i<=n;++i,++p,++w)
        *p={*w,0,0,0};  //（注：这里第0位不用，作为头节点），初始化前n个结点的值，其中权重是n个字符的权重for
    for(;i<=m;++i,++p)
        *p={0,0,0,0};// 后n-1个结点作为全初始化为0
    for(i=n+1;i<=m;++i)//建立赫夫曼树，接在胡n-1个位置
    {
        select(HT,i-1,s1,s2);//从[1,i-1]中挑选**parent==0**里面两个最小的结点，其中s1<s2
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    // 从叶子到根逆向求每个字符的赫夫曼编码
    //HC
    //[
    // baseline1,
    // baseline2,
    // baseline3,
    // baseline4,
    // ] 动态定义的数组和静态定义的，存储上不一样
    //
    HC=(HuffmanCode) malloc((n+1)*sizeof (char *));//malloc函数会根据char**和char*来分配空间
    int start;
    unsigned int c,f;
    char cd[n];
    cd[n-1]='\0';
    for(i=1;i<=n;++i)
    {
        start=n-1;
        for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)//结点初始化parenet为0，所以当从子叶到根结点时，parent==0，结束循环
            if(HT[f].lchild==c)
                cd[--start]='0';
            else
                cd[--start]='1';
        HC[i]=(char *) malloc((n-start)*sizeof (char ));
        strcpy(HC[i],&cd[start]);
    }
    free(cd);
}
int main()
{
    HuffmanTree HT;
    int n;
    scanf("%d",&n);

    char code[n];
    unsigned int w[n];
    HuffmanCode HC;

    for(int i=0;i<n;i++)
        scanf("%d",w+i);
    scanf("%s",code);
    HuffmanCoding(HT,HC,w,n,code);
}