#include "stdio.h"
#include "unistd.h"
#include "sys/types.h"  
#include "stdlib.h"
#include "signal.h"  //内核信号宏定义头
int main()
{
   printf("raise before");
    raise(9);    // 运行时上一条没有输出，说明raise 实际调用_exit()  而不是库函数exit()，
   printf("raise after\n");
    return 0;
}

