typedef struct  //ͼ����Ϣ
{
	char  bookno[10];           //���
	char  bookname[50];         //����
	char  author[20];           //����
	char  publisher[20];        //������
	int   totalnum;             //�ݲ�����
	int   borrownum;            //�������
        DATE  pubday;               //��������
}ElemType_Book;

typedef  ElemType_Book BElemType;

typedef   struct
{
  BElemType   *elem;                 //�洢�ռ��ַ
  int         length;                //��ǰ����
  int         listsize;              //��ǰ����Ĵ洢����
}SqList_B;

Status InitList_BSq(SqList_B  &L)
{  //����һ���յ����Ա�L.
  L.elem=(BElemType *)malloc(LIST_INIT_SIZE*sizeof(BElemType));
  if(!L.elem)exit(OVERFLOW);               //�洢����ʧ��
  L.length=0;                                                //�ձ���Ϊ0
  L.listsize=LIST_INIT_SIZE;                  //��ʼ�洢����
  return OK;
}//InitList_BSq

Status DestroyList_BSq(SqList_B  &L)
{  //����һ�����Ա�L.
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
    if(!newbase)exit(OVERFLOW);                          //�洢����ʧ��
     L.elem=newbase;                                     //�»�ַ
     L.listsize +=LISTINCREMENT;                         //���Ӵ洢����
  }
  q = &(L.elem[i-1]);            	                  //qΪ����λ��
  if(L.length>=1)
  for(p = &(L.elem[L.length-1]);p>=q;--p)      *(p+1)=*p;
  *q=e;                                                                  //����e
  ++L.length;                                             //����1
  return OK;
}

int LocateallElem_Sq(SqList_B L,BElemType e, Status (*compare)(BElemType,BElemType),int *find)
{ //��˳�����Ա�L�в�������ֵ��e����compare()��Ԫ�ص�λ��
  //���ҵ�,����������������Ԫ�ص�λ�����find[],���򷵻�0
 int i,k;BElemType *p;
 i = 1;  k=0;                         //i�ĳ�ֵΪ��1��Ԫ�ص�λ��,kΪfind���±�
 p = L.elem;                         //p�ĳ�ֵΪ��1��Ԫ�صĴ洢λ��
 while(i<=L.length )
 {  if((*compare)(*p, e ))
    { find[k]=i; k++;}
    ++i; p++;
 }
 find[k]=0;   //����������λ��Ľ���
 if (k)
     return OK;
 else return 0;
}//LocateElem_Sq

Status GetElem_BSq(SqList_B La,int i,BElemType &e)
{  //���Ա�La�ĵ�i��Ԫ��ֵ����e��
    if(i<1||i>La.length) return ERROR;
    e=La.elem[i-1];
    return OK;
}

Status SetElem_BSq(SqList_B &La,int i,BElemType e)
{   //���Ա�La�ĵ�i��Ԫ��ֵ����Ϊe��ֵ
    if(i<1||i>La.length) return ERROR;
    La.elem[i-1]=e;
    return OK;
}

 int find_book(SqList_B book,char *bookno)      //�ҵ����bookno������е�λ��
 { int i;
   BElemType eb;
   for(i=1; i<=book.length; i++)
    { GetElem_BSq(book,i,eb);
      if(strcmp(eb.bookno,bookno)==0)
           return i;
   }
   return 0;                                                      //�Ҳ�������0
 }

