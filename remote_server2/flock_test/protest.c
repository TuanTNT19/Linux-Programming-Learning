#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
        char buffr[22]={0};
        char buffw[11]="Pham Huong\n";
    int fd = open("text.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("can not open file text\n");
    }
    else{
        printf("open file succesfully\n");
    }
    int f = flock(fd,LOCK_SH);
 {   if (f==-1)
    {
        printf("can not lock\n");
    }
    else{
        printf("Lock OK\n");
    }
}
  {   lseek(fd,0,SEEK_SET);
    int w = write(fd,buffw,sizeof(buffw)-1);
     if (w==-1)
     {
        printf("CAn not write file\n");
     }
     else{
        printf("Write file succesfully\n");
     }
  }
   {  
    int r = read(fd,buffr,sizeof(buffr)-1);
     if (r==-1)
     {
        printf("Can not read file\n");
     }
     else{
        printf("Read succesfully\n");
        printf("%s",buffr);
     }
   }
     return 0;
}