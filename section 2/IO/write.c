#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"

int main(int argc, char * argv[])
{
	int fd;
	short int rd_num;	
	char buf[100];
	fd = open("./a.c", O_RDONLY);
	if(fd<0)
	{
		printf("creat file a.c ERROR\n");
		return -1;
	}
	printf("open file a.c success,fd=%d\n",fd);
	rd_num = read(fd, buf, sizeof(buf));
	printf("message in text is %sread out %d words\n",buf,rd_num);
	close(fd);
	return 0;
}
