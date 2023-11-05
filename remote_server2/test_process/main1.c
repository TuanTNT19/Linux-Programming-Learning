#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t p,rv;
    char *path = "../ex_process/hello";
    int status;
    p=fork();
    if (p>=0)
    {
        if (p==0)
        {
            printf("This is child process with PID : %d\n",getpid());
           
            int t=4;
            while(t--)
            {
                //execl(path,"hello",NULL);
                printf("Tuan TNT19");
                printf("\n");
                sleep(1);
            }
            sleep(3);
        }
        else{
             printf("This is parent with PID : %d\n",getpid());
            rv = wait(&status);
            printf("Finish waiting\n");
            if (WIFEXITED(status)) {
            printf("Child process exited normally with status: %d\n", WEXITSTATUS(status));
            } 
            else {
            printf("Child process did not exit normally and status is : %d\n", WEXITSTATUS(status));
             }

     
        }
    }
    else{
        printf("Can not fork\n");
    }
    return 0;
}