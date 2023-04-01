typedef struct  //图书信息
{
	char  bookno[10];           //书号
	char  bookname[50];         //书名
	char  author[20];           //作者
	char  publisher[20];        //出版社
	int   totalnum;             //馆藏数量
	int   borrownum;            //借出数量
        DATE  pubday;               //出版日期
}ElemType_Book;

typedef  ElemType_Book BElemType;

typedef   struct
{
  BElemType   *elem;                 //存储空间基址
  int         length;                //当前长度
  int         listsize;              //当前分配的存储容量
}SqList_B;

Status InitList_BSq(SqList_B  &L)
{  //构造一个空的线性表L.
  L.elem=(BElemType *)malloc(LIST_INIT_SIZE*sizeof(BElemType));
  if(!L.elem)exit(OVERFLOW);               //存储分配失败
  L.length=0;                                                //空表长度为0
  L.listsize=LIST_INIT_SIZE;                  //初始存储容量
  return OK;
}//InitList_BSq

Status DestroyList_BSq(SqList_B  &L)
{  //销毁一个线性表L.
  free(L.elem);
  L.length=0;
  L.listsize=0;
  return OK;
}

int ListLength_BSq(SqList_B L)
{ return L.length;}

Status ListInsert_BSq(SqList_B &L,int i,BElemType e)
{ BElemType *p,*q,*newbase;
  if (i<1||i>L.length+1)  return ERROR;
  if (L.length>=L.listsize)
  { newbase=(BElemType *) realloc(L.elem,
            (L.listsize+LISTINCREMENT) *sizeof(BElemType));
    if(!newbase)exit(OVERFLOW);                          //存储分配失败
     L.elem=newbase;                                     //新基址
     L.listsize +=LISTINCREMENT;                         //增加存储容量
  }
  q = &(L.elem[i-1]);            	                  //q为插入位置
  if(L.length>=1)
  for(p = &(L.elem[L.length-1]);p>=q;--p)      *(p+1)=*p;
  *q=e;                                                                  //插入e
  ++L.length;                                             //表长增1
  return OK;
}

int LocateallElem_Sq(SqList_B L,BElemType e, Status (*compare)(BElemType,BElemType),int *find)
{ //在顺序线性表L中查找所有值与e满足compare()的元素的位序
  //若找到,则将所有满足条件的元素的位序放在find[],否则返回0
 int i,k;BElemType *p;
 i = 1;  k=0;                         //i的初值为第1个元素的位序,k为find的下标
 p = L.elem;                         //p的初值为第1个元素的存储位置
 while(i<=L.length )
 {  if((*compare)(*p, e ))
    { find[k]=i; k++;}
    ++i; p++;
 }
 find[k]=0;   //满足条件的位序的结束
 if (k)
     return OK;
 else return 0;
}//LocateElem_Sq

Status GetElem_BSq(SqList_B La,int i,BElemType &e)
{  //线性表La的第i个元素值存于e中
    if(i<1||i>La.length) return ERROR;
    e=La.elem[i-1];
    return OK;
}

Status SetElem_BSq(SqList_B &La,int i,BElemType e)
{   //线性表La的第i个元素值设置为e的值
    if(i<1||i>La.length) return ERROR;
    La.elem[i-1]=e;
    return OK;
}

 int find_book(SqList_B book,char *bookno)      //找到书号bookno在书表中的位序
 { int i;
   BElemType eb;
   for(i=1; i<=book.length; i++)
    { GetElem_BSq(book,i,eb);
      if(strcmp(eb.bookno,bookno)==0)
           return i;
   }
   return 0;                                                      //找不到返回0
 }

void Output_Book(SqList_B book,int pos)       //从第pos本书开始，输出所有图书的信息
{ int j,i;
  ElemType_Book e;
  if(pos>book.length)
  { printf("没有这么多书！\n");
    return ;
  }
  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 余量"," 出版日期");
  for(j=pos; j<=book.length; j++)
  { GetElem_BSq(book,j,e);
    printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
    i=j-pos+1;
    if(i%10==0)
    {pressanykey();
 //    cls();
     if(j<book.length)
         printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 余量"," 出版日期");
    }
  }
  puts("\n");
}

 void OpenBookList(SqList_B &book)   //装入昨天的图书信息（含馆存图书数量）
{
  int i,j,k=0;
  BElemType e;
  FILE *fp;
  fp=fopen("book.txt","r");    //文件中存放了昨天的图书信息（含馆存图书数量）
  if(fp)
  {   k=0;
      while(!feof(fp))
      {fscanf(fp,"%s %s %s %s %d %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,&e.totalnum,&e.borrownum,
                 &e.pubday.year,&e.pubday.month,&e.pubday.day);
       ListInsert_BSq(book,++k,e);
      }
    fclose(fp);
  }
}

