#define MAX_STUDENT_NUM 1000        //������ͼ���ѧ������

typedef struct BorrowInfo                 //������Ϣ���
{  char  bookno[10];                      //���
   DATE  borrowday;                       //��������
   struct BorrowInfo *nextbook;
}BorrowInfo;
typedef struct StudentNode                //������Ϣ����
{  char        studentno[13];            //ѧ��
   int borrownum;                        //���鱾��
   BorrowInfo *firstbook;
}StudentNode;
typedef struct {                        //��������
int studentnum;                         //�ж���ѧ��������
int borrownum;                          //�ж��ٽ��ļ�¼
StudentNode sblist[ MAX_STUDENT_NUM];   //ѧ����������
}SBList;
char borrow_manage_screen(void)     //��ʾ���Ĳ˵�
{
    char choice;
    printf("\n\t-----ͼ�����-------\n");
    printf("\t1.����\n");   //��ʾ���˵�
    printf("\t2.����\n");
    printf("\t3.ͼ�������Ϣ��ѯ\n");
    printf("\t0.�˳�\n");
    printf("\t��ѡ��(0-3):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}

Status InitList_borrow(SBList &borrow)   //��ʼ��������Ϣ��
 { borrow.studentnum=0;                    //����ѧ����Ϊ0
   borrow.borrownum=0;                     //������Ϣ�����Ϊ0
 }
int find_borrow(SBList borrow,char *stuno)      //�ҵ�ͬѧstuno��ѧ�ţ��Ľ�������λ��
 { int i;
   for(i=1; i<=borrow.studentnum; i++)
       if(strcmp(borrow.sblist[i-1].studentno,stuno)==0)
           return i;
   return 0;                                                      //�Ҳ�������0
 }
//�趨������Ϣ��¼�ļ���ʽ
// ����ѧ������
// ѧ�� ���鱾��
// ѧ�� ��� ������ �� ��
// ѧ�� ��� ������ �� ��
// ѧ�� ��� ������ �� ��
// ѧ�� ���鱾��
 Status OpenBorrowList(SBList &borrow)  //�������������Ϣ
 { FILE *fp;
   int i,j;
   BorrowInfo *p,onenode;
   char no[13];
   fp=fopen("borrow.txt","r");   //���ļ���׼����
   if(fp==NULL) return ERROR;
   fscanf(fp,"%d",&borrow.studentnum);    //�������ѧ������
   borrow.borrownum=0;                   //���ı����ʼ��
   for(i=1; i<=borrow.studentnum; i++)
      {fscanf(fp,"%s %d",borrow.sblist[i-1].studentno,&borrow.sblist[i-1].borrownum);  //�������ͬѧѧ�źͽ��ı���
       borrow.sblist[i-1].firstbook=NULL;
       for(j=1; j<=borrow.sblist[i-1].borrownum; j++)
       { p=(BorrowInfo*)malloc(sizeof(BorrowInfo));
         fscanf(fp,"%s %s %d %d %d",no,onenode.bookno,&onenode.borrowday.year,   //�����ͬѧ������Ϣ
               &onenode.borrowday.month,&onenode.borrowday.day);
         if(strcmp(no,borrow.sblist[i-1].studentno)!=0)
           return ERROR;
         borrow.borrownum++;
         *p=onenode;
         p->nextbook=borrow.sblist[i-1].firstbook;                  //��������
         borrow.sblist[i-1].firstbook=p;
        }
      }
   fclose(fp);
   return OK;
 }
Status appointment_in(LinkQueue &queue,char *stuno,char*bookno,SqList_S stu)
{//Ϊѧ��Ϊstuno��ͬѧԤԼ����bookno,��ԤԼ��Ϣ�������
    int i;
    SElemType es;
    QElemType eq;
    i=find_student(stu,stuno);   //��ѧ��������ѧ��Ϊstuno��ѧ��������λ��i
    GetElem_SSq(stu,i,es);       //ȡ���ѧ����Ϣes
    strcpy(eq.bookno,bookno);   //�������Ԫ�أ�ѧ�š���š��ֻ���
    strcpy(eq.stuno,stuno);
    strcpy(eq.stumobile,es.studentmobile);
    EnQueue(queue,eq);                        //���
    return OK;
}

 Status borrowed(SBList &borrow,SqList_B &book,SqList_S stu,int num,LinkQueue &queue)  //num�����ڽ���ѧ����borrow�е�λ��
 {  //Ϊѧ�������������
    //δ�赽������԰���ԤԼ����
     char bookno[10],yesno;
     int j;
     BElemType e;
     BorrowInfo *p;
     do{
          fflush(stdin); printf("\n\t���������������ţ�"); gets(bookno); strupr(bookno);
          j=find_book(book,bookno);                  //��ѯ�Ȿ�飬�������е�λ��
          if(j==0)                          //û���ҵ���
              {  printf("\t���޴��飡"); return ERROR;         }
          GetElem_BSq(book,j,e);                     //����Ȿ���ȫ����Ϣ
          if(e.totalnum<=e.borrownum)                //�費��ʱ
             {  printf("\tȫ�����ˣ�ҪԤԼ������(y/n)��");
                yesno=getche(); yesno=toupper(yesno);
               appointment_in(queue,borrow.sblist[num-1].studentno,e.bookno,stu);  //����ԤԼ
             }
          else {
                 p=(BorrowInfo*)malloc(sizeof(BorrowInfo));     //����������Ϣ���
                 strcpy(p->bookno,bookno);
                 p->borrowday=Get_Sys_Time();                   //���ϵͳʱ��
                 p->nextbook=borrow.sblist[num-1].firstbook;    //������Ӧ�Ľ�������
                 borrow.sblist[num-1].firstbook=p;
                 borrow.sblist[num-1].borrownum++;
                 e.borrownum++;
                 SetElem_BSq(book,j,e);                         //�޸�ͼ����Ϣ
                 borrow.borrownum++;
                 printf("\n\t\t********����ɹ�!***********\n");
                 printf("\t\t���ѽ��� %s %s������һ�����ڹ黹!\n",e.bookno,e.bookname);
                 if(borrow.sblist[num-1].borrownum>=5) break;        //���������ﵽ5���������ٽ���
               }
          printf("\t��������(y/n)?");
          yesno=getche();
          yesno=toupper(yesno);
       }while(yesno=='Y');
       printf("\t\tлл��\n");
       return OK;
 }
 Status borrow_manage_borrow(SBList &borrow,SqList_B &book,SqList_S stu,LinkQueue &queue)   //���鴦��
 {   char stuno[13],bookno[10];
     int i;
     printf("\t���������ѧ�ţ�"); gets(stuno);
     //���Ҹ�ͬѧ�Ľ�����Ϣ
     i=find_borrow(borrow,stuno);          //��ѧ��Ϊstuno��ͬѧ�Ľ�����Ϣ����
     if(i&&i<=borrow.studentnum)
     {  //�ҵ��ˣ��Ȳ鿴��������
         if(borrow.sblist[i-1].borrownum>=5)          //�Ѿ�����5���飬�����ٽ���
             { printf("\t���ѽ���5�����ϵ��飬�����ٽ��ˣ��Ͻ�����ɣ�"); return ERROR;}
         if(borrow.sblist[i-1].borrownum==0)
             { printf("\t��û�н��飬�Ͻ���ɣ�"); }
         borrowed(borrow,book,stu,i,queue);                          //�����i��ͬѧ����
     }
     else     //û���ҵ���ͬѧ�Ľ�����Ϣ��˵������û�н����
     {  i=borrow.studentnum+1;                        //�ڽ�����Ϣ������һ��������
        strcpy(borrow.sblist[i-1].studentno,stuno);
        borrow.sblist[i-1].borrownum=0;
        borrow.sblist[i-1].firstbook=NULL;
        borrow.studentnum++;                          //����ѧ����������
        borrowed(borrow,book,stu,i,queue);            //�����i��ͬѧ����
     }

 }
 Status appointment_out(LinkQueue &queue, SBList &borrow, SqList_B &book, int num)
 //�黹book����λ��Ϊnum��ͼ��󣬼��ԤԼ�������Ƿ���ͬѧԤԼ�����
 //����У������������
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
         if(strcmp(eq.bookno,eb.bookno)==0&&!find)   //��ԤԼ,��������
         {
          p=(BorrowInfo*)malloc(sizeof(BorrowInfo));
          strcpy(p->bookno,eb.bookno);
          //��ý���������Ϣ
          p->borrowday=Get_Sys_Time( );           //���ϵͳʱ��
          pos=find_borrow(borrow,eq.stuno);       //�ҵ���ͬѧ�Ľ�������
          p->nextbook=borrow.sblist[pos-1].firstbook;
          borrow.sblist[pos-1].firstbook=p;
          borrow.sblist[pos-1].borrownum++;
          eb.borrownum++;
          SetElem_BSq(book,num,eb);
          find=1;
          printf("\t\tѧ��%s �ֻ�%s ����ԤԼ��ͼ��%s�Ѿ��������ˣ���2������ȡ�飡\n",
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
 {   //�黹ͼ�顣�ȸ���ѧ�ź���Ų鵽���Ľ�㣬ɾ�����Ľ��
     //����ԤԼ�����ͬѧ��������Ǽǵ�ͬѧ����,��ͨ���ֻ�֪ͨ��
     char stuno[13],bookno[10],yesno;
     int i,j;
     BorrowInfo *p,*pre;
     BElemType e;
     fflush(stdin);  printf("\t���������ѧ�ţ�"); gets(stuno);
     i=find_borrow(borrow,stuno);                              //���Ҹ�ͬѧ�Ľ�����Ϣ
     if(i==0||borrow.sblist[i-1].borrownum==0)
         { printf("\t��û�н��飬�Ͻ�ȥ��ɣ�"); return ERROR;}

     if(i<=borrow.studentnum)
     {  //�ҵ���ͬѧ���������ٽ����ҽ�����Ϣ
       do{
         printf("\n\t�����뻹������:"); gets(bookno); strupr(bookno);
         p=borrow.sblist[i-1].firstbook;
         while(p&&strcmp(p->bookno,bookno)!=0)                             //����صĽ��Ľ�㣬����¼ǰ��
          { pre=p; p=p->nextbook; }
         if(!p) { printf("\n\t��û�н���%s!\n",bookno); return ERROR;}    //û���ҵ�������Ϣ
         if(p==borrow.sblist[i-1].firstbook)                               //ɾ��һ�����Ľ��
            borrow.sblist[i-1].firstbook=p->nextbook;
         else                                                              //ɾ�������Ľ��
            { pre->nextbook=p->nextbook; free(p);}
         borrow.sblist[i-1].borrownum--;                                   //��������1
         borrow.borrownum--;                                               //��������1
         j=find_book(book,bookno);                                         //�ҵ��黹ͼ��������λ��
         GetElem_BSq(book,j,e);
         e.borrownum--;                                                    //�޸Ľ������
         SetElem_BSq(book,j,e);                                            //�޸�ͼ�������Ϣ
         printf("\n\t%s ���ѹ黹ͼ��%s %s\n",stuno,e.bookno,e.bookname);
         appointment_out(queue,borrow,book,j);                             //ΪԤԼѧ�������������
         printf("\t����������(yes/no)��");
         yesno=getche(); yesno=toupper(yesno);
        }while(yesno=='Y');
     }
     else { printf("\n\t��û�н��飡\n"); return ERROR;}
     return OK;
 }

 char borrow_search_screen(void)     //��ʾ���Ĳ˵�
{
    char choice;
    printf("\n\t\t*******ͼ����Ĳ�ѯ**********\n");
    printf("\t\t1.ѧ�����������ѯ\n");   //��ʾ���˵�
    printf("\t\t2.ͼ����Ĳ�ѯ\n");
    printf("\t\t3.���ڽ����ѯ\n");
    printf("\t\t0.�˳�\n");
    printf("\t\t��ѡ��(0-3):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
 Status borrow_manage_search(SBList borrow,SqList_B book,SqList_S stu)   //��ѯ������Ϣ�ʹ߻���
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
        { case '1':  //���ĳ��ͬѧ�����н�����Ϣ
                     printf("\t\t������ѧ�ţ�"); gets(stuno);
                     i=find_borrow(borrow,stuno);                    //���Ҹ�ͬѧ�Ľ�����Ϣ����
                     if(i==0||borrow.sblist[i-1].borrownum==0)
                         { printf("\t\t��û�н��飬�Ͻ�ȥ��ɣ�"); return ERROR;}
                     printf("\n\t\t%s ������ %d ����:",stuno,borrow.sblist[i-1].borrownum);
                     p=borrow.sblist[i-1].firstbook;
                     while(p)                                         //������н�����Ϣ
                        { printf("\n\t\t%s %d-%d-%d",p->bookno,p->borrowday.year,p->borrowday.month,p->borrowday.day);
                          p=p->nextbook;
                        }
                     printf("\n");
                     break;
          case '2':  //���ĳ���鶼��˭����
                     printf("\t\t��������ţ�"); gets(bookno); strupr(bookno);
                     j=find_book(book,bookno);                          //�ҵ��Ȿ��
                     if(j==0)
                         { printf("\t\tû���Ȿ�飡\n"); return ERROR;}
                     GetElem_BSq(book,j,eb);                            //����Ȿ���������Ϣ
                     if(eb.borrownum) printf("\n\t\t%s ���� %d ��ͬѧ�����Ȿ��!\n",bookno,eb.borrownum);
                     else  printf("\n\t\tû��ͬѧ�����Ȿ��!\n");
                     j=1;
                     i=1;
                     p=borrow.sblist[i-1].firstbook;
                     //�����н������������Ȿ��Ľ�����Ϣ
                     while(j<=eb.borrownum)
                     {   if(p==NULL)                              //����һ������
                         {i++; p=borrow.sblist[i-1].firstbook;}   //ת����һ������
                         else
                             if(strcmp(p->bookno,bookno)!=0)       //��һ����㣬û���ҵ�
                                 p=p->nextbook;                    //����һ�����
                             else {printf("\t\tѧ��%s �� %s ���ڣ�%d-%d-%d\n",borrow.sblist[i-1].studentno,bookno,   //�ҵ�һ�����
                                           p->borrowday.year,p->borrowday.month,p->borrowday.day);
                                   j++;
                                  }
                     }
                     break;
          case '3':  //���ڽ����ѯ
                     now=Get_Sys_Time( );                                         //���ϵͳʱ��
                     for(i=1; i<=borrow.studentnum; i++)                          //�����н�����Ϣ
                         { p= borrow.sblist[i-1].firstbook;
                           while(p)
                           {  yesno=0;                                             //����û�г���
                              int day=0;
                              if(p->borrowday.year==now.year)                      //ͬһ������¼�����Ķ�����
                              {   if(p->borrowday.month+2<=now.month) yesno=1;     //�·ݳ���1���£���3�½裬������5��
                                  if(p->borrowday.month!=now.month)                //ǰ�������£���������
                                  { if(p->borrowday.month==2) day=28-p->borrowday.day;
                                    else day=30-p->borrowday.day;
                                    day+=now.day;
                                  }
                                  else day=now.day-p->borrowday.day+1;            // ͬһ���£���������
                                  if(day>30)
                                      yesno=1;
                              }
                              if(p->borrowday.year+1==now.year)                   //��ͬ������¼�����Ķ�����
                              { if(12-p->borrowday.month<=now.month) yesno=1;     //�·ݳ���1���£���11�½裬������1��
                                day=30-p->borrowday.day+now.day;                  //ǰ�������£���������
                                if(day>30) yesno=1;
                              }
                              else if(p->borrowday.year<=now.year)
                                     yesno=1;
                              if(yesno)                                           //���ڽ�����
                              { printf("\t\t%s �� %s ��%d-%d-%d, ����һ�����ˣ��뾡��黹��\n",borrow.sblist[i-1].studentno,
                                          p->bookno,p->borrowday.year,p->borrowday.month,p->borrowday.day);
                                j=find_student(stu,borrow.sblist[i-1].studentno);  //�ҵ����ͬѧ
                                if(j)
                                   {GetElem_SSq(stu,j,es);
                                     printf("\t\t��%s�����ţ�\n",es.studentmobile);     //�߻�
                                   }
                                else  printf("!!%s���ͬѧ������!!\n",borrow.sblist[i-1].studentno);
                              }
                              p=p->nextbook;
                           }
                         }
                     break;
    }
    return OK;
 }

void save_borrow(SBList borrow)  //�������н�����Ϣ
 { FILE *fp;
   int i,j;
   BorrowInfo *p;
   fp=fopen("today_borrow.txt","w");        //���ļ���׼���������
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
void borrow_manager(SBList &borrow,SqList_B &book,SqList_S stu,LinkQueue &queue)  //���Ĺ���
{
    char c;
    while((c=borrow_manage_screen())!='0')
    switch(c)
       {case '1': borrow_manage_borrow(borrow,book,stu,queue);    break;    //����
        case '2': borrow_manage_return(borrow,book,stu,queue);    break;    //����
        case '3': borrow_manage_search(borrow,book,stu);          break;    //��ѯ
       }
    return ;
}


