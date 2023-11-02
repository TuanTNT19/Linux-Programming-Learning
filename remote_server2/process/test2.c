#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
int main()
{
    printf("Start program\n");
    printf("Hello from main\n");
    printf("Kill current process \n");
    kill(getpid(),SIGKILL);
    while(1){
        printf("Tuan TNT19\n");
        sleep(2);
    }
    return 0;
}