int index_bookno(BElemType e,char *info)
{  //查询图书e的书号是否包含info
    if(index(e.bookno,info)) return TRUE;
    return FALSE;
}
int index_author(BElemType e,char *info)
{  //查询图书e的作者是否包含info
    if(index(e.author,info)) return TRUE;
    return FALSE;
}
int index_bookname(BElemType e,char *info)
{  //查询图书e的名称是否包含info
    if(index(e.bookname,info)) return TRUE;
    return FALSE;
}
int index_publisher(BElemType e,char *info)
{  //查询图书e的出版社是否包含info
    if(index(e.publisher,info)) return TRUE;
    return FALSE;
}

void Append_book(SqList_B &book)    //批量添加图书
{
  int i,j,k,pos;
  char filename[50];
  BElemType e;
  FILE *fp;
  printf("\t\t-----------新添一批图书-------\n");
  printf("\t请输入新书文件全名："); gets(filename);//append_book.txt
  fp=fopen(filename,"r");
  if(fp)
  {   k=book.length;
      pos=k+1;
      while(!feof(fp))
      {fscanf(fp,"%s %s %s %s %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,&e.totalnum,
                      &e.pubday.year,&e.pubday.month,&e.pubday.day);
       e.borrownum=e.totalnum;
       ListInsert_BSq(book,++k,e);
      }
    fclose(fp);
    printf("-----------新添加以下图书----------\n");
    Output_Book(book,pos);
  }
  else printf("没有找到这个文件！\n");
}


