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
        printf("End process child\n");
    }
    else{
        printf("Start wait\n");
       int rv =  wait(&status);
       if (rv ==-1)
       {
        printf("Can not wait\n");
       }
       else{
        printf("Wait OK \n");
       }
    }
}
else{
    printf("Can not fork\n");
}
return 0;
}