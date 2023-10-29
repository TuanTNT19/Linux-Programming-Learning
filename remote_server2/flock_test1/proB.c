#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    char buff[11]="Tuan Huong\n";
    //char buff1[22]={0};
    int fd = open ("text1.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("Could not open file text\n");
    }
    else{
        printf("open text succesfully\n");
    }
     int l =flock(fd,LOCK_SH);
     if (l==-1)
     {
        printf("Can not lock sh in B\n");
     }
     else{
        printf("Lock Sh ok from B\n");
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
    //  lseek(fd,0,SEEK_SET);
    // int r = read(fd,buff1,sizeof(buff1)-1);
    // if (r==-1)
    // {
    //     printf("Can not read file\n");
    // }
    // else{
    //     printf("Read OK\n");
    //     printf("%s\n",buff1);
    //  }
    //while(1)
    //{
     //   sleep(3);
    //}
 
    close(fd);
    printf("End process B\n");

    return 0;
}