void book_search_char(SqList_B book,char *info, int (*f)(BElemType,char*) )  //查询图书信息
//输入部分书名，输出所有含部分书名的图书信息
{  int j,count=0;
   int first=0;
   BElemType e;
   for(j=1; j<=book.length; j++)
    { GetElem_BSq(book,j,e);         //检查每一本书
      if((*f)(e,info))               //查询含这部分书名的图书
      {
        count++;                     //数量加1
        if(!first)                   //第一本书输出标题
        {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 余量"," 出版日期");
           first=1;
        }
        //输出图书信息
        printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
        if(count%10==0)              //已输出10本书，换一屏
        {
            pressanykey(); first=0;
        }
      }
   }
   if(count)
       printf("\n\t\t找到%d本书！\n",count);
   else printf("\n\t\n没有找到符合条件的书！\n");
  return;
}
void book_search_have(SqList_B book)
{  //查询还有哪些书可借
    int j,count=0;
    int first=0;
    BElemType e;
    for(j=1; j<=book.length; j++)
       { GetElem_BSq(book,j,e);                   //检查每一本书
         if(e.totalnum>e.borrownum)               //查询存书量>借出量
            { count++;                            //数量加1
              if(!first)                          //第一本书输出标题
                  {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 余量"," 出版日期");
                     first=1;
                  }
              //输出图书信息
              printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
                                e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
              if(count%10==0)              //已输出10本书
                      {          pressanykey(); first=0;       }
            }
        }
    if(count)
        printf("\n\t\t找到%d本书！\n",count);
    else printf("\n\t\n没有可借阅的书！\n");
    return ;
}
void book_search_day(SqList_B book,int year,int month)
{ //根据出版年份和月份查询图书
    int j,count=0;
    int first=0;
    BElemType e;
    for(j=1; j<=book.length; j++)
       { GetElem_BSq(book,j,e);                        //检查每一本书
         if(e.pubday.year==year&&e.pubday.month==month)
            { count++;                     //数量加1
              if(!first)                   //第一本书输出标题
                  {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 余量"," 出版日期");
                     first=1;
                  }
              //输出图书信息
              printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
                                e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
              if(count%10==0)              //已输出10本书
                      {          pressanykey(); first=0;       }
            }
        }
    if(count)
        printf("\n\t\t找到%d本书！\n",count);
    else printf("\n\t\n没有找到图书！\n");
    return ;
}
char book_mana_screen(void)//图书管理主菜单
{   char choice;
    printf("\n\n\t图书信息管理\n");
    printf("1. 来新书了\n");
    printf("2. 图书信息查询\n");
    printf("3. 显示所有图书信息\n");
    printf("0. 退出\n");
    printf("please choice(0-2):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
char book_append_screen(void)//图书添加菜单
{   char choice;
    printf("\n\n\t\t添加图书信息\n");
    printf("\t1. 单本图书信息添加\n");
    printf("\t2. 批量图书信息添加（从文件中）\n");
    printf("\t0. 退出\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
char book_search_screen(void)//图书查询菜单
{   char choice;
    printf("\n\n\t\t查询图书信息\n");
    printf("\t1. 根据出版社查询\n");
    printf("\t2. 根据图书名称查询\n");
    printf("\t3. 根据作者查询\n");
    printf("\t4. 根据出版日期查询\n");
    printf("\t5. 根据书号查询\n");
    printf("\t6. 可借阅图书查询\n");
    printf("\t0. 退出\n");
    printf("\tplease choice(0-6):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
void book_manage_search(SqList_B book)
{
   char c;
   char information_char[50];
   int pub_year,pub_month;
   int (*func_char)(BElemType,char *);
   BElemType e;
   while((c=book_search_screen())!='0')
    switch(c)
       {case '1':  printf("想查哪本书？请输入出版社：");
                   gets(information_char);       //输入全部或部分出版社名
                   func_char=index_publisher;
                   book_search_char(book,information_char,func_char);
                   break;
        case '2':  printf("想查哪本书？请输入书名：");
                   gets(information_char);       //输入全部或部分出版社名
                   func_char=index_bookname;
                   book_search_char(book,information_char,func_char);
                   break;
        case '3':  printf("想查哪本书？请输入作者姓名：");
                   gets(information_char);       //输入全部或部分出版社名
                   func_char=index_author;
                   book_search_char(book,information_char,func_char);
                   break;
        case '4':  printf("想查哪本书？请输入出版时间（年/月）：");
                   scanf("%d/%d",&pub_year,&pub_month);      //输入出版社年份和月份
                   book_search_day(book,pub_year,pub_month);
                   break;
        case '5':  printf("想查哪本书？请输入书号：");
                   gets(information_char);       //输入全部或部分出版社名
                   func_char=index_bookno;
                   book_search_char(book,information_char,func_char);
                   break;
        case '6':  //可借阅图书查询
                   book_search_have(book);
                   break;
       }
    return ;
}
void book_manage_append(SqList_B &book)  //图书增加处理
{
    char c;
    BElemType e;
    while((c=book_append_screen())!='0')
    switch(c)
       {case '1': //增加一本书
                  printf("请输入追加图书的信息：\n");
                  printf("%-6s %-30s %-8s %-20s %4s %8s\n"," 书 号 ","   书   名     "," 作者 "," 出版社 ","数量"," 出版年月日");
                  scanf("%s %s %s %s %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,&e.totalnum,
                      &e.pubday.year,&e.pubday.month,&e.pubday.day);
                  e.borrownum=0;
                  ListInsert_BSq(book,book.length+1,e);
                  break;
        case '2': //从文件中增加一批书
                  Append_book(book);      break;
       }
    return ;
}
void book_manager(SqList_B &book)  //图书管理
{
    char c;
    while((c=book_mana_screen())!='0')
    switch(c)
       {case '1': book_manage_append(book);    break;
        case '2': book_manage_search(book);    break;
        case '3': Output_Book(book,1); break;
       }
    return ;
}

 void save_book(SqList_B  &book)   //保存所有图书信息，退出系统时使用
 { FILE *fp;
   int i;
   BElemType e;
   fp=fopen("today_book.txt","w");
   for(i=1; i<book.length; i++)
   {  GetElem_BSq(book,i,e);
      fprintf(fp,"%s %-s %s %s %d %d %d %d %d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
   }
   GetElem_BSq(book,i,e);      //最后一本书
   fprintf(fp,"%s %-s %s %s %d %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
   fclose(fp);
}


