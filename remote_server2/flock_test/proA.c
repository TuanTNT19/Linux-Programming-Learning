#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    char buff[11]="Tuan Huong\n";
    int fd = open ("text1.txt",O_RDWR | O_CREAT,0667);
    if (fd == -1)
    {
        printf("Could not open file text\n");
    }
    else{
        printf("open text succesfully\n");
    }
    int w=write(fd,buff,sizeof(buff)-1);
    if (w==-1)
    {
        printf("Can not write to text\n");
    }
    else{
        printf("Write succesfully\n");
    }
    int l = flock(fd,LOCK_SH);
    if (l==-1)
    {
        printf("can not lock file \n");
    }
    else 
    {
        printf("Lock succesfully\n");
    }
    while(1){
        sleep(1);
    }
    close(fd);
    return 0;
}