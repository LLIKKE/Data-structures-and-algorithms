//
typedef struct student  //ѧ���ṹ��
{ char studentno[13];       //ѧ��
  char studentname[16];     //����
  char studentmajor[18];    //רҵ
  char studentclass[10];    //�༶
  char studentmobile[20];   //�ֻ�
}ElemType_Stu;

typedef ElemType_Stu SElemType;

typedef   struct                     //����ѧ����Ϣ˳���
{
  SElemType   *elem;                 //�洢�ռ��ַ
  int         length;                //��ǰ����
  int         listsize;              //��ǰ����Ĵ洢����
}SqList_S;

Status InitList_SSq(SqList_S  &L)
{  //����һ���յ����Ա�L.
  L.elem=(SElemType *)malloc(LIST_INIT_SIZE*sizeof(SElemType));
  if(!L.elem)exit(OVERFLOW);               //�洢����ʧ��
  L.length=0;                                                //�ձ���Ϊ0
  L.listsize=LIST_INIT_SIZE;                  //��ʼ�洢����
  return OK;
}//InitList_SSq

Status DestroyList_SSq(SqList_S  &L)
{  //����һ�����Ա�L.
  free(L.elem);
  L.length=0;
  L.listsize=0;
  return OK;
}

int ListLength_SSq(SqList_S L)
{ return L.length;}

Status ListInsert_SSq(SqList_S &L,int i,SElemType e)  //�����Ա�ĵ�i��Ԫ��ǰ��������e
{ SElemType *p,*q,*newbase;
  if (i<1||i>L.length+1)  return ERROR;
  if (L.length>=L.listsize)
  { newbase=(SElemType *) realloc(L.elem,
            (L.listsize+LISTINCREMENT) *sizeof(SElemType));
    if(!newbase)exit(OVERFLOW);                          //�洢����ʧ��
     L.elem=newbase;                                     //�»�ַ
     L.listsize +=LISTINCREMENT;                         //���Ӵ洢����
  }
  q = &(L.elem[i-1]);            	                  //qΪ����λ��
  if(L.length>=1)
  for(p = &(L.elem[L.length-1]);p>=q;--p)      *(p+1)=*p;  //���������ݶ�����Ų
  *q=e;                                                    //����e
  ++L.length;                                              //����1
  return OK;
}

Status ListDelete_SSq(SqList_S &L,int i ,SElemType &e)
{  //��˳�����Ա�L��ɾ����i��Ԫ��,����e������ֵ
   //i�ĺϷ�ֵΪ1��i��ListLength_Sq(L)
    SElemType *p,*q;
  if((i<1)||(i>L.length))return ERROR;               //iֵ���Ϸ�
  p = &(L.elem[i-1]);                                //pΪ��ɾ��Ԫ�ص�λ��
  e = *p;                                            //��ɾ��Ԫ�ص�ֵ����e
  q = L.elem+L.length-1;                             //��βԪ�ص�λ��
  for(++p;p<=q;++p) *(p-1)=*p;                       //��ɾ��Ԫ��֮���Ԫ������
  --L.length;                                        //����1
  return OK;
}//ListDelete_sq

int equal_stuno(SElemType a,SElemType b)
{   //�Ƚ�ѧ��a��b��ѧ���Ƿ���ȣ���ȷ����棬���𷵻ؼ�
    if(strcmp(a.studentno,b.studentno)==0) return TRUE;
    return FALSE;
}
int equal_stuma_or_cl(SElemType a,SElemType b)
{  //�Ƚ�ѧ��a��b��רҵ��༶�Ƿ���ȣ���ȷ����棬���𷵻ؼ�
    if(strcmp(a.studentmajor,b.studentmajor)==0||strcmp(a.studentclass,b.studentclass)==0) return TRUE;
    return FALSE;
}

int LocateAllElem_SSq(SqList_S L,SElemType e, Status (*compare)(SElemType,SElemType),int *find)
{ //��˳�����Ա�L�в�������ֵ��e����compare()��Ԫ�ص�λ��
  //���ҵ�,����OK,������������������Ԫ�ص�λ�����find[],���򷵻�0
 int i,k;SElemType *p;
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
 else return ERROR;
}//LocateElem_Sq

Status GetElem_SSq(SqList_S La,int i,SElemType &e)
{  //���Ա�La�ĵ�i��Ԫ��ֵ����e��
    if(i<1||i>La.length) return ERROR;
    e=La.elem[i-1];
    return OK;
}

