#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    char buff[11]={0};
    char str[11]="Tuan Truong";
    int fd = open("text.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("can not open file text\n");
    }
    else{
        printf("open file succesfully\n");
    }
      int r = read(fd,buff,sizeof(buff)-1);
      if (r==-1)
      {
        printf("Can not read file\n");
      }
      else{
        printf("Read OK\n");
        printf("%s",buff);
      }
    lseek(fd,0,SEEK_SET);
    int w = write(fd,str,sizeof(str));
    if (w==-1)
    {
        printf("Can not write \n");
    }
    else{
        printf("Write OK\n");
    }
    return 0;
}