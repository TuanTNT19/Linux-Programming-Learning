#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <time.h>

void sig_handler1(int num)
{
    printf("I am signal 1 : %d\n",num);
    exit(EXIT_SUCCESS);
}

void sig_handler2(int num)
{
    printf("I am signal 2 : %d\n",num );
}

void sig_handler3(int num)
{
    printf("I am signal 3 : %d\n",num);
}

int main()
{

    if (signal(SIGINT,sig_handler1) == SIG_ERR)
    {
        printf("Can not handler SIGINT\n");
     
    }
    
    if (signal(SIGUSR1,sig_handler2) == SIG_ERR)
    {
        printf("Can not handler SIGUER1\n");
    }
        
    if (signal(SIGUSR2,sig_handler3) == SIG_ERR)
    {
        printf("Can not handler SIGUER2\n");
    }
    
    while(1)
    {
        printf("Main programming running ...\n");
        sleep(1);
    }
    return 0;
}