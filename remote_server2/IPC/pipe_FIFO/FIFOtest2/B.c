#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FIFO1 "./fifo1" //writer A        reader B
#define FIFO2 "./fifo2"  //reader A       writer B

int fd1, fd2;
char buff_r[50];
char buff_s[50];

int main()
{
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while(1)
    {
        fd1 = open(FIFO1, O_RDONLY);
        read(fd1, buff_r, 50);
        printf("Data from A: %s",buff_r);
        close(fd1);

        fd2 = open(FIFO2, O_WRONLY);
        printf("Data to A: ");
        fgets(buff_s, 50, stdin);
        write(fd2, buff_s, 50);
        close(fd2);
    }

    return 0;
}