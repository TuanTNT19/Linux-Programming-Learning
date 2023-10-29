#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
//#include <Windows.h>>
int main()
{
    char buff[11]="Pham Huong\n";
    char buff2[26]={0};
    int fd=open("text.txt",O_RDWR | O_CREAT,0667);
    if (fd ==-1)
    {
        printf("Can not open file text\n");
    }
    else{
        printf("Open file OK !\n");
    }
    int f = flock(fd,LOCK_EX);
    if (f==-1)
    {
        printf("Can not lock EX from B\n");
    }
    else{
        printf("Lock EX ok from B\n");
    }
    lseek(fd,0,SEEK_SET);
    int w = write(fd,buff,sizeof(buff)-1);
    if (w==-1)
    {
        printf("Can not write to file txt\n");
    }
    else{
        printf("Write to file txt ok from A\n");
    }
    lseek(fd,0,SEEK_SET);
    int r=read(fd,buff2,sizeof(buff2)-1);
    if (r==-1)
    {
      printf("Can not read from B\n");
    }
    else{
      printf("REad from B OK \n");
      printf("%s\n",buff2);
    }
    close(fd);
    printf("End of process B\n");
    return 0;
}