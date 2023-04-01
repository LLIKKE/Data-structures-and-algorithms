#include"typedefine.h"              //��Ź��õ����ͺͲ���
#include"sqlist_B.h"                //���ͼ�������ṹ�ͻ���������ͷ�ļ�
#include"sqlist_S.h"                //���ѧ��������ṹ�ͻ���������ͷ�ļ�
#include"queue.h"                   //��Ŷ��е�����ṹ�ͻ���������ͷ�ļ�
#include"borrow.h"                  //��Ž������ݽṹ�Ͳ�����ͷ�ļ�

char main_screen(void)     //��ʾ���˵�
{
    char choice;
    printf("\n@@@@@@@@@@@ѧ��ͼ����Ĺ���ϵͳ@@@@@@@@@\n");
    printf(" 1.ѧ�����ݹ���\n");   //��ʾ���˵�
    printf(" 2.ͼ����Ϣά��\n");
    printf(" 3.ͼ����Ĺ���\n");
    printf(" 0.�˳�\n");
    printf(" ��ѡ��(0-3):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
void sys_manager(SqList_S &stu,SqList_B &book,SBList &borrow,LinkQueue &queue )
{
    char c;
    while((c=main_screen())!='0')
    switch(c)
       {case '1': stu_manager(stu);    break;                          //ѧ����Ϣ����
        case '2': book_manager(book);   break;                         //ͼ����Ϣ����
        case '3': borrow_manager(borrow,book,stu,queue); break;        //ͼ����Ĺ���
       }
    return ;
}

int main()
{   SqList_B book;                                    //ͼ��˳���
    SqList_S stu;                                     //ѧ��˳���
    SBList borrow;                                    //ѧ��������Ϣ������+����
    LinkQueue queue;                                  //���ԤԼ��Ϣ�Ķ���

    InitList_SSq(stu);                  //��һ����˳�����ѧ����Ϣ
    OpenStuList(stu);                   //װ��ѧ����Ϣ
    InitList_BSq(book);                 //��һ����˳�����ͼ����Ϣ
    OpenBookList(book);                 //װ���ϴ�ϵͳ�ر�ʱ�����ͼ����Ϣ
    InitList_borrow(borrow);            //��һ���ձ���ͼ�������Ϣ
    OpenBorrowList(borrow);             //װ����ǰ�Ľ�����Ϣ
    InitQueue(queue);                   //��һ���ն��У����ԤԼ������Ϣ

    sys_manager(stu,book,borrow,queue); //����ѧ��ͼ����Ĺ���ϵͳ

    save_book(book);                    //����ͼ����Ϣ
    save_stu(stu);                      //����ѧ����Ϣ
    save_borrow(borrow);                //���������Ϣ
    DestroyList_SSq(stu);               //����ѧ����
    DestroyList_BSq(book);              //����ͼ���
    DestroyQueue(queue);                //���ٶ���
    printf("��л����ʹ�ã���������������\n");
    return 0;
}
