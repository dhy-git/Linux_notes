#include "stdio.h"
#include "signal.h"
#include "unistd.h"
#include "stdlib.h"
#include "sys/types.h"
#include "sys/wait.h"

int main()
{
	pid_t pid;
	pud = fork();
	if(pid>0)
	{
		sleep(5);
		if(waitpid(pid,NULL,WNOHANG)==0)
		{
			kill(pid,9);
		}
		while(1);
	}
	if(pid==0)
	{
		printf("")
	}
	
}
