#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO1 "./mf1"
#define FIFO2 "./mf2"


/*
FIFO1 : A   ->  B
FIFO2 : A   <-  B
*/
char buff_r[40];
char buff_s[40];

int main()
{
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while(1)
    {
        int fd1 = open(FIFO1, O_RDONLY);
        read(fd1, buff_r, 40);
        printf("Message from A: %s", buff_r);
        close(fd1);

        int fd2 = open(FIFO2, O_WRONLY);
        printf("Message to A: ");
        fgets(buff_s, 40, stdin);
        write(fd2, buff_s, 40);
        close(fd2);

    }

    return 0;
}