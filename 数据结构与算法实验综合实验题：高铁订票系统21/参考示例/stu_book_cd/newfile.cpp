#include"typedefine.h"              //存放共用的类型和操作
#include"sqlist_B.h"                //存放图书的物理结构和基本操作的头文件
#include"sqlist_S.h"                //存放学生的物理结构和基本操作的头文件
#include"queue.h"                   //存放队列的物理结构和基本操作的头文件
#include"borrow.h"                  //存放借阅数据结构和操作的头文件

char main_screen(void)     //显示主菜单
{
    char choice;
    printf("\n@@@@@@@@@@@学生图书借阅管理系统@@@@@@@@@\n");
    printf(" 1.学生数据管理\n");   //显示主菜单
    printf(" 2.图书信息维护\n");
    printf(" 3.图书借阅管理\n");
    printf(" 0.退出\n");
    printf(" 请选择(0-3):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
void sys_manager(SqList_S &stu,SqList_B &book,SBList &borrow,LinkQueue &queue )
{
    char c;
    while((c=main_screen())!='0')
    switch(c)
       {case '1': stu_manager(stu);    break;                          //学生信息管理
        case '2': book_manager(book);   break;                         //图书信息管理
        case '3': borrow_manager(borrow,book,stu,queue); break;        //图书借阅管理
       }
    return ;
}

int main()
{   SqList_B book;                                    //图书顺序表
    SqList_S stu;                                     //学生顺序表
    SBList borrow;                                    //学生借阅信息（数组+链表）
    LinkQueue queue;                                  //存放预约信息的队列

    InitList_SSq(stu);                  //建一个空顺序表存放学生信息
    OpenStuList(stu);                   //装入学生信息
    InitList_BSq(book);                 //建一个空顺序表存放图书信息
    OpenBookList(book);                 //装入上次系统关闭时保存的图书信息
    InitList_borrow(borrow);            //建一个空表存放图书借阅信息
    OpenBorrowList(borrow);             //装入以前的借阅信息
    InitQueue(queue);                   //建一个空队列，存放预约借书信息

    sys_manager(stu,book,borrow,queue); //进入学生图书借阅管理系统

    save_book(book);                    //保存图书信息
    save_stu(stu);                      //保存学生信息
    save_borrow(borrow);                //保存借阅信息
    DestroyList_SSq(stu);               //销毁学生表
    DestroyList_BSq(book);              //销毁图书表
    DestroyQueue(queue);                //销毁队列
    printf("感谢您的使用，请提出宝贵意见！\n");
    return 0;
}
