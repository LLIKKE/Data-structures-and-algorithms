#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node* wrapper(int data){
    struct node *retval = (struct node*)malloc(sizeof(struct node));
    retval->data = data;
    retval->next = NULL;
    return retval;
}

int main(){
    int input, todel;
    struct node *head = wrapper(0), *now = head, *prev;
    while(scanf("%d", &input) != EOF && input != 0){//scanf()的返回值是读取到的有效数据个数，如果只想读取
        now->next = wrapper(input);//入股只想读取一位梳子，返回值为1时正确，如果读取失败比如数据类型不一致，返回0
        now = now->next;
    }
    // wrapper生成一个新的节点，这个节点的指向是null，复制给now在现有的链表后面连接上，然后更新now让新添加的节点复制给now
    prev = head;
    now = prev->next;   // prev现在是头结点，然后让now指向头结点的下一个节点，也就是开始的元素
    scanf("%d", &todel);
    while(now != NULL){
        if(todel == now->data){
            prev->next = now->next;
            free(now);
            now = prev->next;   // prev和now是两个相互存储的变量
        }else if(prev->next != NULL){
            prev = prev->next;
            now = prev->next;
        }else{
            break;
        }
    }
    now = head->next;
    while(now != NULL){
        printf("%d", now->data);
        if(now->next != NULL){
            now = now->next;
        }else{
            break;
        }
    }
    return 0;
}