void Output_Book(SqList_B book,int pos)       //�ӵ�pos���鿪ʼ���������ͼ�����Ϣ
{ int j,i;
  ElemType_Book e;
  if(pos>book.length)
  { printf("û����ô���飡\n");
    return ;
  }
  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����"," ��������");
  for(j=pos; j<=book.length; j++)
  { GetElem_BSq(book,j,e);
    printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
    i=j-pos+1;
    if(i%10==0)
    {pressanykey();
 //    cls();
     if(j<book.length)
         printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����"," ��������");
    }
  }
  puts("\n");
}

 void OpenBookList(SqList_B &book)   //װ�������ͼ����Ϣ�����ݴ�ͼ��������
{
  int i,j,k=0;
  BElemType e;
  FILE *fp;
  fp=fopen("book.txt","r");    //�ļ��д���������ͼ����Ϣ�����ݴ�ͼ��������
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
{  //��ѯͼ��e������Ƿ����info
    if(index(e.bookno,info)) return TRUE;
    return FALSE;
}
int index_author(BElemType e,char *info)
{  //��ѯͼ��e�������Ƿ����info
    if(index(e.author,info)) return TRUE;
    return FALSE;
}
int index_bookname(BElemType e,char *info)
{  //��ѯͼ��e�������Ƿ����info
    if(index(e.bookname,info)) return TRUE;
    return FALSE;
}
int index_publisher(BElemType e,char *info)
{  //��ѯͼ��e�ĳ������Ƿ����info
    if(index(e.publisher,info)) return TRUE;
    return FALSE;
}

void Append_book(SqList_B &book)    //�������ͼ��
{
  int i,j,k,pos;
  char filename[50];
  BElemType e;
  FILE *fp;
  printf("\t\t-----------����һ��ͼ��-------\n");
  printf("\t�����������ļ�ȫ����"); gets(filename);//append_book.txt
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
    printf("-----------���������ͼ��----------\n");
    Output_Book(book,pos);
  }
  else printf("û���ҵ�����ļ���\n");
}


