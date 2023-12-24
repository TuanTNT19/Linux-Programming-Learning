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

int t=0;
int main()
{
    sigset_t new_set,old_set;
    if (signal(SIGINT,sig_handler1)==SIG_ERR)
    {
        fprintf(stderr,"Can not handler SIGINT\n");
        exit(EXIT_FAILURE);
    }
    sigemptyset(&new_set);
    sigemptyset(&old_set);
    sigaddset(&new_set,SIGINT);
    printf("new st is %x\n",old_set);
    //kill(getpid(),SIGINT);
    if (sigprocmask(SIG_SETMASK,&new_set,&old_set)==0){
        if (sigismember(&new_set,SIGINT)==1)
        {
            printf("SIGINT exist\n");
        }
        else if (sigismember(&new_set,SIGINT)==0)
        {
            printf("SIGINT dose not exist\n");
        }
    }
    kill(getpid(),SIGINT);
    while(1)
    {
        printf("Main programming running ...\n");
        sleep(1);
        t++;
        if (t==5)
        {
            sigprocmask(SIG_UNBLOCK,&new_set,&old_set);
        }
    }
    return 0;
}