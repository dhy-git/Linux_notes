#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"   //ϵͳʱ����ʱ����
#include "stdlib.h"
#include "fcntl.h"  //open��read�����������ļ�
int main()
{
   int fd,i;
   char process_inter = 0;
   fd = open("./myfifo", O_RDONLY);
   if(fd<0)
   {
       printf("open myfifo failure\n");
       return -1;
   }
   printf("open myfifo success\n");
   read(fd,&process_inter,1);   //�ӹܵ����ж�����δ�����洢����ʱ��������������
   while(process_inter=0);        //ֻ��first.c��������ܵ���ֵΪ1ʱ�������У�������ѭ����
   for(i=0; i<5; i++)
   {
       printf("this is second process i=%d\n",i);
       usleep(100);
   }
   while(1);
   return 0;
}
