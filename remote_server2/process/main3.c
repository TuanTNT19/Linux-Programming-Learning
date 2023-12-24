#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t child_pid;
    int status;
    int cou=0;
    printf("Gia tri cou khoi tao la : %d \n",cou);
    child_pid = fork();
    if (child_pid >=0)
    {
        if (child_pid==0)
    {
        printf("I am the child process \n");
        sleep(5);
        printf("My PID is : %d , my parent PID is : %d \n",getpid(),getppid());
    }
    else{
        printf("I am the parent process \n");
        printf("My PID id %d \n",getpid());
        printf("ID of child process by child_pid is : %d\n",child_pid);
        wait(&status);
        printf("Wait OK from parrent \n");
        //while(1);
    }

    }
    else{
        printf("Fork unsuccessfully\n");
    }
    return 0;
}