Status SetElem_SSq(SqList_S &La,int i,SElemType e)
{  //���Ա�La�ĵ�i��Ԫ��ֵ����Ϊe��ֵ
    if(i<1||i>La.length) return ERROR;
    La.elem[i-1]=e;
    return OK;
}

int index_stuno(SElemType e,char *info)
{   //��ѯѧ��e��ѧ���Ƿ����info
    if(index(e.studentno,info)) return TRUE;
    return FALSE;
}

int find_student(SqList_S stu,char *stuno)      //�ҵ�ѧ��Ϊstuno��ѧ����ѧ�����е�λ��
 { int i;
   SElemType es;
   for(i=1; i<=stu.length; i++)                  //����ȡ��ÿ��ѧ������
    { GetElem_SSq(stu,i,es);
      if(strcmp(es.studentno,stuno)==0)
           return i;
   }
   return 0;                                                      //�Ҳ�������0
 }

int index_stuname(SElemType e,char *info)
{  //��ѯѧ��e�������Ƿ����info
    if(index(e.studentname,info)) return TRUE;
    return FALSE;
}
int index_stumajor(SElemType e,char *info)
{   //��ѯѧ��e��רҵ�Ƿ����info
    if(index(e.studentmajor,info)) return TRUE;
    return FALSE;
}
int index_stuclass(SElemType e,char *info)
{   //��ѯѧ��e�İ༶�Ƿ����info
    if(index(e.studentclass,info)) return TRUE;
    return FALSE;
}

