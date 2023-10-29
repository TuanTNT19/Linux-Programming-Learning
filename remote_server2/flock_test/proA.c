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
    int fd=open("text.txt",O_RDWR | O_CREAT,0667);
    if (fd ==-1)
    {
        printf("Can not open file text\n");
    }
    else{
        printf("Open file OK !\n");
    }
    int f = flock(fd,LOCK_SH);
    if (f==-1)
    {
        printf("Can not lock sh from B\n");
    }
    else{
        printf("Lock sh ok from B\n");
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
    sleep(5);
    close(fd);
    printf("End of process A\n");
    return 0;
}