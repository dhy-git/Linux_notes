#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"

int main()
{
    int ret;
    int fd[2];
    char writebuf[] = "terminal test\n";
    char readbuf[128];
    ret = pipe(fd);
    if(ret<0)
    {
       printf("creat pipe error!\n");
       return -2;
    }
    printf("creat pipe success. fd[0]=%d, fd[1]=%d\n", fd[0],fd[1]);    //open函数创建成功返回的描述符fd从3开始
    write(fd[1],writebuf,sizeof(writebuf));
    read(fd[0],readbuf,128);
    printf("readbuf = %s\n",readbuf);
    close(fd[0]);
    close(fd[1]);
    return 0;
}
