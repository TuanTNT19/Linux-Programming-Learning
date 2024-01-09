#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

#define FIFO1 "./mf1"
#define FIFO2 "./mf2"

/*
FIFO1 : A   ->  B
FIFO2 : A   <-  B
*/
// void communication()
// {

// }

void sig_handler1()
{
    if (!unlink(FIFO1))
    {
        printf("unlink FIFO 1 OK\n");
    }

    else if (unlink(FIFO1)){
        printf("Can not unlink FIFO 1\n");
    }

      if (!unlink(FIFO2))
    {
        printf("unlink FIFO 2 OK\n");
    }

    else if (unlink(FIFO2)){
        printf("Can not unlink FIFO 2\n");
    }

    exit(0);

}
char buff_r[40];
char buff_s[40];

int main()
{
    // if (signal(SIGINT, sig_handler1) == SIG_ERR)
    // {
    //     printf("Can not make handler for SIGINT\n");
    // }
    mkfifo(FIFO1, 0666);
    mkfifo(FIFO2, 0666);

    while(1)
    {
        int fd1 = open(FIFO1, O_WRONLY);
        printf("Message to B: ");
        fgets(buff_s,40,stdin);
        write(fd1, buff_s, 40);
        close(fd1);

        int fd2 = open(FIFO2, O_RDONLY);
        read(fd2, buff_r, 40);
        printf("Message from B: %s", buff_r);
        close(fd2);
    }



    return 0;
}