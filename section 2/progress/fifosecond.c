#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"   //系统时钟延时函数
#include "stdlib.h"
#include "fcntl.h"  //open、read函数包含库文件
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
   read(fd,&process_inter,1);   //从管道队列读数，未读到存储内容时产生进程阻塞。
   while(process_inter=0);        //只有first.c进程中向管道赋值为1时向下运行，否则死循环。
   for(i=0; i<5; i++)
   {
       printf("this is second process i=%d\n",i);
       usleep(100);
   }
   while(1);
   return 0;
}
