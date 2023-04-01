//
typedef struct student  //学生结构体
{ char studentno[13];       //学号
  char studentname[16];     //姓名
  char studentmajor[18];    //专业
  char studentclass[10];    //班级
  char studentmobile[20];   //手机
}ElemType_Stu;

typedef ElemType_Stu SElemType;

typedef   struct                     //定义学生信息顺序表
{
  SElemType   *elem;                 //存储空间基址
  int         length;                //当前长度
  int         listsize;              //当前分配的存储容量
}SqList_S;

Status InitList_SSq(SqList_S  &L)
{  //构造一个空的线性表L.
  L.elem=(SElemType *)malloc(LIST_INIT_SIZE*sizeof(SElemType));
  if(!L.elem)exit(OVERFLOW);               //存储分配失败
  L.length=0;                                                //空表长度为0
  L.listsize=LIST_INIT_SIZE;                  //初始存储容量
  return OK;
}//InitList_SSq

Status DestroyList_SSq(SqList_S  &L)
{  //销毁一个线性表L.
  free(L.elem);
  L.length=0;
  L.listsize=0;
  return OK;
}

int ListLength_SSq(SqList_S L)
{ return L.length;}

Status ListInsert_SSq(SqList_S &L,int i,SElemType e)  //在线性表的第i个元素前插入数据e
{ SElemType *p,*q,*newbase;
  if (i<1||i>L.length+1)  return ERROR;
  if (L.length>=L.listsize)
  { newbase=(SElemType *) realloc(L.elem,
            (L.listsize+LISTINCREMENT) *sizeof(SElemType));
    if(!newbase)exit(OVERFLOW);                          //存储分配失败
     L.elem=newbase;                                     //新基址
     L.listsize +=LISTINCREMENT;                         //增加存储容量
  }
  q = &(L.elem[i-1]);            	                  //q为插入位置
  if(L.length>=1)
  for(p = &(L.elem[L.length-1]);p>=q;--p)      *(p+1)=*p;  //插入点后数据都往后挪
  *q=e;                                                    //插入e
  ++L.length;                                              //表长增1
  return OK;
}

Status ListDelete_SSq(SqList_S &L,int i ,SElemType &e)
{  //在顺序线性表L中删除第i个元素,并用e返回其值
   //i的合法值为1≤i≤ListLength_Sq(L)
    SElemType *p,*q;
  if((i<1)||(i>L.length))return ERROR;               //i值不合法
  p = &(L.elem[i-1]);                                //p为被删除元素的位置
  e = *p;                                            //被删除元素的值赋给e
  q = L.elem+L.length-1;                             //表尾元素的位置
  for(++p;p<=q;++p) *(p-1)=*p;                       //被删除元素之后的元素左移
  --L.length;                                        //表长减1
  return OK;
}//ListDelete_sq

int equal_stuno(SElemType a,SElemType b)
{   //比较学生a、b的学号是否相等，相等返回真，负责返回假
    if(strcmp(a.studentno,b.studentno)==0) return TRUE;
    return FALSE;
}
int equal_stuma_or_cl(SElemType a,SElemType b)
{  //比较学生a、b的专业或班级是否相等，相等返回真，负责返回假
    if(strcmp(a.studentmajor,b.studentmajor)==0||strcmp(a.studentclass,b.studentclass)==0) return TRUE;
    return FALSE;
}

int LocateAllElem_SSq(SqList_S L,SElemType e, Status (*compare)(SElemType,SElemType),int *find)
{ //在顺序线性表L中查找所有值与e满足compare()的元素的位序
  //若找到,返回OK,并将所有满足条件的元素的位序放在find[],否则返回0
 int i,k;SElemType *p;
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
 else return ERROR;
}//LocateElem_Sq

Status GetElem_SSq(SqList_S La,int i,SElemType &e)
{  //线性表La的第i个元素值存于e中
    if(i<1||i>La.length) return ERROR;
    e=La.elem[i-1];
    return OK;
}

