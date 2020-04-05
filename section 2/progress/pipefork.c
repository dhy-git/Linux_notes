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
   ret = pipe(fd);      //先创建管道
   if(ret<0)
   {
       printf("creat pipe error!\n");
       return -2;
    }
    pid = fork();        //再创建子进程
       if(pid ==0 )                    //子进程部分，是父进程的拷贝，可对同一个管道进行操作
       {
           int i=0;
           read(fd[0], &process_inter,1);          //管道为空时，进入睡眠
           while( process_inter ==0 );
           for(i=0; i<4; i++)
           {  printf("i=%d\n",i);
              usleep(100);
           }
       }
       if(pid >0)                    //父进程部分
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
   printf("creat pipe success. fd[0]=%d, fd[1]=%d\n", fd[0],fd[1]);    //open函数创建成功返回的描述符fd从3开始
   write(fd[1],writebuf,sizeof(writebuf));
   read(fd[0],readbuf,128);
   printf("readbuf = %s\n",readbuf);
   close(fd[0]);
   close(fd[1]);
   return 0;
}
