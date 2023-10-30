
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
//#include <Windows.h>>
int main()
{
    char buff[12]="Tuan Truong ";
    char buff1[25]={0};
    char buf[11]="Pham Huong\n";
    int fd = open ("text1.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("Could not open file text\n");
    }
    else{
        printf("open text succesfully\n");
    }

     lseek(fd,13,SEEK_SET);
    int w1=write(fd,buff,sizeof(buff)-1);
    if (w1==-1)
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
    lseek(fd,0,SEEK_SET);
     int w2=write(fd,buf,sizeof(buf)-1);
    if (w2==-1)
    {
        printf("Can not write to text\n");
    }
    else{
        printf("Write succesfully\n");
     }
     lseek(fd,0,SEEK_SET);
    int r1 = read(fd,buff1,sizeof(buff1)-1);
    if (r1==-1)
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