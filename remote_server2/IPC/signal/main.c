#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

void sig_handler1(int num)
{
    printf("I am signal 1 : %d\n",num);
    exit(EXIT_SUCCESS);
}

void sig_handler2(int num)
{
    printf("I am signal 2 : %d\n",num);
}

void sig_handler3(int num)
{
    printf("I am signal 3 : %d\n",num);
    exit(EXIT_SUCCESS);

}

int main()
{
    if (signal(SIGINT,sig_handler1)==SIG_ERR)
    {
        fprintf(stderr,"Can not handler SIGINT\n");
        exit(EXIT_FAILURE);
    }
    signal(SIGKILL, sig_handler2);
    signal(SIGTERM, sig_handler3);
    printf("Process ID : %d\n",getpid());
    sleep(4);
    kill(getpid(),SIGINT);
    while(1)
    {
        printf("Main programming running ...\n");
        sleep(1);
    }
    return 0;
}