#define MAX_STUDENT_NUM 1000        //最多借阅图书的学生人数

typedef struct BorrowInfo                 //借阅信息结点
{  char  bookno[10];                      //书号
   DATE  borrowday;                       //借阅日期
   struct BorrowInfo *nextbook;
}BorrowInfo;
typedef struct StudentNode                //借阅信息链表
{  char        studentno[13];            //学号
   int borrownum;                        //借书本书
   BorrowInfo *firstbook;
}StudentNode;
typedef struct {                        //借阅链表
int studentnum;                         //有多少学生借了书
int borrownum;                          //有多少借阅记录
StudentNode sblist[ MAX_STUDENT_NUM];   //学生借阅数组
}SBList;
char borrow_manage_screen(void)     //显示借阅菜单
{
    char choice;
    printf("\n\t-----图书借阅-------\n");
    printf("\t1.借书\n");   //显示主菜单
    printf("\t2.还书\n");
    printf("\t3.图书借阅信息查询\n");
    printf("\t0.退出\n");
    printf("\t请选择(0-3):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}

Status InitList_borrow(SBList &borrow)   //初始化借阅信息表
 { borrow.studentnum=0;                    //借书学生数为0
   borrow.borrownum=0;                     //借阅信息结点数为0
 }
int find_borrow(SBList borrow,char *stuno)      //找到同学stuno（学号）的借书链表位序
 { int i;
   for(i=1; i<=borrow.studentnum; i++)
       if(strcmp(borrow.sblist[i-1].studentno,stuno)==0)
           return i;
   return 0;                                                      //找不到返回0
 }
//设定借阅信息记录文件格式
// 借书学生人数
// 学号 借书本书
// 学号 书号 借阅年 月 日
// 学号 书号 借阅年 月 日
// 学号 书号 借阅年 月 日
// 学号 借书本书
 Status OpenBorrowList(SBList &borrow)  //读入昨天借阅信息
 { FILE *fp;
   int i,j;
   BorrowInfo *p,onenode;
   char no[13];
   fp=fopen("borrow.txt","r");   //打开文件，准备读
   if(fp==NULL) return ERROR;
   fscanf(fp,"%d",&borrow.studentnum);    //读入借书学生人数
   borrow.borrownum=0;                   //借阅本书初始化
   for(i=1; i<=borrow.studentnum; i++)
      {fscanf(fp,"%s %d",borrow.sblist[i-1].studentno,&borrow.sblist[i-1].borrownum);  //读入借书同学学号和借阅本书
       borrow.sblist[i-1].firstbook=NULL;
       for(j=1; j<=borrow.sblist[i-1].borrownum; j++)
       { p=(BorrowInfo*)malloc(sizeof(BorrowInfo));
         fscanf(fp,"%s %s %d %d %d",no,onenode.bookno,&onenode.borrowday.year,   //读入该同学借阅信息
               &onenode.borrowday.month,&onenode.borrowday.day);
         if(strcmp(no,borrow.sblist[i-1].studentno)!=0)
           return ERROR;
         borrow.borrownum++;
         *p=onenode;
         p->nextbook=borrow.sblist[i-1].firstbook;                  //插入链首
         borrow.sblist[i-1].firstbook=p;
        }
      }
   fclose(fp);
   return OK;
 }
Status appointment_in(LinkQueue &queue,char *stuno,char*bookno,SqList_S stu)
{//为学号为stuno的同学预约借书bookno,将预约信息加入队列
    int i;
    SElemType es;
    QElemType eq;
    i=find_student(stu,stuno);   //在学生表中找学号为stuno的学生，返回位序i
    GetElem_SSq(stu,i,es);       //取这个学生信息es
    strcpy(eq.bookno,bookno);   //构造队列元素（学号、书号、手机）
    strcpy(eq.stuno,stuno);
    strcpy(eq.stumobile,es.studentmobile);
    EnQueue(queue,eq);                        //入队
    return OK;
}

 Status borrowed(SBList &borrow,SqList_B &book,SqList_S stu,int num,LinkQueue &queue)  //num是正在借书学生在borrow中的位序
 {  //为学生办理借书手续
    //未借到的书可以办理预约借书
     char bookno[10],yesno;
     int j;
     BElemType e;
     BorrowInfo *p;
     do{
          fflush(stdin); printf("\n\t请输入欲借书的书号："); gets(bookno); strupr(bookno);
          j=find_book(book,bookno);                  //查询这本书，获得书表中的位序
          if(j==0)                          //没有找到书
              {  printf("\t查无此书！"); return ERROR;         }
          GetElem_BSq(book,j,e);                     //获得这本书的全部信息
          if(e.totalnum<=e.borrownum)                //借不到时
             {  printf("\t全借完了！要预约借书吗(y/n)？");
                yesno=getche(); yesno=toupper(yesno);
               appointment_in(queue,borrow.sblist[num-1].studentno,e.bookno,stu);  //办理预约
             }
          else {
                 p=(BorrowInfo*)malloc(sizeof(BorrowInfo));     //建立借阅信息结点
                 strcpy(p->bookno,bookno);
                 p->borrowday=Get_Sys_Time();                   //获得系统时间
                 p->nextbook=borrow.sblist[num-1].firstbook;    //插入相应的借书链表
                 borrow.sblist[num-1].firstbook=p;
                 borrow.sblist[num-1].borrownum++;
                 e.borrownum++;
                 SetElem_BSq(book,j,e);                         //修改图书信息
                 borrow.borrownum++;
                 printf("\n\t\t********借书成功!***********\n");
                 printf("\t\t您已借书 %s %s，请在一个月内归还!\n",e.bookno,e.bookname);
                 if(borrow.sblist[num-1].borrownum>=5) break;        //借书数量达到5本，不能再借了
               }
          printf("\t继续借书(y/n)?");
          yesno=getche();
          yesno=toupper(yesno);
       }while(yesno=='Y');
       printf("\t\t谢谢！\n");
       return OK;
 }
 Status borrow_manage_borrow(SBList &borrow,SqList_B &book,SqList_S stu,LinkQueue &queue)   //借书处理
 {   char stuno[13],bookno[10];
     int i;
     printf("\t请输入你的学号："); gets(stuno);
     //先找该同学的借阅信息
     i=find_borrow(borrow,stuno);          //找学号为stuno的同学的借阅信息链首
     if(i&&i<=borrow.studentnum)
     {  //找到了，先查看借阅数量
         if(borrow.sblist[i-1].borrownum>=5)          //已经借了5本书，不能再借了
             { printf("\t您已借了5本以上的书，不能再借了，赶紧还书吧！"); return ERROR;}
         if(borrow.sblist[i-1].borrownum==0)
             { printf("\t您没有借书，赶紧借吧！"); }
         borrowed(borrow,book,stu,i,queue);                          //办理第i个同学借书
     }
     else     //没有找到该同学的借阅信息，说明他从没有借过书
     {  i=borrow.studentnum+1;                        //在借阅信息中增加一个空链表
        strcpy(borrow.sblist[i-1].studentno,stuno);
        borrow.sblist[i-1].borrownum=0;
        borrow.sblist[i-1].firstbook=NULL;
        borrow.studentnum++;                          //借书学生人数增加
        borrowed(borrow,book,stu,i,queue);            //办理第i个同学借书
     }

 }
 Status appointment_out(LinkQueue &queue, SBList &borrow, SqList_B &book, int num)
 //归还book表中位序为num的图书后，检查预约队列里是否有同学预约借此书
 //如果有，帮他把书借了
 {   int find=0,pos;
     char bookno[50];
     BorrowInfo *p;
     LinkQueue qtemp;
     QElemType eq;
     BElemType eb;
     InitQueue(qtemp);
     GetElem_BSq(book,num,eb);
     while(!QueueEmpty(queue))
     {
         DeQueue(queue,eq);
         if(strcmp(eq.bookno,eb.bookno)==0&&!find)   //有预约,帮他借书
         {
          p=(BorrowInfo*)malloc(sizeof(BorrowInfo));
          strcpy(p->bookno,eb.bookno);
          //获得借书日期信息
          p->borrowday=Get_Sys_Time( );           //获得系统时间
          pos=find_borrow(borrow,eq.stuno);       //找到该同学的借书链表
          p->nextbook=borrow.sblist[pos-1].firstbook;
          borrow.sblist[pos-1].firstbook=p;
          borrow.sblist[pos-1].borrownum++;
          eb.borrownum++;
          SetElem_BSq(book,num,eb);
          find=1;
          printf("\t\t学号%s 手机%s ：您预约的图书%s已经帮您借了，请2日内来取书！\n",
                   eq.stuno,eq.stumobile,eq.bookno);
          break;
         }
         else EnQueue(qtemp,eq);
     }
     while(!QueueEmpty(qtemp))
     { DeQueue(qtemp,eq);EnQueue(queue,eq); }
     DestroyQueue(qtemp);
     return OK;
 }
 Status borrow_manage_return(SBList &borrow,SqList_B &book,SqList_S stu, LinkQueue &queue)
 {   //归还图书。先根据学号和书号查到借阅结点，删除借阅结点
     //若有预约借书的同学，帮最早登记的同学借书,并通过手机通知他
     char stuno[13],bookno[10],yesno;
     int i,j;
     BorrowInfo *p,*pre;
     BElemType e;
     fflush(stdin);  printf("\t请输入你的学号："); gets(stuno);
     i=find_borrow(borrow,stuno);                              //先找该同学的借阅信息
     if(i==0||borrow.sblist[i-1].borrownum==0)
         { printf("\t您没有借书，赶紧去借吧！"); return ERROR;}

     if(i<=borrow.studentnum)
     {  //找到该同学借阅链表，再接着找借阅信息
       do{
         printf("\n\t请输入还书的书号:"); gets(bookno); strupr(bookno);
         p=borrow.sblist[i-1].firstbook;
         while(p&&strcmp(p->bookno,bookno)!=0)                             //找相关的借阅结点，并记录前驱
          { pre=p; p=p->nextbook; }
         if(!p) { printf("\n\t您没有借书%s!\n",bookno); return ERROR;}    //没有找到借阅信息
         if(p==borrow.sblist[i-1].firstbook)                               //删第一个借阅结点
            borrow.sblist[i-1].firstbook=p->nextbook;
         else                                                              //删其他借阅结点
            { pre->nextbook=p->nextbook; free(p);}
         borrow.sblist[i-1].borrownum--;                                   //借书量减1
         borrow.borrownum--;                                               //借阅量减1
         j=find_book(book,bookno);                                         //找到归还图书在书表的位序
         GetElem_BSq(book,j,e);
         e.borrownum--;                                                    //修改借出数量
         SetElem_BSq(book,j,e);                                            //修改图书表中信息
         printf("\n\t%s 您已归还图书%s %s\n",stuno,e.bookno,e.bookname);
         appointment_out(queue,borrow,book,j);                             //为预约学生办理借阅手续
         printf("\t继续还书吗(yes/no)？");
         yesno=getche(); yesno=toupper(yesno);
        }while(yesno=='Y');
     }
     else { printf("\n\t您没有借书！\n"); return ERROR;}
     return OK;
 }

 char borrow_search_screen(void)     //显示借阅菜单
{
    char choice;
    printf("\n\t\t*******图书借阅查询**********\n");
    printf("\t\t1.学生借阅情况查询\n");   //显示主菜单
    printf("\t\t2.图书借阅查询\n");
    printf("\t\t3.超期借书查询\n");
    printf("\t\t0.退出\n");
    printf("\t\t请选择(0-3):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
 Status borrow_manage_search(SBList borrow,SqList_B book,SqList_S stu)   //查询借阅信息和催还书
 {  char c;
      char stuno[13],bookno[10];
     int i,j,yesno;
     BorrowInfo *p;
     DATE now;
     BElemType eb;
     SElemType es;
     fflush(stdin);
     while((c=borrow_search_screen())!='0')
       switch(c)
        { case '1':  //输出某个同学的所有借阅信息
                     printf("\t\t请输入学号："); gets(stuno);
                     i=find_borrow(borrow,stuno);                    //先找该同学的借阅信息链表
                     if(i==0||borrow.sblist[i-1].borrownum==0)
                         { printf("\t\t您没有借书，赶紧去借吧！"); return ERROR;}
                     printf("\n\t\t%s 共借了 %d 本书:",stuno,borrow.sblist[i-1].borrownum);
                     p=borrow.sblist[i-1].firstbook;
                     while(p)                                         //输出所有借阅信息
                        { printf("\n\t\t%s %d-%d-%d",p->bookno,p->borrowday.year,p->borrowday.month,p->borrowday.day);
                          p=p->nextbook;
                        }
                     printf("\n");
                     break;
          case '2':  //输出某本书都被谁借了
                     printf("\t\t请输入书号："); gets(bookno); strupr(bookno);
                     j=find_book(book,bookno);                          //找到这本书
                     if(j==0)
                         { printf("\t\t没有这本书！\n"); return ERROR;}
                     GetElem_BSq(book,j,eb);                            //获得这本书的所有信息
                     if(eb.borrownum) printf("\n\t\t%s 共有 %d 个同学借了这本书!\n",bookno,eb.borrownum);
                     else  printf("\n\t\t没有同学借了这本书!\n");
                     j=1;
                     i=1;
                     p=borrow.sblist[i-1].firstbook;
                     //在所有借阅链表中找这本书的借阅信息
                     while(j<=eb.borrownum)
                     {   if(p==NULL)                              //找完一个链表
                         {i++; p=borrow.sblist[i-1].firstbook;}   //转到下一个链表
                         else
                             if(strcmp(p->bookno,bookno)!=0)       //找一个结点，没有找到
                                 p=p->nextbook;                    //找下一个结点
                             else {printf("\t\t学生%s 借 %s 日期：%d-%d-%d\n",borrow.sblist[i-1].studentno,bookno,   //找到一个结点
                                           p->borrowday.year,p->borrowday.month,p->borrowday.day);
                                   j++;
                                  }
                     }
                     break;
          case '3':  //超期借书查询
                     now=Get_Sys_Time( );                                         //获得系统时间
                     for(i=1; i<=borrow.studentnum; i++)                          //查所有借阅信息
                         { p= borrow.sblist[i-1].firstbook;
                           while(p)
                           {  yesno=0;                                             //假设没有超期
                              int day=0;
                              if(p->borrowday.year==now.year)                      //同一年情况下计算借阅多少天
                              {   if(p->borrowday.month+2<=now.month) yesno=1;     //月份超过1个月，如3月借，现在是5月
                                  if(p->borrowday.month!=now.month)                //前后两个月，计算天数
                                  { if(p->borrowday.month==2) day=28-p->borrowday.day;
                                    else day=30-p->borrowday.day;
                                    day+=now.day;
                                  }
                                  else day=now.day-p->borrowday.day+1;            // 同一个月，计算天数
                                  if(day>30)
                                      yesno=1;
                              }
                              if(p->borrowday.year+1==now.year)                   //不同年情况下计算借阅多少天
                              { if(12-p->borrowday.month<=now.month) yesno=1;     //月份超过1个月，如11月借，现在是1月
                                day=30-p->borrowday.day+now.day;                  //前后两个月，计算天数
                                if(day>30) yesno=1;
                              }
                              else if(p->borrowday.year<=now.year)
                                     yesno=1;
                              if(yesno)                                           //超期借书了
                              { printf("\t\t%s 借 %s 于%d-%d-%d, 超过一个月了！请尽快归还！\n",borrow.sblist[i-1].studentno,
                                          p->bookno,p->borrowday.year,p->borrowday.month,p->borrowday.day);
                                j=find_student(stu,borrow.sblist[i-1].studentno);  //找到这个同学
                                if(j)
                                   {GetElem_SSq(stu,j,es);
                                     printf("\t\t向%s发短信！\n",es.studentmobile);     //催还
                                   }
                                else  printf("!!%s这个同学不存在!!\n",borrow.sblist[i-1].studentno);
                              }
                              p=p->nextbook;
                           }
                         }
                     break;
    }
    return OK;
 }

void save_borrow(SBList borrow)  //保存所有借阅信息
 { FILE *fp;
   int i,j;
   BorrowInfo *p;
   fp=fopen("today_borrow.txt","w");        //打开文件，准备存放数据
   fprintf(fp,"%d\n",borrow.studentnum);
   for(i=1; i<=borrow.studentnum; i++)
   {
       fprintf(fp,"%s %d\n",borrow.sblist[i-1].studentno,borrow.sblist[i-1].borrownum);
       p=borrow.sblist[i-1].firstbook;
       for(j=1; j<=borrow.sblist[i-1].borrownum; j++)
       {
           fprintf(fp,"%s %s %d %d %d\n",borrow.sblist[i-1].studentno,p->bookno,p->borrowday.year,p->borrowday.month,p->borrowday.day);
           p=p->nextbook;
       }
   }
   fclose(fp);
 }
void borrow_manager(SBList &borrow,SqList_B &book,SqList_S stu,LinkQueue &queue)  //借阅管理
{
    char c;
    while((c=borrow_manage_screen())!='0')
    switch(c)
       {case '1': borrow_manage_borrow(borrow,book,stu,queue);    break;    //借书
        case '2': borrow_manage_return(borrow,book,stu,queue);    break;    //还书
        case '3': borrow_manage_search(borrow,book,stu);          break;    //查询
       }
    return ;
}


