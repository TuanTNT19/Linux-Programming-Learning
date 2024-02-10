#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO1 "./f1"        /* p1 -> p2*/
#define FIFO2 "./f2"        /* p1 <- p2*/

int main()
{
    char buff_r[50];
    char buff_s[50];

    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while(1)
    {
        int fd1 = open(FIFO1, O_WRONLY);
        printf("Message to process 2: ");
        fgets(buff_s, 50, stdin);
        write(fd1, buff_s, 50);
        close(fd1);

        int fd2 = open(FIFO2, O_RDONLY);
        read(fd2, buff_r, 50);
        printf("Message from process 2: %s\n", buff_r);
        close(fd2);
    }
    
    return 0;
}