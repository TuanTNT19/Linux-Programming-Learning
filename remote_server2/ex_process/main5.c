#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void func()
{
    printf("In am func\n");
    wait(NULL);
}
int main()
{
    pid_t p;
    p=fork();
    if (p>=0)
    {
        if (p==0)
        {
        printf("This is child process with PID : %d \n",getpid());
        while(1);
        }
        else{
            signal(SIGCHLD,func);
            printf("This is parrent process with PID : %d \n",getpid());
             while(1);
        }

    }
    else{
        printf("Can not fork\n");
    }
    return 0;
}