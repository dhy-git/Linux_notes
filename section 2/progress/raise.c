#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"  
#include "stdlib.h"
#include "signal.h"  //�ں��źź궨��ͷ
int main()
{
   printf("raise before");
    raise(9);    // ����ʱ��һ��û�������˵��raise ʵ�ʵ���_exit()  �����ǿ⺯��exit()��
   printf("raise after\n");
    return 0;
}

