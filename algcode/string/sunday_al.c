#include "stdio.h"
#include "stdlib.h"
#define ERROR (-1)
#define OK 1

typedef int Status;
//int memchr(const char str, char c, int n)
//{
//	int i;
//	for(i=0;i<n;i++)
//	{
//		if(*(str+i) == c)
//			return i;
//	}
//	return ERROR;
//}
int StringLength(char *str)
{
	int i=0;
	while(str[i] != '\0')
		i++;
	return i;
}

Status StringCpy(char *des , char *src)
{
	int i,len_d,len_s;
	len_s = StringLength(src);
	len_d = StringLength(des);
	if(len_d<len_s)
		return ERROR;
	while(src[i] != '\0')
	{
		des[i] = src[i];
		i++;
	}
	des[i] = '\0';
	return OK;
}

Status StringSearch(char *des , char t, int *pos)
{
	int k;
	int len = StringLength(des);
	for(k=0;k<len;k++)
	{
		if(des[k] == t)
		{
			*pos = k;
			return OK;
		}
	}
	return ERROR;
}


Status StringCmp(char *des , char *src, int pos)
{
	int len_d,len_s,i=0;
	len_d = StringLength(des);
	len_s = StringLength(src);
	if( pos<0 || len_d -pos + 1 <len_s)
	{
		printf("compare failure\n");
		return ERROR;
	}
	while(i<=len_s-1)
	{
		if(des[pos+i-1] != src[i])
		{
			printf("the %d position is  uncompared\n",i+1);
			return ERROR;
		}
		i++;
	}
	return OK;
}

Status StrNaiveSearch(char *des , char *src, int *pos)
{
	int ret,len_d,len_s,i=0;
	len_d = StringLength(des);
	len_s = StringLength(src);
	if( len_d<len_s)
	{
		printf("Length uncompare\n");
		return ERROR;
	}
	for(;i<len_d-len_s+1;i++)
	{
		ret = StringCmp(des,src,i);
		if(ret == OK)
		{
			*pos= i;
			printf("target finding success, position at %d\n",*pos);
			return OK;
		}
	}
	return ERROR;
}

Status Sunday_ALG(char *des , char *src, int *pos)
{
	int ret,len_d,len_s,k,j,i=0;
	int tmp;
	len_d = StringLength(des);
	len_s = StringLength(src);
	if( len_d<len_s)
	{
		printf("Length uncompare\n");
		return ERROR;
	}

	while(i < len_d-len_s+1)
	{
		j=0;
		while(j <= len_s-1)
		{
			if(des[i+j] == src[j])
			{
				if(j == len_s-1)
				{
					*pos = i;
					return OK;
				}
				else
				{
					printf("round %d : the %d is correct\n",i,j);
					j++;
				}
			}
			else
			{
				printf("round %d : the %d is not matching\n",i,j);
				ret = StringSearch(src, des[i+len_s], &tmp);
				if(ret == ERROR)
				{
					printf("there is no %c in src string\n",des[i+len_s]);
					i+=len_s+1;
				}
				else
				{
					
					printf("there is  %c at %d\n",des[i+len_s],tmp);
					i+= len_s - tmp;
				}
				break;
			}
		}
	}
	return ERROR;
}

int main()
{
	int ret,pos;
	char str1[] = "try find the good globle severs google";
	char str2[] = "google";
	printf(" str1 = %s, len1 = %d\n str2 = %s, len2 =  %d\n",str1,StringLength(str1),str2,StringLength(str2));
	//ret = StringCpy(str2,str1);
	ret =Sunday_ALG(str1, str2, &pos);
	if(ret == OK)
		printf("find the target, locate in %d\n",pos);
	else 
		printf("No found\n");
	printf(" str1 = %s, len1 = %d\n str2 = %s, len2 =  %d\n",str1,StringLength(str1),str2,StringLength(str2));
	return 0;
}
