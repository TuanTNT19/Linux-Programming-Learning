#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
pipe1:
- child : writer
- parrent : reader
pipe2:
- child : reader
- parrent : writer
*/

char buff_r[50];
char buff_s[50];
int main()
{
    int fds1[2]; 
    int fds2[2];
    pid_t child_pid;
    
    pipe(fds1);
    pipe(fds2);

    child_pid = fork();

    if (child_pid >= 0)
    {
        if (child_pid == 0)
        {
            close(fds1[0]);
            close(fds2[1]);

            while(1)
            {
                printf("Message to parrent : ");
                fgets(buff_s, 50, stdin);
                write(fds1[1], buff_s, 50);

                read(fds2[0], buff_r, 50);
                printf("Messgae from parrent: %s\n",buff_r);

            }
            close(fds1[1]);
            close(fds2[0]);

        }
        else{
            close(fds1[1]);
            close(fds2[0]);

            while(1)
            {
                read(fds1[0], buff_r, 50);
                printf("Message from child : %s\n",buff_r);

                printf("Message to child: ");
                fgets(buff_s, 50 , stdin);
                write(fds2[1], buff_s, 50);

            }
            close(fds1[0]);
            close(fds2[1]);

        }
    }
    else{
        printf("Can not fork\n");
    }

    return 0;
}