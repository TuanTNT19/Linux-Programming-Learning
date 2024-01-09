#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
pipe1 : 
  writer : parrent
  reader : child
pipe2:
  writer : child
  reader : parrent
*/

char buff_s[40];
char buff_r[40];

int main()
{
    int fds1[2];
    int fds2[2];
    pid_t id;

    pipe(fds1);
    pipe(fds2);

    id = fork();
    
    if (id < 0)
    {
        printf("ERROR: Can not make process\n");
        return -1;
    }

    else if (id == 0)
    {
        close(fds1[1]);
        close(fds2[0]);

        while(1)
        {
            read(fds1[0], buff_r, 40);
            printf("Message from parrent: %s", buff_r);

            printf("Message to parrent: ");
            fgets(buff_s, 40, stdin);
            write(fds2[1], buff_s, 40);

        }

        close(fds1[0]);
        close(fds2[1]);
    }

    else{
        close(fds1[0]);
        close(fds2[1]);

        while(1)
        {
            printf("Message to child: ");
            fgets(buff_s, 40, stdin);
            write(fds1[1], buff_s, 40);

            read(fds2[0], buff_r, 50);
            printf("Message from child: %s", buff_r);
        }

        close(fds1[1]);
        close(fds2[0]);
    }

    return 0;

   

}