int index_stumobile(SElemType e,char *info)
{   //��ѯѧ��e���ֻ��Ƿ����info
    if(index(e.studentmobile,info)) return TRUE;
    return FALSE;
}

 void OpenStuList(SqList_S &stu)   //װ�������ѧ����Ϣ
{
  int i,j,k=0;
  SElemType e;
  FILE *fp;
  fp=fopen("student.txt","r");    //�ļ��д���������ѧ����Ϣ
  if(fp)
  {   k=0;
      while(!feof(fp))
      {fscanf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
       ListInsert_SSq(stu,++k,e);        //�������Ա�
      }
    fclose(fp);
  }
}
Status stu_manage_output(SqList_S stu,int pos)       //�ӵ�pos��ѧ����ʼ�����ѧ����Ϣ
{ int j,i;
  SElemType e;
  if(pos>stu.length)
    { printf("û����ô��ѧ����\n");
      return ERROR;
    }
  printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
  for(j=pos; j<=stu.length; j++)
  { GetElem_SSq(stu,j,e);
    printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
    i=j-pos+1;
    if(i%20==0)
    {pressanykey();
     system("CLS");
     if(j<stu.length)
         printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
    }
  }
  puts("\n");
  return OK;
}
char stu_append_screen(void)//ѧ����Ϣ��Ӳ˵�
{   char choice;
    printf("\n\n\t\t--------������ѧ---------\n");
    printf("\t1. ���һ��������Ϣ\n");
    printf("\t2. �������������Ϣ�����ļ��У�\n");
    printf("\t0. �˳�\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
char stu_mana_screen(void)     //ѧ����Ϣ�������˵�
{
    char choice;
    printf("\n-----ѧ������-------\n");
    printf("1.������ѧ\n");
    printf("2.ѧ����ҵ\n");
    printf("3.���ѧ����Ϣ\n");
    printf("4.ͬѧ��Ϣ��ѯ\n");
    printf("5.�޸�ѧ����Ϣ\n");
    printf("0.�˳�\n");
    printf("��ѡ��(0-5):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}

void Append_stu(SqList_S &stu)    //���ļ����������ѧ����Ϣ
{
  int i,j,k,pos;
  char filename[50];
  SElemType e;
  FILE *fp;
  printf("\t\t-----------����ѧһ��ѧ��-------\n");
  printf("\t�����������ļ�ȫ����"); gets(filename);  //�����ļ���append_stu
  fp=fopen(filename,"r");                            //���ļ���׼����
  if(fp)
  {   k=stu.length;
      pos=k+1;
      while(!feof(fp))                                   //ֻҪ�ļ�û�ж���
      {fscanf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
       ListInsert_SSq(stu,++k,e);
      }
    fclose(fp);
    printf("-----------�������������----------\n");
    stu_manage_output(stu,pos);                           //��������ӵ�ѧ����Ϣ
  }
  else printf("û���ҵ�����ļ���\n");
}
void stu_manage_append(SqList_S &stu)
{   char c;
    SElemType e;
    while((c=stu_append_screen())!='0')
    switch(c)
       {case '1': //����һ��ѧ����Ϣ
                  printf("\t������һλ��������Ϣ��\n");
                  printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
                  scanf("%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                  ListInsert_SSq(stu,stu.length+1,e);
                  break;
        case '2': //���ļ�������һ��ѧ����Ϣ
                  Append_stu(stu);      break;
       }
    return ;
}
char stu_search_screen(void)//ѧ����Ϣ��ѯ�˵�
{   char choice;
    printf("\n\n\t\t��ѯѧ����Ϣ\n");
    printf("\t1. ����ѧ�Ų�ѯ\n");
    printf("\t2. ����ѧ��������ѯ\n");
    printf("\t3. ����רҵ��ѯ\n");
    printf("\t4. ���ݰ༶��ѯ\n");
    printf("\t5. �����ֻ���ѯ\n");
    printf("\t0. �˳�\n");
    printf("\tplease choice(0-5):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
void stu_search_char(SqList_S stu,char *info, int (*f)(SElemType,char*) )  //��ѯѧ����Ϣ
//���벿��ѧ����Ϣ��������к�������Ϣ��ѧ��
//ֻ�ܲ�ѯ�ַ������͵���Ϣ
{  int j,count=0;
   int first=0,find=0;
   SElemType e;
   for(j=1; j<=stu.length; j++)
    { GetElem_SSq(stu,j,e);          //���ÿһ��ѧ��
      if((*f)(e,info))               //��ѯ���ⲿ����Ϣ��ѧ��
      { find=1;                      //�ҵ���
        count++;                     //������1
        if(!first)                   //��һ�����������
        {  printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
           first=1;
        }
        //���ѧ����Ϣ
        printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
        if(count%20==0)              //�����20���飬��һ��
        {
            pressanykey(); first=0;
        }
      }
   }
   if(count)
       printf("\n\t\t�ҵ�%d��ѧ����\n",count);
   else printf("\n\t\nû���ҵ�����������ѧ����\n");
  return;
}

void stu_manage_search(SqList_S stu)
{  //ѧ����Ϣ��ѯ�������
   char c;
   char information_char[50];
   int (*func_char)(SElemType,char *);
   SElemType e;
   while((c=stu_search_screen())!='0')
    switch(c)
       {case '1':  //����ѧ�Ų�ѯ
                   printf("�����λͬѧ��������ѧ�ţ�");
                   gets(information_char);       //����ȫ���򲿷�ѧ��
                   func_char=index_stuno;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '2':  //����������ѯ
                   printf("�����λͬѧ��������������");
                   gets(information_char);       //����ȫ���򲿷�����
                   func_char=index_stuname;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '3':  //����רҵ��ѯ
                   printf("�����λͬѧ��������רҵ��");
                   gets(information_char);       //����ȫ���򲿷�רҵ����
                   func_char=index_stumajor;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '4':  //���ݰ༶��ѯ
                   printf("�����λͬѧ��������༶��");
                   gets(information_char);       //����ȫ���򲿷ְ༶��
                   func_char=index_stuclass;
                   stu_search_char(stu,information_char,func_char);
                   break;
        case '5':  //�����ֻ��Ų�ѯ
                   printf("�����λͬѧ���������ֻ��ţ�");
                   gets(information_char);       //����ȫ���򲿷��ֻ���
                   func_char=index_stumobile;
                   stu_search_char(stu,information_char,func_char);
                   break;
       }
    return ;
}
char stu_delete_screen(void)//ѧ����Ϣɾ���˵�
{   char choice;
    printf("\n\n\t\t--------ѧ����ҵ��---------\n");   //��ʾ��ҵ�˵�
    printf("\t1. һ��ѧ����ҵ\n");
    printf("\t2. һ��ѧ����ҵ\n");
    printf("\t0. �˳�\n");
    printf("\tplease choice(0-2):");
    choice=getche(); printf("\n");         //���ѡ��
    return choice;
}
void stu_manage_delete(SqList_S &stu)//ѧ����Ϣɾ������
{   char c,yesno;
    char stuinfo[20];
    int find[LIST_INIT_SIZE];
    int position,i;
    SElemType e;
    while((c=stu_delete_screen())!='0')
    switch(c)
       {case '1': //����ѧ��ɾ��һ��ѧ��
                  printf("\t�������ҵͬѧ��ѧ��:");
                  fflush(stdin);
                  gets(stuinfo);
                  strcpy(e.studentno,stuinfo);
                  if(LocateAllElem_SSq(stu,e,equal_stuno,find))
                  { //�ҵ���ͬѧ
                    printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
                    position=find[0];
                    GetElem_SSq(stu,position,e);
                    printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                    printf("�����ͬѧ��ҵ��ȷ��(y/n)");
                    yesno=getche();
                    yesno=toupper(yesno);
                    if(yesno=='Y')
                        ListDelete_SSq(stu,position,e);
                  }
                  else printf("û���ҵ���ͬѧ��\n");
                  break;
        case '2': //���ݰ༶��רҵɾ��һ��ѧ��
                  printf("\t�������ҵͬѧ�İ༶���ƻ�רҵ:");
                  fflush(stdin);
                  gets(stuinfo);
                  strcpy(e.studentmajor,stuinfo); strcpy(e.studentclass,stuinfo);
                  if(LocateAllElem_SSq(stu,e,equal_stuma_or_cl,find))
                  { //�ҵ���ҵͬѧ
                    printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
                    i=0;
                    while(position=find[i])  //find[i]=0��ʾû�з����Ƽ���ѧ����
                    {  GetElem_SSq(stu,position,e);
                       printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
                       i++;
                    }
                    printf("��Щͬѧ����ҵ��ȷ��(y/n)");
                    yesno=getche();
                    yesno=toupper(yesno);
                    if(yesno=='Y')
                        i--;               //����������ɾ��
                        while(i>=0)
                        {position=find[i];
                         ListDelete_SSq(stu,position,e);
                         i--;
                        }
                  }
                  else printf("û���ҵ�ͬѧ��\n");
                  break;
       }
    return ;
}

void stu_manage_update(SqList_S &stu)  //����ѧ���޸�һ��ѧ������Ϣ��ѧ�Ų����޸�
{   char stuinfo[50],yesno;
    SElemType e;
    int position,find[LIST_INIT_SIZE];
    printf("\t�޸�ѧ�����ݣ�ÿ��ֻ���޸�һ��ѧ�����ݣ�ѧ����ѧ�Ų����޸ģ�\n");
    printf("\t�����뱻�޸�����ͬѧ��ѧ�ţ�����0��ʾ�����޸ģ�");
    gets(stuinfo);
    if(stuinfo[0]=='0') return ;
    strcpy(e.studentno,stuinfo);
    if(LocateAllElem_SSq(stu,e,equal_stuno,find))
       { //�ҵ���ͬѧ
         printf("%-10s %-9s %-18s   %-10s %-12s \n"," ѧ �� ","  ��  ��  "," ר    ҵ ","�� �� ","��   ��");
         position=find[0];
         GetElem_SSq(stu,position,e);
         printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
         printf("ȷ���޸����ͬѧ��Ϣ��(y/n)");
         yesno=getche();
         yesno=toupper(yesno);
         if(yesno=='Y')
         { printf("\n\n\t�����޸�Ϊ�����޸İ��س�����"); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentname,stuinfo);
           printf("\tרҵ�޸�Ϊ�����޸İ��س�����"); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentmajor,stuinfo);
           printf("\t�༶�޸�Ϊ�����޸İ��س�����"); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentclass,stuinfo);
           printf("\t�ֻ��޸�Ϊ�����޸İ��س�����"); gets(stuinfo);
           if(strlen(stuinfo)) strcpy(e.studentmobile,stuinfo);
           printf("��ͬѧ��Ϣ�޸�Ϊ��\n");
           printf("%-10s   %-9s %-18s %-10s %-12s \n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
           SetElem_SSq(stu,position,e);
         }
    }
    else printf("û���ҵ���ͬѧ��\n");
}
void stu_manager(SqList_S &stu)
{  //ѧ����Ϣ����
    char c;
    while((c=stu_mana_screen())!='0')
    switch(c)
       {case '1': stu_manage_append(stu);    break;  //����ѧ����Ϣ
        case '2': stu_manage_delete(stu);    break;  //ɾ��ѧ����Ϣ
        case '3': stu_manage_output(stu,1); break;   //���ѧ����Ϣ
        case '4': stu_manage_search(stu);    break;  //��ѯѧ����Ϣ
        case '5': stu_manage_update(stu); break;     //�޸�ѧ����Ϣ
       }
    return ;
}

 void save_stu(SqList_S  &stu)  //��������ѧ����Ϣ���˳�ϵͳʱʹ��
 { FILE *fp;
   int i;
   SElemType e;
   fp=fopen("today_stu.txt","w");
   for(i=1; i<stu.length; i++)
   {  GetElem_SSq(stu,i,e);
      fprintf(fp,"%s %s %s %s %s\n",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
   }
   GetElem_SSq(stu,i,e);      //���һ��ѧ��
   fprintf(fp,"%s %s %s %s %s",e.studentno,e.studentname,e.studentmajor,e.studentclass,e.studentmobile);
   fclose(fp);
}

