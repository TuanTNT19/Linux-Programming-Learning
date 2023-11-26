#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t p;
    int status;
    p=fork();
    if (p>=0)
    {
    if (p==0)
    {
        printf("This is child process with PID : %d\n",getpid());
        while(1);
        //printf("End process child\n");
        //sleep(5);
        printf("Check\n");
       // exit(0);
    }
    else{
        printf("Start wait\n");
       pid_t rv =  wait(&status);
       if (rv ==-1)
       {
        printf("Can not wait\n");
       }
       else{
        printf("Wait OK , PID of child process : %d \n",rv);
        printf("Parent PID : %d\n",getpid());
       }
       printf("Status : %d\n",status);
        if (WIFEXITED(status)) {
            printf("Child process  ended normally with status: %d\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not exit normally and status is : %d\n", WEXITSTATUS(status));
        }
    }
}
else{
    printf("Can not fork\n");
}
return 0;
}