#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
   pid_t p,rv;
   int status;
   p=fork();
   if (p>=0)
   {
    if (p==0)
    {
        printf("This is child process with PID : %d\n",getpid());
        sleep(1);
    }
    else{
        printf("This is parent process with PID : %d\n",getpid());
        // rv = wait(&status);
        //  if (WIFEXITED(status)) {
        //     printf("Child process exited normally with status: %d\n", WEXITSTATUS(status));
        //     } 
        //     else {
        //     printf("Child process did not exit normally and status is : %d\n", WEXITSTATUS(status));
        //      }
        while(1);
    }
   }
   else{
    printf("Can not fork\n");
   }
    return 0;
}