#include"stdio.h"
#include"string.h"
#include<ctype.h>
#include<conio.h>
#include<time.h>
#include"stdlib.h"

#define  OK	1
#define  ERROR	0
#define  OVERFLOW	-2
#define TRUE 1
#define FALSE 0
typedef  int  Status;

typedef struct
{
   int year,month,day;
}DATE;                 //�������ڽṹ��

//�C�C�C�C�C���Ա�Ķ�̬����˳��洢�ṹ�C�C�C�C�C
#define LIST_INIT_SIZE  400  //���Ա�洢�ռ�ĳ�ʼ����
#define LISTINCREMENT   50   //���Ա�洢�ռ�ķ�������

void pressanykey()   //��ʾ������������������ȴ�
{ printf("=========����һ������========");
  getch();fflush(stdin);
  printf("\n\n");
}
int index(char *s1,char *s2)   //��s1[]�в��Ҵ�s2[],�ҵ�����TRUE�����򷵻�FALSE
{ int i,j,k;
  int len1,len2;
  len1=strlen(s1); len2=strlen(s2);
  i=0;
  while(i<=len1-len2)
  { k=i; j=0;
    while(*(s1+k)==*(s2+j)&&j<len2)
        k++,j++;
    if(j==len2) return TRUE;
    i++;
  }
  return FALSE;
}

DATE Get_Sys_Time( )       //���ص�ǰϵͳʱ��
{     struct tm today;       //���ʱ��Ľṹ��
      time_t one;            //���ʱ�������
      DATE now;
      one=time(&one);              //���ϵͳʱ��
      today=*(gmtime(&one));       //��time_t��ʽϵͳʱ��תΪstruct tm��ʽ
      now.year=today.tm_year-100+2000;     //2011�귵��111
      now.month=today.tm_mon+1;           //9�·���8;
      now.day=today.tm_mday;
      return now;
}
