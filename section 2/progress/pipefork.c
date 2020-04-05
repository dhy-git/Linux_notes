#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main()
{
   int ret;
   int fd[2];
   char writebuf[] = "hello linux";
   char readbuf[128];
    pid_t pid;
    char process_inter = 0;
   ret = pipe(fd);      //�ȴ����ܵ�
   if(ret<0)
   {
       printf("creat pipe error!\n");
       return -2;
    }
    pid = fork();        //�ٴ����ӽ���
       if(pid ==0 )                    //�ӽ��̲��֣��Ǹ����̵Ŀ������ɶ�ͬһ���ܵ����в���
       {
           int i=0;
           read(fd[0], &process_inter,1);          //�ܵ�Ϊ��ʱ������˯��
           while( process_inter ==0 );
           for(i=0; i<4; i++)
           {  printf("i=%d\n",i);
              usleep(100);
           }
       }
       if(pid >0)                    //�����̲���
       {
           int i=0;
           for(i = 0; i<8; i++)
           {
               printf("i = %d\n",i);
               usleep(100);
           }
           process_inter = 1;
           sleep(3);
           write(fd[1], &process_inter, 1);
       }
	//sleep(2);
   printf("creat pipe success. fd[0]=%d, fd[1]=%d\n", fd[0],fd[1]);    //open���������ɹ����ص�������fd��3��ʼ
   write(fd[1],writebuf,sizeof(writebuf));
   read(fd[0],readbuf,128);
   printf("readbuf = %s\n",readbuf);
   close(fd[0]);
   close(fd[1]);
   return 0;
}
