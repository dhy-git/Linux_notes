#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"           
#include "string.h"
#include "unistd.h"   
#include "fcntl.h"
int main(int argc, char *argv[]){
   DIR *dp;                    
   int fd;
   struct dirent *dir;
   char server[128] = {0};
   int src_fd,des_fd;
   char file[128]={0};
   char buf[128]={0};
   int ret;

start:    
   printf("please input server PATH and Directory name\n");
   scanf("%s",server);
   //list server files
   dp = opendir(server);
   if(dp == NULL){
       printf("open server %s error\n",server);
       goto start;
   }
   printf("open server %s success\n",server);
   
  //read server dir
   while(1){
       dir = readdir(dp);
       if(dir == NULL){
           break;
       }else{
           printf("inode=%ld name =%s\n",dir->d_ino,dir->d_name);
       }
   }
   printf("please input download file\n");
   scanf("%s",file);
   
  //open server file
   src_fd = open(strcat(strcat(server,"/"),file),O_RDONLY);
   if(src_fd < 0){
       printf("open download file :%s\n",file);
       return -1;
   }
   printf("open download file %s success\n",file);
   
    //download file
   des_fd = open(file,O_CREAT | O_WRONLY,0777);
   if(des_fd < 0){
       printf("create file %s error\n",file);
       return -2;
   }
   printf("create file %s success\n",file);
   
   while(1){
       ret = read(src_fd,buf,128);
       if(ret < 128){
           break;
       }
       write(des_fd,buf,ret);
   }
   write(des_fd,buf,ret);
   
   close(des_fd);
   close(src_fd);
   closedir(dp);
   return 0;
}