Status SetElem_SSq(SqList_S &La,int i,SElemType e)
{  //线性表La的第i个元素值设置为e的值
    if(i<1||i>La.length) return ERROR;
    La.elem[i-1]=e;
    return OK;
}

int index_stuno(SElemType e,char *info)
{   //查询学生e的学号是否包含info
    if(index(e.studentno,info)) return TRUE;
    return FALSE;
}

int find_student(SqList_S stu,char *stuno)      //找到学号为stuno的学生在学生表中的位序
 { int i;
   SElemType es;
   for(i=1; i<=stu.length; i++)                  //依次取出每个学生数据
    { GetElem_SSq(stu,i,es);
      if(strcmp(es.studentno,stuno)==0)
           return i;
   }
   return 0;                                                      //找不到返回0
 }

int index_stuname(SElemType e,char *info)
{  //查询学生e的姓名是否包含info
    if(index(e.studentname,info)) return TRUE;
    return FALSE;
}
int index_stumajor(SElemType e,char *info)
{   //查询学生e的专业是否包含info
    if(index(e.studentmajor,info)) return TRUE;
    return FALSE;
}
int index_stuclass(SElemType e,char *info)
{   //查询学生e的班级是否包含info
    if(index(e.studentclass,info)) return TRUE;
    return FALSE;
}