void book_search_char(SqList_B book,char *info, int (*f)(BElemType,char*) )  //��ѯͼ����Ϣ
//���벿��������������к�����������ͼ����Ϣ
{  int j,count=0;
   int first=0;
   BElemType e;
   for(j=1; j<=book.length; j++)
    { GetElem_BSq(book,j,e);         //���ÿһ����
      if((*f)(e,info))               //��ѯ���ⲿ��������ͼ��
      {
        count++;                     //������1
        if(!first)                   //��һ�����������
        {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����"," ��������");
           first=1;
        }
        //���ͼ����Ϣ
        printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
        if(count%10==0)              //�����10���飬��һ��
        {
            pressanykey(); first=0;
        }
      }
   }
   if(count)
       printf("\n\t\t�ҵ�%d���飡\n",count);
   else printf("\n\t\nû���ҵ������������飡\n");
  return;
}
void book_search_have(SqList_B book)
{  //��ѯ������Щ��ɽ�
    int j,count=0;
    int first=0;
    BElemType e;
    for(j=1; j<=book.length; j++)
       { GetElem_BSq(book,j,e);                   //���ÿһ����
         if(e.totalnum>e.borrownum)               //��ѯ������>�����
            { count++;                            //������1
              if(!first)                          //��һ�����������
                  {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����"," ��������");
                     first=1;
                  }
              //���ͼ����Ϣ
              printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
                                e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
              if(count%10==0)              //�����10����
                      {          pressanykey(); first=0;       }
            }
        }
    if(count)
        printf("\n\t\t�ҵ�%d���飡\n",count);
    else printf("\n\t\nû�пɽ��ĵ��飡\n");
    return ;
}
void book_search_day(SqList_B book,int year,int month)
{ //���ݳ�����ݺ��·ݲ�ѯͼ��
    int j,count=0;
    int first=0;
    BElemType e;
    for(j=1; j<=book.length; j++)
       { GetElem_BSq(book,j,e);                        //���ÿһ����
         if(e.pubday.year==year&&e.pubday.month==month)
            { count++;                     //������1
              if(!first)                   //��һ�����������
                  {  printf("%-6s %-30s %-8s %-20s %4s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����"," ��������");
                     first=1;
                  }
              //���ͼ����Ϣ
              printf("%-6s %-30s %-8s %-20s %3d    %3d   %4d-%2d-%2d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
                                e.totalnum-e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
              if(count%10==0)              //�����10����
                      {          pressanykey(); first=0;       }
            }
        }
    if(count)
        printf("\n\t\t�ҵ�%d���飡\n",count);
    else printf("\n\t\nû���ҵ�ͼ�飡\n");
    return ;
}
char book_mana_screen(void)//ͼ��������˵�
{   char choice;
    printf("\n\n\tͼ����Ϣ����\n");
    printf("1. ��������\n");
    printf("2. ͼ����Ϣ��ѯ\n");
    printf("3. ��ʾ����ͼ����Ϣ\n");
    printf("0. �˳�\n");
    printf("please choice(0-2):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
char book_append_screen(void)//ͼ����Ӳ˵�
{   char choice;
    printf("\n\n\t\t���ͼ����Ϣ\n");
    printf("\t1. ����ͼ����Ϣ���\n");
    printf("\t2. ����ͼ����Ϣ��ӣ����ļ��У�\n");
    printf("\t0. �˳�\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
char book_search_screen(void)//ͼ���ѯ�˵�
{   char choice;
    printf("\n\n\t\t��ѯͼ����Ϣ\n");
    printf("\t1. ���ݳ������ѯ\n");
    printf("\t2. ����ͼ�����Ʋ�ѯ\n");
    printf("\t3. �������߲�ѯ\n");
    printf("\t4. ���ݳ������ڲ�ѯ\n");
    printf("\t5. ������Ų�ѯ\n");
    printf("\t6. �ɽ���ͼ���ѯ\n");
    printf("\t0. �˳�\n");
    printf("\tplease choice(0-6):");
    choice=getche(); printf("\n");         //���ѡ��
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
       {case '1':  printf("����ı��飿����������磺");
                   gets(information_char);       //����ȫ���򲿷ֳ�������
                   func_char=index_publisher;
                   book_search_char(book,information_char,func_char);
                   break;
        case '2':  printf("����ı��飿������������");
                   gets(information_char);       //����ȫ���򲿷ֳ�������
                   func_char=index_bookname;
                   book_search_char(book,information_char,func_char);
                   break;
        case '3':  printf("����ı��飿����������������");
                   gets(information_char);       //����ȫ���򲿷ֳ�������
                   func_char=index_author;
                   book_search_char(book,information_char,func_char);
                   break;
        case '4':  printf("����ı��飿���������ʱ�䣨��/�£���");
                   scanf("%d/%d",&pub_year,&pub_month);      //�����������ݺ��·�
                   book_search_day(book,pub_year,pub_month);
                   break;
        case '5':  printf("����ı��飿��������ţ�");
                   gets(information_char);       //����ȫ���򲿷ֳ�������
                   func_char=index_bookno;
                   book_search_char(book,information_char,func_char);
                   break;
        case '6':  //�ɽ���ͼ���ѯ
                   book_search_have(book);
                   break;
       }
    return ;
}
void book_manage_append(SqList_B &book)  //ͼ�����Ӵ���
{
    char c;
    BElemType e;
    while((c=book_append_screen())!='0')
    switch(c)
       {case '1': //����һ����
                  printf("������׷��ͼ�����Ϣ��\n");
                  printf("%-6s %-30s %-8s %-20s %4s %8s\n"," �� �� ","   ��   ��     "," ���� "," ������ ","����"," ����������");
                  scanf("%s %s %s %s %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,&e.totalnum,
                      &e.pubday.year,&e.pubday.month,&e.pubday.day);
                  e.borrownum=0;
                  ListInsert_BSq(book,book.length+1,e);
                  break;
        case '2': //���ļ�������һ����
                  Append_book(book);      break;
       }
    return ;
}
void book_manager(SqList_B &book)  //ͼ�����
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

 void save_book(SqList_B  &book)   //��������ͼ����Ϣ���˳�ϵͳʱʹ��
 { FILE *fp;
   int i;
   BElemType e;
   fp=fopen("today_book.txt","w");
   for(i=1; i<book.length; i++)
   {  GetElem_BSq(book,i,e);
      fprintf(fp,"%s %-s %s %s %d %d %d %d %d\n",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
   }
   GetElem_BSq(book,i,e);      //���һ����
   fprintf(fp,"%s %-s %s %s %d %d %d %d %d",e.bookno,e.bookname,e.author,e.publisher,e.totalnum,
              e.borrownum,e.pubday.year,e.pubday.month,e.pubday.day);
   fclose(fp);
}


