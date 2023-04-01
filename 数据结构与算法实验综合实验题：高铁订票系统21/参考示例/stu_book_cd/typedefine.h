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
}DATE;                 //定义日期结构体

//–––––线性表的动态分配顺序存储结构–––––
#define LIST_INIT_SIZE  400  //线性表存储空间的初始分配
#define LISTINCREMENT   50   //线性表存储空间的分配增量

void pressanykey()   //显示“敲任意键继续”并等待
{ printf("=========敲任一键继续========");
  getch();fflush(stdin);
  printf("\n\n");
}
int index(char *s1,char *s2)   //在s1[]中查找串s2[],找到返回TRUE，否则返回FALSE
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

DATE Get_Sys_Time( )       //返回当前系统时间
{     struct tm today;       //存放时间的结构体
      time_t one;            //存放时间的类型
      DATE now;
      one=time(&one);              //获得系统时间
      today=*(gmtime(&one));       //将time_t格式系统时间转为struct tm格式
      now.year=today.tm_year-100+2000;     //2011年返回111
      now.month=today.tm_mon+1;           //9月返回8;
      now.day=today.tm_mday;
      return now;
}
