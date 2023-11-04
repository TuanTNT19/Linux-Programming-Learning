#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
int main()
{
    int fd;
    char buff1[6]="Irene";
    char buff2[12]="Bae YooHuyn";
    fd = open("hello.txt",O_RDWR | O_CREAT,0667);
	if (fd ==-1)
	{
		printf("Open hello.txt failed\n");
	}
    pid_t p;
    p=fork();
    if (p>=0)
    {
        if (p==0)
        {
            printf("This is child process with PID : %d\n",getpid());
            lseek(fd,0,SEEK_SET);
            write(fd,buff1,sizeof(buff1));
            exit(0);
        }
        else{
            printf("this is parrent process with PID : %d \n",getpid());
            lseek(fd,10,SEEK_SET);
            write(fd,buff2,sizeof(buff2));
            exit(0);
        }
    }
    return 0;
}

