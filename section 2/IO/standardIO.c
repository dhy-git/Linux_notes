#include "stdio.h"
#include "unistd.h"
int main()
{
    char buf[] = "hello linux";
    int i =1 ;
    while(i<=500){
       printf("%s",buf);
       i++;
    }
    while(1);
    return 0;
}
