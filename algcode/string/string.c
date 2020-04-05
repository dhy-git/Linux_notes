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

int main()
{
	int ret,pos;
	char str1[] = "try find the good globle severs google ";
	char str2[] = "google";
	printf(" str1 = %s, len1 = %d\n str2 = %s, len2 =  %d\n",str1,StringLength(str1),str2,StringLength(str2));
	//ret = StringCpy(str2,str1);
	ret = StrNaiveSearch(str1, str2, &pos);
	printf(" str1 = %s, len1 = %d\n str2 = %s, len2 =  %d\n",str1,StringLength(str1),str2,StringLength(str2));
	return 0;
}

