#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"  
#include "stdlib.h"
#include "signal.h"  //�ں��źź궨��ͷ
int main(int argc,char* argv[])
{
    int sig;
    int pid;
   if(argc<3)
    {
       printf("please input param\n");
       return -1;
   }
    sig = atoi(argv[1]);   //atoi����ʵ���ַ��������γ�����ת��
    pid = atoi(argv[2]);
    printf("sig=%d,pid=%d\n",sig,pid);
    kill(pid,sig);
    return 0;
}
