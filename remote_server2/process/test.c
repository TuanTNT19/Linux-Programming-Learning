#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    pid_t child_pid;
    int cou=2;
    printf("Gia tri cou khoi tao la : %d \n",cou);
    child_pid = fork();
    if (child_pid >=0)
    {
        if (child_pid==0)
    {
        printf("I am the child process , cou : %d\n",++cou);
        printf("My PID is : %d , my parent PID is : %d \n",getpid(),getppid());
        //sleep(1);
    }
    else{
        printf("I am the parent process , cou : %d\n",++cou);
        printf("My PID id %d \n",getpid());
        //while(1);
    }

    }
    else{
        printf("Fork unsuccessfully\n");
    }
    return 0;
}