#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main()
{
      pid_t child_pid;
     child_pid = fork();
     int a = 0;
     if (child_pid>=0)
     {
        if (child_pid ==0)
        {
            printf("This is child process: %d \n",child_pid);
            printf("My PID is %d, my parrent PID is : %d\n", getpid(),getppid());
            printf("Gia tri a+1 la : %d\n",a+1);
            sleep(1);
        
        }
        else{
            printf("I am parrent process : %d\n ",child_pid);
            printf("My PID is %d\n",getpid());
            printf("Gia tri a+1 la : %d\n",a+1);
            sleep(1);
        }

     }
     else{
        printf("Can not fork\n");
     }
     return 0;
}
