#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main()
{
    printf("Start ! \n");
    pid_t p;
    char *path ="../test/check";
    p=fork();
    if (p>=0)
    {
        if (p==0)
        {
            printf("This is child process\n");
            printf("PID : %d \n",getpid());
            execl(path,"check",NULL);
            sleep(1);
        }
        else{
            printf("This is parrent process\n");
            printf("PID : %d \n",getpid());
             while(1)
            {
                printf("Bae Joo-Huyn from parrent process\n");
                sleep(1);
            }
        }
    }
else{
    printf("Can not fork\n");
}
     return 0;
}
