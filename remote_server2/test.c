/*
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
//#include <Windows.h>>
int main()
{
    char buff[11]="Tuan Huong\n";
    char buff2[22]={0};
    int fd=open("text1.txt",O_RDWR | O_CREAT,0667);
    if (fd ==-1)
    {
        printf("Can not open file text\n");
    }
    else{
        printf("Open file OK !\n");
    }
  
    lseek(fd,12,SEEK_SET);
    int w = write(fd,buff,sizeof(buff)-1);
    if (w==-1)
    {
        printf("Can not write to file txt\n");
    }
    else{
        printf("Write to file txt ok from A\n");
    }
     lseek(fd,0,SEEK_SET);
     int r = read(fd,buff2,sizeof(buff2)-1);
     if (r==-1)
     {
        printf("Can not read\n");
     }
     else{
        printf("Read OK\n");
        printf("%s\n",buff2);
     }
    close(fd);
 
    return 0;
}
*/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
//#include <Windows.h>>
int main()
{
    char buff[12]="Tuan Truong\n";
    char buff1[25]={0};
    int fd = open ("text1.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("Could not open file text\n");
    }
    else{
        printf("open text succesfully\n");
    }
   int l = flock(fd,LOCK_EX);
     if (l==-1)
    {
      
       printf("can not lock EX in A \n");
    }
    else 
    {
       printf("Lock EX succesfully in A\n");
    }
     lseek(fd,12,SEEK_SET);
    int w=write(fd,buff,sizeof(buff)-1);
    if (w==-1)
    {
        printf("Can not write to text\n");
    }
    else{
        printf("Write succesfully\n");
     }
     lseek(fd,0,SEEK_SET);
    int r = read(fd,buff1,sizeof(buff1)-1);
    if (r==-1)
    {
        printf("Can not read file\n");
    }
    else{
        printf("Read OK\n");
        printf("%s\n",buff1);
    }
    //while(1)
    //{
        //sleep(5);
  // }
 
 
    //close(fd);
     //printf("End process A\n");
      //flock(fd,LOCK_UN);
    return 0;
}