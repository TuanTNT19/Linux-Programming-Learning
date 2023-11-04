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
        
        printf("Check\n");
    }
    else{
        printf("Start wait\n");
       pid_t rv =  wait(&status);
       if (rv ==-1)
       {
        printf("Can not wait\n");
       }
       else{
        printf("Wait OK , PID : %d \n",rv);
       }
        if (WIFEXITED(status)) {
            printf("Child process  exited with status: %d\n", WEXITSTATUS(status));
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