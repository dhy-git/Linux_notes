/*
	问题：
		有一些人，人数在50到60之间，现在这些人排成一队，从左到右一次按照1-4报数；然后从右到左依次按照1-3报数，最后有15个人两次报数相同，
		问：一共有多少个人？
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

int main()
{
	int num;
	int i,j,count;
	int p[65]={0};
	int q[65]={0};
	for(num=50; num<60;num++)
	{
		for(i = 0; i < num; i++)
		{
			p[i] = i%4;
		}
		for(i = 0; i < num; i++)
		{
			q[num-i] = i%3;
		}
		printf("try num = %d   ", num);
		count = 0;
		for(j=0; j<num; j++)
		{
			if(q[j] == p[j])
			{
				count++;
			}
		}
		printf("same count == %d\n",count);
	}
}