int index_stumobile(SElemType e,char *info)
{   //查询学生e的手机是否包含info
    if(index(e.studentmobile,info)) return TRUE;
    return FALSE;
}

 void OpenStuList(SqList_S &stu)   //装入昨天的学生信息
{
  int i,j,k=0;
  SElemType e;
  FILE *fp;
  fp=fopen("student.txt","r");    //文件中存放了昨天的学生信息
  if(fp)
  {   k=0;
      while(!feof(fp))
      {fscanf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
       ListInsert_SSq(stu,++k,e);        //加入线性表
      }
    fclose(fp);
  }
}
Status stu_manage_output(SqList_S stu,int pos)       //从第pos个学生开始，输出学生信息
{ int j,i;
  SElemType e;
  if(pos>stu.length)
    { printf("没有这么多学生！\n");
      return ERROR;
    }
  printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
  for(j=pos; j<=stu.length; j++)
  { GetElem_SSq(stu,j,e);
    printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
    i=j-pos+1;
    if(i%20==0)
    {pressanykey();
     system("CLS");
     if(j<stu.length)
         printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
    }
  }
  puts("\n");
  return OK;
}
char stu_append_screen(void)//学生信息添加菜单
{   char choice;
    printf("\n\n\t\t--------新生入学---------\n");
    printf("\t1. 添加一个新生信息\n");
    printf("\t2. 批量添加新生信息（从文件中）\n");
    printf("\t0. 退出\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
char stu_mana_screen(void)     //学生信息管理主菜单
{
    char choice;
    printf("\n-----学生管理-------\n");
    printf("1.新生入学\n");
    printf("2.学生毕业\n");
    printf("3.输出学生信息\n");
    printf("4.同学信息查询\n");
    printf("5.修改学生信息\n");
    printf("0.退出\n");
    printf("请选择(0-5):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}

void Append_stu(SqList_S &stu)    //从文件中批量添加学生信息
{
  int i,j,k,pos;
  char filename[50];
  SElemType e;
  FILE *fp;
  printf("\t\t-----------新入学一批学生-------\n");
  printf("\t请输入新生文件全名："); gets(filename);  //输入文件名append_stu
  fp=fopen(filename,"r");                            //打开文件，准备读
  if(fp)
  {   k=stu.length;
      pos=k+1;
      while(!feof(fp))                                   //只要文件没有读完
      {fscanf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
       ListInsert_SSq(stu,++k,e);
      }
    fclose(fp);
    printf("-----------新添加以下新生----------\n");
    stu_manage_output(stu,pos);                           //输出新增加的学生信息
  }
  else printf("没有找到这个文件！\n");
}
void stu_manage_append(SqList_S &stu)
{   char c;
    SElemType e;
    while((c=stu_append_screen())!='0')
    switch(c)
       {case '1': //增加一个学生信息
                  printf("\t请输入一位新生的信息：\n");
                  printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
                  scanf("%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                  ListInsert_SSq(stu,stu.length+1,e);
                  break;
        case '2': //从文件中增加一批学生信息
                  Append_stu(stu);      break;
       }
    return ;
}
char stu_search_screen(void)//学生信息查询菜单
{   char choice;
    printf("\n\n\t\t查询学生信息\n");
    printf("\t1. 根据学号查询\n");
    printf("\t2. 根据学生姓名查询\n");
    printf("\t3. 根据专业查询\n");
    printf("\t4. 根据班级查询\n");
    printf("\t5. 根据手机查询\n");
    printf("\t0. 退出\n");
    printf("\tplease choice(0-5):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
void stu_search_char(SqList_S stu,char *info, int (*f)(SElemType,char*) )  //查询学生信息
//输入部分学生信息，输出所有含部分信息的学生
//只能查询字符串类型的信息
{  int j,count=0;
   int first=0,find=0;
   SElemType e;
   for(j=1; j<=stu.length; j++)
    { GetElem_SSq(stu,j,e);          //检查每一个学生
      if((*f)(e,info))               //查询含这部分信息的学生
      { find=1;                      //找到了
        count++;                     //数量加1
        if(!first)                   //第一本书输出标题
        {  printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
           first=1;
        }
        //输出学生信息
        printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
        if(count%20==0)              //已输出20本书，换一屏
        {
            pressanykey(); first=0;
        }
      }
   }
   if(count)
       printf("\n\t\t找到%d个学生！\n",count);
   else printf("\n\t\n没有找到符合条件的学生！\n");
  return;
}

void stu_manage_search(SqList_S stu)
{  //学生信息查询处理程序
   char c;
   char information_char[50];
   int (*func_char)(SElemType,char *);
   SElemType e;
   while((c=stu_search_screen())!='0')
    switch(c)
       {case '1':  //根据学号查询
                   printf("想查哪位同学？请输入学号：");
                   gets(information_char);       //输入全部或部分学号
                   func_char=index_stuno;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '2':  //根据姓名查询
                   printf("想查哪位同学？请输入姓名：");
                   gets(information_char);       //输入全部或部分姓名
                   func_char=index_stuname;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '3':  //根据专业查询
                   printf("想查哪位同学？请输入专业：");
                   gets(information_char);       //输入全部或部分专业名称
                   func_char=index_stumajor;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '4':  //根据班级查询
                   printf("想查哪位同学？请输入班级：");
                   gets(information_char);       //输入全部或部分班级名
                   func_char=index_stuclass;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '5':  //根据手机号查询
                   printf("想查哪位同学？请输入手机号：");
                   gets(information_char);       //输入全部或部分手机号
                   func_char=index_stumobile;
                   stu_search_char(stu,information_char,func_char);
                   break;
       }
    return ;
}
char stu_delete_screen(void)//学生信息删除菜单
{   char choice;
    printf("\n\n\t\t--------学生毕业了---------\n");   //显示毕业菜单
    printf("\t1. 一个学生毕业\n");
    printf("\t2. 一批学生毕业\n");
    printf("\t0. 退出\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //获得选择
    return choice;
}
void stu_manage_delete(SqList_S &stu)//学生信息删除处理
{   char c,yesno;
    char stuinfo[20];
    int find[LIST_INIT_SIZE];
    int position,i;
    SElemType e;
    while((c=stu_delete_screen())!='0')
    switch(c)
       {case '1': //根据学号删除一个学生
                  printf("\t请输入毕业同学的学号:");
                  fflush(stdin);
                  gets(stuinfo);
                  strcpy(e.studentno,stuinfo);
                  if(LocateAllElem_SSq(stu,e,equal_stuno,find))
                  { //找到该同学
                    printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
                    position=find[0];
                    GetElem_SSq(stu,position,e);
                    printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                    printf("是这个同学毕业吗？确认(y/n)");
                    yesno=getche();
                    yesno=toupper(yesno);
                    if(yesno=='Y')
                        ListDelete_SSq(stu,position,e);
                  }
                  else printf("没有找到该同学！\n");
                  break;
        case '2': //根据班级或专业删除一批学生
                  printf("\t请输入毕业同学的班级名称或专业:");
                  fflush(stdin);
                  gets(stuinfo);
                  strcpy(e.studentmajor,stuinfo); strcpy(e.studentclass,stuinfo);
                  if(LocateAllElem_SSq(stu,e,equal_stuma_or_cl,find))
                  { //找到毕业同学
                    printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
                    i=0;
                    while(position=find[i])  //find[i]=0表示没有符合推荐的学生了
                    {  GetElem_SSq(stu,position,e);
                       printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                       i++;
                    }
                    printf("这些同学都毕业吗？确认(y/n)");
                    yesno=getche();
                    yesno=toupper(yesno);
                    if(yesno=='Y')
                        i--;               //反过来依次删除
                        while(i>=0)
                        {position=find[i];
                         ListDelete_SSq(stu,position,e);
                         i--;
                        }
                  }
                  else printf("没有找到同学！\n");
                  break;
       }
    return ;
}

void stu_manage_update(SqList_S &stu)  //根据学号修改一个学生的信息，学号不能修改
{   char stuinfo[50],yesno;
    SElemType e;
    int position,find[LIST_INIT_SIZE];
    printf("\t修改学生数据，每次只能修改一个学生数据，学生的学号不可修改！\n");
    printf("\t请输入被修改数据同学的学号，输入0表示放弃修改！");
    gets(stuinfo);
    if(stuinfo[0]=='0') return ;
    strcpy(e.studentno,stuinfo);
    if(LocateAllElem_SSq(stu,e,equal_stuno,find))
       { //找到该同学
         printf("%-10s %-9s %-18s   %-10s %-12s \n"," 学 号 ","  姓  名  "," 专    业 ","班 级 ","手   机");
         position=find[0];
         GetElem_SSq(stu,position,e);
         printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
         printf("确定修改这个同学信息？(y/n)");
         yesno=getche();
         yesno=toupper(yesno);
         if(yesno=='Y')
         { printf("\n\n\t姓名修改为（不修改按回车）："); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentname,stuinfo);
           printf("\t专业修改为（不修改按回车）："); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentmajor,stuinfo);
           printf("\t班级修改为（不修改按回车）："); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentclass,stuinfo);
           printf("\t手机修改为（不修改按回车）："); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentmobile,stuinfo);
           printf("该同学信息修改为：\n");
           printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
           SetElem_SSq(stu,position,e);
         }
    }
    else printf("没有找到该同学！\n");
}
void stu_manager(SqList_S &stu)
{  //学生信息管理
    char c;
    while((c=stu_mana_screen())!='0')
    switch(c)
       {case '1': stu_manage_append(stu);    break;  //增加学生信息
        case '2': stu_manage_delete(stu);    break;  //删除学生信息
        case '3': stu_manage_output(stu,1); break;   //输出学生信息
        case '4': stu_manage_search(stu);    break;  //查询学生信息
        case '5': stu_manage_update(stu); break;     //修改学生信息
       }
    return ;
}

 void save_stu(SqList_S  &stu)  //保存所有学生信息，退出系统时使用
 { FILE *fp;
   int i;
   SElemType e;
   fp=fopen("today_stu.txt","w");
   for(i=1; i<stu.length; i++)
   {  GetElem_SSq(stu,i,e);
      fprintf(fp,"%s %s %s %s %s\n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
   }
   GetElem_SSq(stu,i,e);      //最后一个学生
   fprintf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
   fclose(fp);
}

